#include "Joint.h"

using namespace std;

namespace cor3d {
    ostream& operator <<(ostream& lhs, const Joint& rhs)
    {
        lhs << "id: " << rhs.get_id() << ", parent: ";
        lhs << rhs._parent_id << ", ";
        for (vector<unsigned int>::const_iterator it = rhs._children_ids.begin(); it != rhs._children_ids.end(); it++)
        {
            lhs << *it << " ";
        }
        return lhs;
    }
}
