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

        unsigned int get_id() const
        {
            return _id;
        }

        string get_name() const
        {
            return _name;
        }
    };
}
