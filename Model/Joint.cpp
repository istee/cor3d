#include "Joint.h"

using namespace std;

namespace cor3d {
    void Joint::update_coordinates(const DCoordinate3& parent_coordinates)
    {
        _coordinate = parent_coordinates + _orientation;
    }

    ostream& operator <<(ostream& lhs, const Joint& rhs)
    {
        lhs << "joint_name:" << endl << rhs.getName() << endl;
        lhs << "joint_id: " << rhs.getId() << endl;
        lhs << "joint_parent: " << rhs.get_parent() << endl;
        lhs << "joint_type: " << rhs.get_type() << endl;
        lhs << "joint_children_count: " << rhs.get_children().size() << endl;
        lhs << "joint_childrens: ";
        for (vector<unsigned int>::const_iterator it = rhs._children_ids.begin(); it != rhs._children_ids.end(); it++)
        {
            lhs << *it << " ";
        }
        lhs << endl << "joint_coordinates: " << rhs.get_coordinates() << endl;
        lhs << "_joint_parent_relative_coordinates: " << rhs.get_orientation() << endl;
        lhs << "joint_scale: " << rhs.get_scale() << endl;
        return lhs;
    }

    istream& operator >>(istream& lhs, Joint& rhs)
    {
        string text;
        char name[256];
        int number, child;
        lhs >> text;
        lhs.getline(name, 256);
        lhs.getline(name, 256);
        rhs.setName(name);
        lhs >> text >> rhs._id;
        lhs >> text >> rhs._parent_id;
        lhs >> text >> number;
        rhs._type = (Type) number;
        lhs >> text >> number >> text;
        for (int i = 0; i < number; i++)
        {
            lhs >> child;
            rhs._children_ids.push_back(child);
        }
        lhs >> text >> rhs._coordinate;
        lhs >> text >> rhs._orientation;
        lhs >> text >> rhs._scale;
        return lhs;
    }
}
