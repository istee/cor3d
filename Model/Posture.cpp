#include "Posture.h"

namespace cor3d
{
    Posture::Posture(vector<Joint*>& joints): QObject(), BaseEntity()
    {
        _isEdited = false;
        _chainsNeedUpdate = false;
        _postureAlgorithmType = RIGID;
        _joints = joints;
        _selectedJoint = -1;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            _jointAbsolutePostureCoordinates.push_back(j->get_coordinates());
            _jointAbsoluteInitialPostureCoordinates.push_back(j->get_coordinates());
        }
    }

    Posture::Posture(unsigned int id, string name, vector<Joint*>& joints): QObject(), BaseEntity(id, name)
    {
        _isEdited = false;
        _chainsNeedUpdate = false;
        _postureAlgorithmType = RIGID;
        _joints = joints;
        _selectedJoint = -1;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            _jointAbsolutePostureCoordinates.push_back(j->get_coordinates());
            _jointAbsoluteInitialPostureCoordinates.push_back(j->get_coordinates());
        }
    }

    ostream& operator <<(ostream& lhs, const Posture& rhs)
    {
        lhs << "posture_name: " << rhs.getName() << endl;
        lhs << "posture_id: " << rhs.getId() << endl;
        lhs << "joint_count " << rhs._jointAbsolutePostureCoordinates.size() << endl;
        for (unsigned int i = 0; i < rhs._jointAbsolutePostureCoordinates.size(); i++)
        {
            lhs << rhs._jointAbsoluteInitialPostureCoordinates[i] << " ";
        }
        lhs << endl;
        return lhs;
    }

    istream& operator >>(istream& lhs, Posture& rhs)
    {
        string text;
        char name[256];
        int number;
        DCoordinate3 coordinates;
        lhs >> text;
        lhs.getline(name, 256);
        rhs.setName(name);
        lhs >> text >> rhs._id;
        lhs >> text >> number;
        cout << "number " << number << endl;
        rhs._jointAbsolutePostureCoordinates.clear();
        rhs._jointAbsoluteInitialPostureCoordinates.clear();
        for (unsigned int i = 0; i < number; i++)
        {
            lhs >> coordinates;
            rhs._jointAbsoluteInitialPostureCoordinates.push_back(coordinates);
            rhs._jointAbsolutePostureCoordinates.push_back(coordinates);
        }
        return lhs;
    }

    unsigned int Posture::getAlgorithmType() const
    {
        return _postureAlgorithmType;
    }

    //getter functions
    bool Posture::isEdited() const
    {
        return _isEdited;
    }

    Joint* Posture::selectedJoint() const
    {
        return _joints[_selectedJoint];
    }

    void Posture::selectJoint(int jointId)
    {
        _selectedJoint = jointId;
        _chainsNeedUpdate = true;
    }

    const DCoordinate3& Posture::getAbsolutePostureCoordinate(unsigned int jointId) const
    {
        return _jointAbsolutePostureCoordinates[jointId];
    }

    void Posture::MoveSelected(const DCoordinate3& target)
    {
        cout << *this << endl;
        cout << "move " << _isEdited << endl;
        if (!_isEdited)
        {
            _isEdited = true;
            cout << "before chains " << _selectedJoint << endl;
            emit modelPostureIsEdited(this, _isEdited);
            constructChains(_selectedJoint);
        }

        if (_chainsNeedUpdate)
        {
            cout << "_chainsneedupdate " << endl;
            clearChains();
            constructChains(_selectedJoint);
        }

        cout << "after chains " << endl;
        if (_chains.size() > 0)
        {
            DCoordinate3 selectedCoordinates = DCoordinate3(_chains[0].get_joint_coordinates(_chains[0].get_chain_size() - 1));

            fabrik(_chains[0], target, 1e-10);

            selectedCoordinates -= DCoordinate3(_chains[0].get_joint_coordinates(_chains[0].get_chain_size() - 1));

            if (FABRIK == _postureAlgorithmType)
            {
                for (unsigned int i = 1; i < _chains.size(); i++)
                {
                    SimpleForwardFABRIK(&_chains[i], _chains[_chains[i].getChainParent()].get_chain_ending(), 1e-10);
                }
            }
            else
            {
                for (unsigned int i = 1; i < _chains.size(); i++)
                {
                    Chain parentChain = _chains[_chains[i].getChainParent()];
                    _chains[i].set_joint_coordinates(parentChain.get_chain_ending(), _chains[i].get_chain_size() - 1);
                    for (unsigned int j = 0; j < _chains[i].get_chain_size() - 1; j++)
                    {

                        _chains[i].set_joint_coordinates(_chains[i].get_joint_coordinates(j) - selectedCoordinates, j);
                    }
                }
            }

            FinalizeMove();

            emit modelPostureDataChanged(this, _joints[_chains[0].getJointId(0)]->getName());
        }
    }

    void Posture::fabrik(Chain& chain, DCoordinate3 target, double tolerance)
    {
        double *lengths = new double[chain.get_chain_size()];
        double total_length = 0.0;
        for (int i = 0; i < chain.get_chain_size() - 1; i++)
        {
            lengths[i] = (chain.get_joint_coordinates(i) - chain.get_joint_coordinates(i + 1)).length();
            total_length += lengths[i];
        }
        double distance = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
        if (distance > total_length)
        {
            for (int i = 0; i < chain.get_chain_size() - 1; i++)
            {
                double r = (target - chain.get_joint_coordinates(i)).length();
                double lambda = lengths[i] / r;

                // innen folytatni
                chain.set_joint_coordinates(DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * target), i + 1);
            }
        }
        else
        {
            DCoordinate3 b = DCoordinate3(chain.get_joint_coordinates(0));
            double dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            unsigned int iteration_count = 0, max_iteration = 10;
            while (dif_A > tolerance && iteration_count < max_iteration)
            {
                iteration_count++;
                chain.set_joint_coordinates(DCoordinate3(target), chain.get_chain_size() - 1);
                for (int i = chain.get_chain_size() - 2; i >= 0; i--)
                {
                    double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                    double lambda = lengths[i] / r;
                    chain.set_joint_coordinates((1 - lambda) * chain.get_joint_coordinates(i + 1) + lambda * chain.get_joint_coordinates(i), i);
                }
                chain.set_joint_coordinates(b, 0);
                for (int i = 0; i < chain.get_chain_size() - 1; i++)
                {
                    double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                    double lambda = lengths[i] / r;
                    chain.set_joint_coordinates( DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * chain.get_joint_coordinates(i + 1)), i + 1);
                }
                dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            }
        }
    }

    void Posture::SimpleForwardFABRIK(Chain *chain, DCoordinate3 target, double tolerance)
    {
        double *lengths = new double[chain->get_chain_size()];
        for (int i = 0; i < chain->get_chain_size() - 1; i++)
        {
            lengths[i] = (chain->get_joint_coordinates(i) - chain->get_joint_coordinates(i + 1)).length();
        }

        chain->set_joint_coordinates(DCoordinate3(target), chain->get_chain_size() - 1);
        for (int i = chain->get_chain_size() - 2; i >= 0; i--)
        {
            double r = (chain->get_joint_coordinates(i + 1) - chain->get_joint_coordinates(i)).length();
            double lambda = lengths[i] / r;
            chain->set_joint_coordinates(DCoordinate3((1 - lambda) * chain->get_joint_coordinates(i + 1) + lambda * chain->get_joint_coordinates(i)), i);
        }

        DCoordinate3 offset = chain->get_chain_start() - target;
        for (int i = 0; i < chain->get_chain_size(); i++)
        {
            chain->set_joint_coordinates(DCoordinate3(chain->get_joint_coordinates(i) - offset), i);
        }

    }

    int Posture::construct_chains_(int joint_id, int chain_index, int parent_chain_index)
    {
        Chain chain = Chain(chain_index, parent_chain_index, false);
        chain.add_joint_to_front(_jointAbsolutePostureCoordinates[getJointById(joint_id)->get_parent()], getJointById(getJointById(joint_id)->get_parent())->getId());
        while(getJointById(joint_id)->get_children().size() == 1)
        {
            chain.add_joint_to_front(_jointAbsolutePostureCoordinates[joint_id], getJointById(joint_id)->getId());
            joint_id = getJointById(joint_id)->get_children()[0];
        }
        chain.add_joint_to_front(_jointAbsolutePostureCoordinates[joint_id], getJointById(joint_id)->getId());
        _chains.push_back(chain);
        vector<unsigned int> children = getJointById(joint_id)->get_children();
        int chain_number = 1;
        for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
        {
            chain_number += construct_chains_(*it, chain_index + chain_number, chain_index);
        }
        return chain_number;
    }

    void Posture::constructChains(unsigned int selectedJoint)
    {
        //update_joint_coordinates();
        if (selectedJoint > 0)
        {
            Chain chain = Chain(0, -1, true);
            forward_chain(chain, selectedJoint);
            _chains.push_back(chain);
            vector<unsigned int> children = getJointById(selectedJoint)->get_children();
            int chain_number = 1;
            for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
            {
                chain_number += construct_chains_(*it, chain_number, 0);
            }
        }
    }

    void Posture::forward_chain(Chain& chain, int joint_id)
    {
        int index = joint_id;
        while(getJointById(index)->get_parent() != -1 && getJointById(getJointById(index)->get_parent())->get_children().size() == 1)
        {
            index = getJointById(index)->get_parent();
        }
        if (getJointById(index)->get_parent() != -1)
        {
            chain.add_joint(_jointAbsolutePostureCoordinates[getJointById(index)->get_parent()], getJointById(getJointById(index)->get_parent())->getId());
        }
        while (index != joint_id)
        {
            chain.add_joint(_jointAbsolutePostureCoordinates[index], getJointById(index)->getId());
            index = getJointById(index)->get_children()[0];
        }
        chain.add_joint(_jointAbsolutePostureCoordinates[joint_id], getJointById(joint_id)->getId());
    }

    void Posture::clearChains()
    {
        _chains.clear();
    }

    void Posture::renderPosture(RenderingOptions* renderingOptions, bool glLoad) const
    {
        renderPostureJoints(renderingOptions, glLoad);
        renderPostureLinks(renderingOptions, true);
        render_chains(renderingOptions, glLoad);
    }

    void Posture::renderPostureJoints(RenderingOptions* renderingOptions, bool glLoad) const
    {
        const TriangulatedMesh3* joint_model = renderingOptions->get_joint_model();

        if (renderingOptions->get_renderJoints() && joint_model)
        {
            renderingOptions->get_material(renderingOptions->get_joint_material())->Apply();

            for(unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
            {
                Joint* joint = (Joint*) _joints[i];
                DCoordinate3 absoluteCoordinate = _jointAbsolutePostureCoordinates[i];
                glPointSize(1.0);
                glPushMatrix();
                glTranslated(absoluteCoordinate.x(), absoluteCoordinate.y(), absoluteCoordinate.z());
                glScalef(joint->get_scale().x() / 10, joint->get_scale().y() / 10, joint->get_scale().z() / 10);
                if (glLoad)
                {
                    glLoadName(joint->getId() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }

    void Posture::renderPostureLinks(RenderingOptions* renderingOptions, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = renderingOptions->get_link_model();

        if (renderingOptions->get_renderLinks() && link_model &&_joints.size() > 1)
        {
            renderingOptions->get_material(renderingOptions->get_link_material())->Apply();

            for(unsigned int i = 1; i < _jointAbsoluteInitialPostureCoordinates.size(); i++)
            {
                Joint* joint = (Joint*) _joints[i];
                DCoordinate3 start = _jointAbsoluteInitialPostureCoordinates[joint->get_parent()];
                DCoordinate3 end = _jointAbsoluteInitialPostureCoordinates[joint->getId()];
                DCoordinate3 k_prime = end - start;

                float length = k_prime.length();

                k_prime /= length;

                DCoordinate3 j_prime;

                while (j_prime.length() < EPS)
                {
                    j_prime =  k_prime;
                    j_prime ^= DCoordinate3((double)rand() / (double)RAND_MAX , (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
                }

                DCoordinate3 i_prime = j_prime;
                i_prime ^= k_prime;

                float matrix[16];

                k_prime.normalize();
                j_prime.normalize();
                i_prime.normalize();

                matrix[0] = i_prime[0];
                matrix[1] = i_prime[1];
                matrix[2] = i_prime[2];
                matrix[3] = 0.0;

                matrix[4] = j_prime[0];
                matrix[5] = j_prime[1];
                matrix[6] = j_prime[2];
                matrix[7] = 0.0;

                matrix[ 8] = k_prime[0];
                matrix[ 9] = k_prime[1];
                matrix[10] = k_prime[2];
                matrix[11] = 0.0;

                matrix[12] = start[0];
                matrix[13] = start[1];
                matrix[14] = start[2];
                matrix[15] = 1.0;

                DCoordinate3 jointScale = getJointById(joint->get_parent())->get_scale();
                double scale = min(jointScale.x(), min(jointScale.y(), jointScale.z())) / 10.0;

                glPushMatrix();
                    glMultMatrixf(matrix);
                    glScalef(scale, scale, length);
                    link_model->Render();
                glPopMatrix();
            }
        }
    }

    void Posture::render_chains(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->get_link_model();
        MatFBRuby.Apply();
        for(vector<Chain>::const_iterator it = _chains.begin(); it != _chains.end(); it++)
        {
            for (int i = 1; i < (*it).get_chain_size(); i++)
            {
                    DCoordinate3 start =  (*it).get_joint_coordinates(i - 1);
                    DCoordinate3 end = (*it).get_joint_coordinates(i);
                    DCoordinate3 k_prime = end - start;

                    float length = k_prime.length();

                    k_prime /= length;

                    DCoordinate3 j_prime;

                    while (j_prime.length() < EPS)
                    {
                        j_prime =  k_prime;
                        j_prime ^= DCoordinate3((double)rand() / (double)RAND_MAX , (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
                    }

                    DCoordinate3 i_prime = j_prime;
                    i_prime ^= k_prime;

                    float matrix[16];

                    k_prime.normalize();
                    j_prime.normalize();
                    i_prime.normalize();

                    matrix[0] = i_prime[0];
                    matrix[1] = i_prime[1];
                    matrix[2] = i_prime[2];
                    matrix[3] = 0.0;

                    matrix[4] = j_prime[0];
                    matrix[5] = j_prime[1];
                    matrix[6] = j_prime[2];
                    matrix[7] = 0.0;

                    matrix[ 8] = k_prime[0];
                    matrix[ 9] = k_prime[1];
                    matrix[10] = k_prime[2];
                    matrix[11] = 0.0;

                    matrix[12] = start[0];
                    matrix[13] = start[1];
                    matrix[14] = start[2];
                    matrix[15] = 1.0;

                    DCoordinate3 jointScale = getJointById((*it).getJointId(i))->get_scale();
                    double scale = min(jointScale.x(), min(jointScale.y(), jointScale.z())) / 10.0;

                    glPushMatrix();
                        glMultMatrixf(matrix);
                        glScalef(scale, scale, length);
                        link_model->Render();
                    glPopMatrix();
                }
        }
    }

    Joint* Posture::getJointById(unsigned int index) const
    {
        return _joints[index];
    }

    void Posture::FinalizeMove()
    {
        for (unsigned int i = 0; i < _chains[0].get_chain_size(); i++)
        {
            _jointAbsolutePostureCoordinates[_chains[0].getJointId(i)] = _chains[0].get_joint_coordinates(i);
        }
        for (unsigned int i = 1; i < _chains.size(); i++)
        {
            for (unsigned int j = 0; j < _chains[i].get_chain_size(); j++)
            {
                _jointAbsolutePostureCoordinates[_chains[i].getJointId(j)] = _chains[i].get_joint_coordinates(j);
            }
        }
    }

    void Posture::handleViewChangesAccepted()
    {
        _isEdited = false;
        _chainsNeedUpdate = false;
        clearChains();
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsoluteInitialPostureCoordinates[i] = _jointAbsolutePostureCoordinates[i];
        }
        emit modelPostureDataChanged(this, _joints[0]->getName());
    }

    void Posture::handleViewChangesCanceled()
    {
        _isEdited = false;
        _chainsNeedUpdate = false;
        clearChains();
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsolutePostureCoordinates[i] = _jointAbsoluteInitialPostureCoordinates[i];
        }
        emit modelPostureDataChanged(this, _joints[0]->getName());
    }

    void Posture::handleViewPostureAlgorithmTypeSelected(const string& algorithmName)
    {
        cout << "algorithm changed " << algorithmName << endl;
        if ("FABRIK" == algorithmName)// && FABRIK =! _postureAlgorithmType)
        {
            _postureAlgorithmType = FABRIK;
        }
        if ("RIGID" == algorithmName)// && RIGID =! _postureAlgorithmType)
        {
            _postureAlgorithmType = RIGID;
        }
    }
}
