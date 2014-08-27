#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "BaseEntity.h"

#include "../Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

namespace cor3d {

    enum Type{ROTATIONAL = 0, TRANSLATIONAL = 1};

    class Joint: public BaseEntity {
        friend std::ostream& operator <<(std::ostream& lhs, const Joint& rhs);

        int                     _parent_id;
        vector<unsigned int>    _children_ids;
        Type                    _type;
        DCoordinate3            _axis;
        double                  _length;
        DCoordinate3            _coordinate;
        double                  _lower_limit;
        double                  _upper_limit;
        double                  _initial_value;

    public:
        Joint(unsigned int id, string name, int parent_id/*, DCoordinate3 parent_coordinate*/): BaseEntity(id, name)
        {
            _parent_id  = parent_id;
            _type       = ROTATIONAL;
            //_coordinate = parent_coordinate;
        }

        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        int get_parent() const
        {
            return _parent_id;
        }

        vector<unsigned int> get_children() const
        {
            return _children_ids;
        }

        Type get_type() const
        {
            return _type;
        }

        double get_axis_x() const
        {
            return _axis.x();
        }

        double get_axis_y() const
        {
            return _axis.y();
        }

        double get_axis_z() const
        {
            return _axis.z();
        }

        DCoordinate3 get_axis() const
        {
            return _axis;
        }

        double get_length() const
        {
            return _length;
        }

        DCoordinate3 get_coordinate() const
        {
            return _coordinate;
        }

        double get_lower_limit() const
        {
            return _lower_limit;
        }

        double get_upper_limit() const
        {
            return _upper_limit;
        }

        double get_initial_value() const
        {
            return _initial_value;
        }

        ///////////////////////////
        // setter methods        //
        ///////////////////////////
        void set_parent(int parent_id)
        {
            _parent_id = parent_id;
        }

        void add_child(unsigned int child_id)
        {
            _children_ids.push_back(child_id);
        }

        void remove_child(unsigned int child_id)
        {
            _children_ids.erase(std::remove(_children_ids.begin(), _children_ids.end(), child_id), _children_ids.end());
        }

        void set_type(Type type)
        {
            _type = type;
        }

        void set_axis(double x, double y, double z)
        {
            _axis = DCoordinate3(x, y, z);
        }

        void set_axis(const DCoordinate3& axis)
        {
            _axis = axis;
        }

        void set_length(double length)
        {
            _length = length;
        }

        void set_lower_limit(double limit)
        {
            _lower_limit = limit;
        }

        void set_upper_limit(double limit)
        {
            _upper_limit = limit;
        }

        void set_initial_value(double value)
        {
            _initial_value = value;
        }
    };
}
