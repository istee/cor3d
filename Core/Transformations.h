#pragma once

#include "RealSquareMatrices.h"
#include "DCoordinates3.h"
#include "HCoordinates3.h"

namespace cagd
{
    class Transformation
    {

        friend Transformation operator *(const double& lhs, const Transformation& rhs);
        friend std::ostream& operator <<(std::ostream& lhs, const Transformation& rhs);

    protected:
        double _mat[16];

    public:
        Transformation(); // identity matrix

        Transformation(const double mat[16]);

        void LoadNullMatrix();
        void LoadIdentityMatrix();

        Transformation Transpose() const;

        double operator ()(int row, int column) const;
        double& operator ()(int row, int column);

        Transformation operator *(const Transformation& rhs) const;
        Transformation& operator *=(const Transformation& rhs);

        Transformation operator +(const Transformation& rhs) const;
        Transformation& operator +=(const Transformation& rhs);

        Transformation operator -(const Transformation& rhs) const;
        Transformation& operator -=(const Transformation& rhs);

        Transformation operator *(const double& rhs) const;
        Transformation& operator *=(const double& rhs);

        DCoordinate3 operator *(const DCoordinate3& rhs) const;
        HCoordinate3 operator *(const HCoordinate3& rhs) const;

        bool GetInverse(Transformation& inverse) const;

        void Apply() const;
    };

    Transformation operator *(const double& lhs, const Transformation& rhs);

    // p. 39
    class Rotation: public Transformation
    {
    public:
        Rotation();
        Rotation(double degree, DCoordinate3& axis);
    };

    class Scale: public Transformation
    {
    public:
        Scale(double s_x, double s_y, double s_z);
    };

    // p. 26
    class Translate: public Transformation
    {
    public:
        Translate(double t_x, double t_y, double t_z);
    };
}
