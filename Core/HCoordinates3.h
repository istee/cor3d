#pragma once

#ifndef __HCoordinates_H_INCLUDED__
#define __HCoordinates_H_INCLUDED__

#include <cmath>
#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //--------------------------------------
    // 3-dimensional homogeneous coordinates
    //--------------------------------------
    class HCoordinate3
    {
    protected:
        GLfloat _data[4]; // x, y, z, w;

    public:
        // default constructor
        HCoordinate3();

        // special constructor
        HCoordinate3(GLfloat x, GLfloat y, GLfloat z = 0.0, GLfloat w = 1.0);

        // homework: get components by value
        GLfloat operator[](GLuint rhs) const;
        GLfloat x() const;
        GLfloat y() const;
        GLfloat z() const;
        GLfloat w() const;

        // homework: get components by reference
        GLfloat& operator[](GLuint rhs);
        GLfloat& x();
        GLfloat& y();
        GLfloat& z();
        GLfloat& w();

        // add
        const HCoordinate3 operator +(const HCoordinate3& rhs) const;

        // homework: add to this
        HCoordinate3& operator +=(const HCoordinate3& rhs);

        // homework: subtract
        const HCoordinate3 operator -(const HCoordinate3& rhs) const;

        // homework: subtract from this
        HCoordinate3& operator -=(const HCoordinate3& rhs);

        // homework: dot product
        GLfloat operator *(const HCoordinate3& rhs) const;

        // homework: cross product
        const HCoordinate3 operator ^(const HCoordinate3& rhs) const;

        // homework: cross product with this
        HCoordinate3& operator ^=(const HCoordinate3& rhs);

        // homework: multiplicate with scalar from right
        const HCoordinate3 operator *(GLfloat rhs) const;

        // homework: multiplicate this with a scalar
        HCoordinate3& operator *=(GLfloat rhs);

        // homework: divide with scalar
        const HCoordinate3 operator /(GLfloat rhs) const;

        // homework: divide this with a scalar
        HCoordinate3& operator /=(GLfloat rhs);

        // homework: length of vector represented by this homogeneous coordinate
        GLfloat length() const;

        // homework: normalize
        HCoordinate3& normalize();
    };

    // default constructor
    inline HCoordinate3::HCoordinate3()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
        _data[3] = 1.0;
    }

    // special constructor
    inline HCoordinate3::HCoordinate3(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    }

    // add
    inline const HCoordinate3 HCoordinate3::operator +(const HCoordinate3& rhs) const
    {
        return HCoordinate3(
                rhs.w() * x() + w() * rhs.x(),
                rhs.w() * y() + w() * rhs.y(),
                rhs.w() * z() + w() * rhs.z(),
                w() * rhs.w());
    }

    // scale from left with a scalar
    inline const HCoordinate3 operator *(GLfloat lhs, const HCoordinate3& rhs)
    {
        return HCoordinate3(rhs.x()*lhs, rhs.y()*lhs, rhs.z()*lhs, rhs.w());
    }

    // output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const HCoordinate3& rhs)
    {
        return lhs << rhs[0] << " " << rhs[1] << " " << rhs[2] << " " << rhs[3];
    }

    // input from stream
    inline std::istream& operator >>(std::istream& lhs, HCoordinate3& rhs)
    {
        return lhs >> rhs[0] >> rhs[1] >> rhs[2] >> rhs[3];
    }

    // get components by value
    GLfloat HCoordinate3::operator[](GLuint rhs) const
    {
        return _data[rhs];
    }

    GLfloat HCoordinate3::x() const
    {
        return _data[0];
    }

    GLfloat HCoordinate3::y() const
    {
        return _data[1];
    }

    GLfloat HCoordinate3::z() const
    {
        return _data[2];
    }

    GLfloat HCoordinate3::w() const
    {
        return _data[3];
    }

    // get components by reference
    GLfloat& HCoordinate3::operator[](GLuint rhs)
    {
        return _data[rhs];
    }

    GLfloat& HCoordinate3::x()
    {
        return _data[0];
    }

    GLfloat& HCoordinate3::y()
    {
        return _data[1];
    }

    GLfloat& HCoordinate3::z()
    {
        return _data[2];
    }

    GLfloat& HCoordinate3::w()
    {
        return _data[3];
    }

    // add to this
    HCoordinate3& HCoordinate3::operator +=(const HCoordinate3& rhs)
    {
        x() += rhs.w() * x() + w() * rhs.x();
        y() += rhs.w() * y() + w() * rhs.y();
        z() += rhs.w() * z() + w() * rhs.z();
        w() = w() * rhs.w();

        return *this;
    }

    // subtract
    const HCoordinate3 HCoordinate3::operator -(const HCoordinate3& rhs) const
    {
        return HCoordinate3(rhs.w() * x() - w() * rhs.x(),
                    rhs.w() * y() - w() * rhs.y(),
                    rhs.w() * z() - w() * rhs.z(),
                    w() * rhs.w());
    }

    // subtract from this
    HCoordinate3& HCoordinate3::operator -=(const HCoordinate3& rhs)
    {
        x() -= rhs.w() * x() + w() * rhs.x();
        y() -= rhs.w() * y() + w() * rhs.y();
        z() -= rhs.w() * z() + w() * rhs.z();
        w() = w() * rhs.w();

        return *this;
    }

    // dot product
    GLfloat HCoordinate3::operator *(const HCoordinate3& rhs) const
    {
        return rhs.w() * x() * w() * rhs.x() +
                rhs.w() * y() * w() * rhs.y() +
                rhs.w() * z() * w() * rhs.z();
    }

    // cross product
    const HCoordinate3 HCoordinate3::operator ^(const HCoordinate3& rhs) const
    {
        return HCoordinate3(y() * rhs.w() * rhs.z() * w() - z() * rhs.w() * rhs.y() * w(),
                            z() * rhs.w() * rhs.x() * w() - x() * rhs.w() * rhs.z() * w(),
                            x() * rhs.w() * rhs.y() * w() - y() * rhs.w() * rhs.x() * w(),
                            w() * rhs.w());
    }

    // cross product with this
    HCoordinate3& HCoordinate3::operator ^=(const HCoordinate3& rhs)
    {
        HCoordinate3 temp = HCoordinate3();
        temp.x() = y() * rhs.w() * rhs.z() * w() - z() * rhs.w() * rhs.y() * w();
        temp.y() = z() * rhs.w() * rhs.x() * w() - x() * rhs.w() * rhs.z() * w();
        temp.z() = x() * rhs.w() * rhs.y() * w() - y() * rhs.w() * rhs.x() * w();
        temp.w() = w() * rhs.w();

        x() = temp.x();
        y() = temp.y();
        z() = temp.z();
        w() = temp.w();

        return *this;
    }

    // multiplicate with scalar from right
    const HCoordinate3 HCoordinate3::operator *(GLfloat rhs) const
    {
        return HCoordinate3(x() * rhs, y() * rhs, z() * rhs, w());
    }

    // multiplicate this with a scalar
    HCoordinate3& HCoordinate3::operator *=(GLfloat rhs)
    {
        x() *= rhs;
        y() *= rhs;
        z() *= rhs;

        return *this;
    }

    // divide with scalar
    const HCoordinate3 HCoordinate3::operator /(GLfloat rhs) const
    {
        return HCoordinate3(x() / rhs, y() / rhs, z() / rhs, w());
    }

    // divide this with a scalar
    HCoordinate3& HCoordinate3::operator /=(GLfloat rhs)
    {
        x() /= rhs;
        y() /= rhs;
        z() /= rhs;

        return *this;
    }

    // length of vector represented by this homogeneous coordinate
    GLfloat HCoordinate3::length() const
    {
        return sqrt(x()*x() + y()*y() + z()*z());
    }

    // normalize
    HCoordinate3& HCoordinate3::normalize()
    {
        GLfloat len = length();
        this->operator /=(len);
        return *this;
    }
}

#endif // __HCoordinates_H_INCLUDED__
