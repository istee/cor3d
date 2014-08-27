#pragma once

#include <string>

using namespace std;

namespace cor3d {

    class BaseEntity
    {
        unsigned int    _id;
        string          _name;

    public:
        BaseEntity(unsigned int id, string name)
        {
            _id     = id;
            _name   = name;
        }

<<<<<<< HEAD
        // getter methods
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
        unsigned int get_id() const
        {
            return _id;
        }

        string get_name() const
        {
            return _name;
        }
<<<<<<< HEAD

        // setter methods
        void set_name(string name)
        {
            _name = name;
        }

        void decrease_id()
        {
            _id--;
        }
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    };
}
