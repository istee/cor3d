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
        vector<DCoordinate3> _joints_coordinates;
    public:
        vector<int>  ids;
        Chain(int id, int parent_id, bool forward)
        {
            _id = id;
            _parent_id = parent_id;
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

        void add_joint(DCoordinate3 coordinates)
        {
            _joints_coordinates.push_back(coordinates);
        }

        void add_joint_to_front(DCoordinate3 coordinates)
        {
            _joints_coordinates.insert(_joints_coordinates.begin(), coordinates);
        }

        const DCoordinate3 get_joint_coordinates(int index) const
        {
            return _joints_coordinates[index];
        }

        void set_joint_coodinates(const DCoordinate3& coordinates, int index)
        {
            _joints_coordinates[index] = coordinates;
        }

        int get_chain_size() const
        {
            return _joints_coordinates.size();
        }

        friend std::ostream& operator <<(std::ostream& lhs, const Chain& rhs)
        {
            lhs << "Chain " << rhs._id << std::endl;
            lhs << "Parent chain " << rhs._parent_id << std::endl;
            for (int i = 0; i < rhs.get_chain_size(); i++)
            {
                lhs << rhs.get_joint_coordinates(i) << endl;
            }
            return lhs;
        }
    };
}
