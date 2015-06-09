#include "Posture.h"

namespace cor3d
{
    Posture::Posture(unsigned int id, string name, vector<Joint*>& joints): QObject(), BaseEntity(id, name)
    {
        _isEdited = false;
        _joints = joints;
        _selectedJoint = -1;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            _jointAbsolutePostureCoordinates.push_back(j->get_coordinates());
            _jointAbsoluteInitialPostureCoordinates.push_back(j->get_coordinates());
        }
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

    const DCoordinate3& Posture::getAbsolutePostureCoordinate(unsigned int jointId) const
    {
        return _jointAbsolutePostureCoordinates[jointId];
    }

    void Posture::MoveSelected(double x, double y, double z)
    {
        if (!_isEdited)
        {
            _isEdited = true;
            emit modelPostureIsEdited(this, _isEdited);
            constructChains(_selectedJoint);
        }

        DCoordinate3 target(x, y, z);
        FABRIK(_chains[0], target, 1e-10);
        for (unsigned int i = 1; i < _chains.size(); i++)
        {
            SimpleForwardFABRIK(&_chains[i], _chains[_chains[i].getChainParent()].get_chain_ending(), 1e-10);
        }
        FinalizeMove();
    }

    void Posture::FABRIK(Chain& chain, DCoordinate3 target, double tolerance)
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
        chain.add_joint_to_front(_jointAbsolutePostureCoordinates[get_joint(joint_id)->get_parent()], get_joint(get_joint(joint_id)->get_parent())->get_id());
        while(get_joint(joint_id)->get_children().size() == 1)
        {
            chain.add_joint_to_front(_jointAbsolutePostureCoordinates[joint_id], get_joint(joint_id)->get_id());
            joint_id = get_joint(joint_id)->get_children()[0];
        }
        chain.add_joint_to_front(_jointAbsolutePostureCoordinates[joint_id], get_joint(joint_id)->get_id());
        _chains.push_back(chain);
        vector<unsigned int> children = get_joint(joint_id)->get_children();
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
        if (selectedJoint >= 0)
        {
            Chain chain = Chain(0, -1, true);
            forward_chain(chain, selectedJoint);
            _chains.push_back(chain);
            vector<unsigned int> children = get_joint(selectedJoint)->get_children();
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
        while(get_joint(index)->get_parent() != -1 && get_joint(get_joint(index)->get_parent())->get_children().size() == 1)
        {
            index = get_joint(index)->get_parent();
        }
        if (get_joint(index)->get_parent() != -1)
        {
            chain.add_joint(_jointAbsolutePostureCoordinates[get_joint(index)->get_parent()], get_joint(get_joint(index)->get_parent())->get_id());
        }
        while (index != joint_id)
        {
            chain.add_joint(_jointAbsolutePostureCoordinates[index], get_joint(index)->get_id());
            index = get_joint(index)->get_children()[0];
        }
        chain.add_joint(_jointAbsolutePostureCoordinates[joint_id], get_joint(joint_id)->get_id());
    }

    void Posture::clearChains()
    {
        _chains.clear();
    }

    void Posture::handle_view_joint_fabrik_moved(const DCoordinate3& target)
    {
        MoveSelected(target.x(), target.y(), target.z());
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

        if (renderingOptions->get_render_joints() && joint_model)
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
                    glLoadName(joint->get_id() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }

    void Posture::renderPostureLinks(RenderingOptions* renderingOptions, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = renderingOptions->get_link_model();

        if (renderingOptions->get_render_links() && link_model &&_joints.size() > 1)
        {
            renderingOptions->get_material(renderingOptions->get_link_material())->Apply();

            for(unsigned int i = 1; i < _jointAbsoluteInitialPostureCoordinates.size(); i++)
            {
                Joint* joint = (Joint*) _joints[i];
                DCoordinate3 start = _jointAbsoluteInitialPostureCoordinates[joint->get_parent()];
                DCoordinate3 end = _jointAbsoluteInitialPostureCoordinates[joint->get_id()];
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

                DCoordinate3 jointScale = get_joint(joint->get_parent())->get_scale();
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

                    glPushMatrix();
                        glMultMatrixf(matrix);
                        glScalef(0.1, 0.1, length);
                        link_model->Render();
                    glPopMatrix();
                }
        }

    }

    Joint* Posture::get_joint(unsigned int index) const
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
        clearChains();
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsoluteInitialPostureCoordinates[i] = _jointAbsolutePostureCoordinates[i];
        }
    }

    void Posture::handleViewChangesCanceled()
    {
        _isEdited = false;
        clearChains();
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsolutePostureCoordinates[i] = _jointAbsoluteInitialPostureCoordinates[i];
        }
    }
}
