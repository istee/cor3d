#include "Joint.h"

using namespace std;

namespace cor3d {
    void Joint::update_coordinates(const DCoordinate3& parent_coordinates)
    {
        _coordinate = parent_coordinates + _orientation;
    }

    ostream& operator <<(ostream& lhs, const Joint& rhs)
    {
        lhs << "joint_name: " << rhs.get_name() << endl;
        lhs << "joint_id: " << rhs.get_id() << endl;
        lhs << "joint_parent: " << rhs.get_parent() << endl;
        lhs << "joint_type: " << rhs.get_type() << endl;
        lhs << "joint_children_count: " << rhs.get_children().size() << endl;
        lhs << "joint_childrens: ";
        for (vector<unsigned int>::const_iterator it = rhs._children_ids.begin(); it != rhs._children_ids.end(); it++)
        {
            lhs << *it << " ";
        }
        lhs << endl << "joint_axis: " << rhs.get_axis() << endl;
        lhs << "joint_orientaion: " << rhs.get_orientation() << endl;
        lhs << "joint_configuration: " << rhs.get_configuration() << endl;
        return lhs;
    }

    istream& operator >>(istream& lhs, Joint& rhs)
    {
        string text;
        char name[256];
        int number, child;
        lhs >> text;
        cout << "text: " << text << endl;
        lhs.getline(name, 256);
        rhs.set_name(name);
        cout << "joint name: " << name << endl;
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
        lhs >> text >> rhs._axis;
        cout << text << " axis: " << rhs._axis << endl;
        lhs >> text >> rhs._orientation;
        lhs >> text >> rhs._configuration;
        cout << text << "orientation: " << rhs._orientation << endl;
        return lhs;
    }
}
