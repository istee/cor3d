#pragma once

#include "../Core/DCoordinates3.h"

namespace cagd
{
    class Joint {
    private:
        DCoordinate3  _position;
        DCoordinate3  _orientation;
        DCoordinate3  _end_position;

        //Joint*              _parent;
        //uint              _child_count;
        //Vector<Joint*>    childs;
    public:
        /*Joint()
        {
            _position = HCoordinate3(0,0,0);
        }*/

        DCoordinate3 position() const;

    };

    DCoordinate3 Joint::position() const
    {
        return _position;
    }

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const Joint& rhs)
    {
        return lhs << rhs.position();
    }

    /*
    // input from stream
    inline std::istream& operator >>(std::istream& lhs, Joint& rhs)
    {
        return lhs >> rhs._position;
    }
    */
}
