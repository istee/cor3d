#pragma once

#include <string>
#include <vector>

#include "BaseEntity.h"

#include "../Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

namespace cor3d {
    enum Type{ROTATIONAL, TRANSLATIONAL};

    class Joint: public BaseEntity {
        int                     _parent_id;
        vector<unsigned int>    _children_ids;
        Type                    _type;
        DCoordinate3            _axis;
        double                  _length;
        double                  _lower_limit;
        double                  _upper_limit;
        double                  _initial_joint_value;

    public:
        Joint(unsigned int id, string name, int parent_id): BaseEntity(id, name) { _parent_id = parent_id; }

        void set_parent(int parent_id)
        {
            _parent_id = parent_id;
        }

        int get_parent()
        {
            return _parent_id;
        }

        void add_children(int children_id)
        {
            _children_ids.push_back(children_id);
        }

        vector<unsigned int>& get_childrens()
        {
            return _children_ids;
        }

        void set_type(Type type)
        {
            _type = type;
        }

        Type get_type()
        {
            return _type;
        }

        void set_axis(double x, double y, double z)
        {
            _axis = DCoordinate3(x, y, z);
        }

        double get_axis_x()
        {
            return _axis.x();
        }

        double get_axis_y()
        {
            return _axis.y();
        }

        double get_axis_z()
        {
            return _axis.z();
        }

        void set_length(double length)
        {
            _length = length;
        }

        double get_length()
        {
            return _length;
        }

        void set_lower_limit(double limit)
        {
            _lower_limit = limit;
        }

        double get_lower_limit()
        {
            return _lower_limit;
        }

        void set_upper_limit(double limit)
        {
            _upper_limit = limit;
        }

        double get_upper_limit()
        {
            return _upper_limit;
        }

        void set_initial_joint_value(double value)
        {
            _initial_joint_value = value;
        }

        double get_initial_joint_value()
        {
            return _initial_joint_value;
        }
    };
}
