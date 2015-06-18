#include "Algorithm.h"

namespace cor3d {
    Algorithm::Algorithm(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoluteCoordinates, vector<DCoordinate3>& currentJointAbsoluteCoordinates):
    _joints(joints),
    _initialJointAbsoluteCoordinates(initialJointAbsoluteCoordinates),
    _currentJointAbsoluteCoordinates(currentJointAbsoluteCoordinates)
    {
        _isActive = false;
        _editRootJoint = -1;
        _currentRootJoint = -1;
        _lockedJoint = -1;
        _selectedJoint = -1;

        _loggingEnabled = true;
        _parallelProcessingEnabled = true;
    }

    bool Algorithm::moveToTarget(const DCoordinate3 target)
    {
        /*
        if (!_isActive || _joints.getSelectedEntity()->getId() != _selectedJoint)
        {
            constructChains(_joints.getSelectedEntity()->getId());

        }
        */
        clearChains();
        constructChains(_joints.getSelectedEntity()->getId());

        if (_chains.size() < 1 || _chains[0].get_chain_size() < 2)
        {
            _selectedJoint = -1;
            return false;
        }

        _selectedJoint = _joints.getSelectedEntity()->getId();
        _currentRootJoint = _chains[0].getJointId(_chains[0].get_chain_size() - 1);

        if (_editRootJoint == -1 || _currentRootJoint < _editRootJoint)
        {
            _editRootJoint = _currentRootJoint;
        }

        if (this->specificMoveToTarget(target))
        {
            _isActive = true;
            finalizeMove();
        }
        else
        {
            cout << "valami baj van" << endl;
        }

        return true;
    }

    void Algorithm::clearChains()
    {
        _chains.clear();
    }

    void Algorithm::constructChains(unsigned int selectedJoint)
    {

        cout << "construct chains" << endl;

        if (selectedJoint > 0)
        {
            Chain chain = Chain(0, -1, 0, true);
            forwardChain(chain, selectedJoint);
            _chains.push_back(chain);
            vector<unsigned int> children = static_cast<Joint*>(_joints[selectedJoint])->get_children();
            int chain_number = 1;
            for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
            {
                chain_number += _constructChains(*it, chain_number, 0);
            }
        }
    }

    int Algorithm::_constructChains(int jointId, int chainIndex, int parentChainIndex)
    {
        Chain chain = Chain(chainIndex, parentChainIndex, _chains[parentChainIndex].getChainHierarchyLevel() + 1, false);
        Joint* joint = static_cast<Joint*>(_joints[jointId]);
        unsigned int parentJointId = joint->get_parent();
        chain.add_joint_to_front(_initialJointAbsoluteCoordinates[parentJointId], parentJointId);
        while(joint->get_children().size() == 1)
        {
            chain.add_joint_to_front(_initialJointAbsoluteCoordinates[joint->getId()], joint->getId());
            joint = static_cast<Joint*>(_joints[joint->get_children()[0]]);
        }
        chain.add_joint_to_front(_initialJointAbsoluteCoordinates[joint->getId()], joint->getId());
        _chains.push_back(chain);
        vector<unsigned int> children = static_cast<Joint*>(_joints[joint->getId()])->get_children();
        int chain_number = 1;
        for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
        {
            chain_number += _constructChains(*it, chainIndex + chain_number, chainIndex);
        }
        return chain_number;
    }

    void Algorithm::forwardChain(Chain& chain, int joint_id)
    {
        int index = joint_id;
        while(static_cast<Joint*>(_joints[index])->get_parent() != -1 && static_cast<Joint*>(_joints[static_cast<Joint*>(_joints[index])->get_parent()])->get_children().size() == 1)
        {
            index = static_cast<Joint*>(_joints[index])->get_parent();
        }
        if (static_cast<Joint*>(_joints[index])->get_parent() != -1)
        {
            chain.add_joint(_initialJointAbsoluteCoordinates[static_cast<Joint*>(_joints[index])->get_parent()], static_cast<Joint*>(_joints[static_cast<Joint*>(_joints[index])->get_parent()])->getId());
        }
        while (index != joint_id)
        {
            chain.add_joint(_initialJointAbsoluteCoordinates[index], static_cast<Joint*>(_joints[index])->getId());
            index = static_cast<Joint*>(_joints[index])->get_children()[0];
        }
        chain.add_joint(_initialJointAbsoluteCoordinates[joint_id], static_cast<Joint*>(_joints[joint_id])->getId());
    }

    void Algorithm::finalizeMove()
    {
        for (unsigned int i = 0; i < _chains[0].get_chain_size(); i++)
        {
            _currentJointAbsoluteCoordinates[_chains[0].getJointId(i)] = _chains[0].get_joint_coordinates(i);
        }
        for (unsigned int i = 1; i < _chains.size(); i++)
        {
            for (unsigned int j = 0; j < _chains[i].get_chain_size(); j++)
            {
                _currentJointAbsoluteCoordinates[_chains[i].getJointId(j)] = _chains[i].get_joint_coordinates(j);
            }
        }
    }

    void Algorithm::renderChains(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->getLinkMesh();
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

                    DCoordinate3 jointScale = static_cast<Joint*>(_joints[(*it).getJointId(i)])->get_scale();
                    double scale = min(jointScale.x(), min(jointScale.y(), jointScale.z())) / 10.0;

                    glPushMatrix();
                        glMultMatrixf(matrix);
                        glScalef(scale, scale, length);
                        link_model->Render();
                    glPopMatrix();
                }
        }
    }
}
