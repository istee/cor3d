#pragma once

#include <vector>

#include "Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

namespace cor3d {
    class Chain
    {
        int _id;
        int _parent_id;
        bool _forward;
        unsigned int         _chainHierarchyLevel;
        vector<DCoordinate3> _joints_coordinates;
        vector<unsigned int> _jointIds;
    public:
        vector<int>  ids;
        Chain(int id, int parent_id, unsigned int chainHierarchyLevel, bool forward)
        {
            _id = id;
            _parent_id = parent_id;
            _chainHierarchyLevel = chainHierarchyLevel;
            _forward = forward;
        }
        DCoordinate3 get_chain_start()
        {
            return _forward ? _joints_coordinates[0] : _joints_coordinates[_joints_coordinates.size() - 1];
        }
        DCoordinate3 get_chain_ending()
        {
            return _forward ? _joints_coordinates[_joints_coordinates.size() - 1] : _joints_coordinates[0];
        }

        bool isForward() const
        {
            return _forward;
        }

        void add_joint(DCoordinate3 coordinates, unsigned int jointId)
        {
            _joints_coordinates.push_back(coordinates);
            _jointIds.push_back(jointId);
        }

        void add_joint_to_front(DCoordinate3 coordinates, unsigned int jointId)
        {
            _joints_coordinates.insert(_joints_coordinates.begin(), coordinates);
            _jointIds.insert(_jointIds.begin(), jointId);
        }

        DCoordinate3 get_joint_coordinates(int index) const
        {
            return _joints_coordinates[index];
        }

        unsigned int getJointId(int index) const
        {
            return _jointIds[index];
        }

        void set_joint_coordinates(const DCoordinate3& coordinates, int index)
        {
            _joints_coordinates[index] = coordinates;
        }

        int get_chain_size() const
        {
            return _joints_coordinates.size();
        }

        int getChainParent() const
        {
            return _parent_id;
        }

        unsigned int getChainHierarchyLevel()
        {
            return _chainHierarchyLevel;
        }

        friend std::ostream& operator <<(std::ostream& lhs, const Chain& rhs)
        {
            lhs << "Chain " << rhs._id << std::endl;
            lhs << "Parent chain " << rhs._parent_id << std::endl;
            lhs << "Chain size " << rhs.get_chain_size() << endl;
            for (int i = 0; i < rhs.get_chain_size(); i++)
            {
                lhs << rhs.getJointId(i) << " " << rhs.get_joint_coordinates(i) << endl;
            }
            return lhs;
        }
    };
}
