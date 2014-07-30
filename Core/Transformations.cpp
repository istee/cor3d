#include "Transformations.h"
#include <GL/glew.h>

namespace cagd
{
    Transformation::Transformation()
    {
        LoadIdentityMatrix();
    }

    Transformation::Transformation(const double mat[])
    {
        for (int i = 0; i < 16; ++i)
        {
            _mat[i] = mat[i];
        }
    }

    void Transformation::LoadNullMatrix()
    {
        for (int i = 0; i < 16; ++i)
        {
            _mat[i] = 0.0;
        }
    }

    void Transformation::LoadIdentityMatrix()
    {
        for (int i = 0; i < 16; ++i)
        {
            _mat[i] = (i % 5) ? 0.0 : 1.0;
        }
    }

    Transformation Transformation::Transpose() const
    {
        double transpose[16];

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                transpose[i + 4 * j] = _mat[j + 4 * i];
            }
        }

        return Transformation(transpose);
    }

    double Transformation::operator ()(int row, int column) const
    {
        return _mat[row * 4 + column];
    }

    double& Transformation::operator ()(int row, int column)
    {
        return _mat[row * 4 + column];
    }

    Transformation Transformation::operator *(const Transformation& rhs) const
    {
        Transformation result;
        result.LoadNullMatrix();

        for (unsigned int i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; j < 4; ++j)
            {
                for (unsigned int k = 0; k < 4; ++k)
                {
                    result._mat[i * 4 + j] += _mat[i * 4 + k] * rhs._mat[k * 4 + j];
                }
            }
        }

        return result;
    }

    Transformation& Transformation::operator *=(const Transformation& rhs)
    {
        double result[16];
        for (unsigned int i = 0; i < 16; ++i)
        {
            result[i] = 0.0;
        }

        for (unsigned int i = 0; i < 16; i+=4)
        {
            for (unsigned int j = 0; j < 16; j+=4)
            {
                for (unsigned int k = 0; k < 16; ++k)
                {
                    result[i * 4 + j] += _mat[i * 4 + k] * rhs._mat[k * 4 + j];
                }
            }
        }

        for (unsigned int i = 0; i < 16; ++i)
        {
            _mat[i] = result[i];
        }

        return *this;
    }

    Transformation Transformation::operator +(const Transformation& rhs) const
    {
        Transformation result;

        for (unsigned int i = 0; i < 16; i++)
        {
            result._mat[i] = _mat[i] + rhs._mat[i];
        }

        return result;
    }

    Transformation& Transformation::operator +=(const Transformation& rhs)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            _mat[i] += rhs._mat[i];
        }

        return *this;
    }

    Transformation Transformation::operator -(const Transformation& rhs) const
    {
        Transformation result;

        for (unsigned int i = 0; i < 16; i++)
        {
            result._mat[i] = _mat[i] - rhs._mat[i];
        }

        return result;
    }

    Transformation& Transformation::operator -=(const Transformation& rhs)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            _mat[i] -= rhs._mat[i];
        }

        return *this;
    }

    Transformation Transformation::operator *(const double& rhs) const
    {
        Transformation result;

        for (unsigned int i = 0; i < 16; i++)
        {
            result._mat[i] = _mat[i] * rhs;
        }

        return result;
    }

    Transformation& Transformation::operator *=(const double& rhs)
    {
        for (unsigned int i = 0; i < 16; i++)
        {
            _mat[i] *= rhs;
        }

        return *this;
    }

    DCoordinate3 Transformation::operator *(const DCoordinate3& rhs) const
    {
        double w = 0.0;

        for (int j = 0; j < 3; ++j)
        {
            w += _mat[3 + 4 * j] * rhs[j];
        }
        w += _mat[15];
        //std::cout << "w: " << w << std::endl;

        DCoordinate3 result;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result[i] += _mat[i + 4 * j] * rhs[j];
            }
            result[i] += _mat[i + 12];
        }

        result /= w;

        return result;
    }

    HCoordinate3 Transformation::operator *(const HCoordinate3& rhs) const
    {
        HCoordinate3 result;
        result[3] = 0.0;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result[i] += _mat[i * 4 + j] * rhs[j];
            }
        }

        for (unsigned int i = 0; i < 3; ++i)
        {
            result[i] /= result[3];
        }
        result[3] = 1.0;

        return result;
    }

    bool Transformation::GetInverse(Transformation &inverse) const
    {
        inverse.LoadNullMatrix();


        double inv[16], det;
        int i;

        inv[0] = _mat[5]  * _mat[10] * _mat[15] -
                 _mat[5]  * _mat[11] * _mat[14] -
                 _mat[9]  * _mat[6]  * _mat[15] +
                 _mat[9]  * _mat[7]  * _mat[14] +
                 _mat[13] * _mat[6]  * _mat[11] -
                 _mat[13] * _mat[7]  * _mat[10];

        inv[4] = -_mat[4]  * _mat[10] * _mat[15] +
                 _mat[4]  * _mat[11] * _mat[14] +
                 _mat[8]  * _mat[6]  * _mat[15] -
                 _mat[8]  * _mat[7]  * _mat[14] -
                 _mat[12] * _mat[6]  * _mat[11] +
                 _mat[12] * _mat[7]  * _mat[10];

        inv[8] = _mat[4]  * _mat[9] * _mat[15] -
                 _mat[4]  * _mat[11] * _mat[13] -
                 _mat[8]  * _mat[5] * _mat[15] +
                 _mat[8]  * _mat[7] * _mat[13] +
                 _mat[12] * _mat[5] * _mat[11] -
                 _mat[12] * _mat[7] * _mat[9];

        inv[12] = -_mat[4]  * _mat[9] * _mat[14] +
                  _mat[4]  * _mat[10] * _mat[13] +
                  _mat[8]  * _mat[5] * _mat[14] -
                  _mat[8]  * _mat[6] * _mat[13] -
                  _mat[12] * _mat[5] * _mat[10] +
                  _mat[12] * _mat[6] * _mat[9];

        inv[1] = -_mat[1]  * _mat[10] * _mat[15] +
                 _mat[1]  * _mat[11] * _mat[14] +
                 _mat[9]  * _mat[2] * _mat[15] -
                 _mat[9]  * _mat[3] * _mat[14] -
                 _mat[13] * _mat[2] * _mat[11] +
                 _mat[13] * _mat[3] * _mat[10];

        inv[5] = _mat[0]  * _mat[10] * _mat[15] -
                 _mat[0]  * _mat[11] * _mat[14] -
                 _mat[8]  * _mat[2] * _mat[15] +
                 _mat[8]  * _mat[3] * _mat[14] +
                 _mat[12] * _mat[2] * _mat[11] -
                 _mat[12] * _mat[3] * _mat[10];

        inv[9] = -_mat[0]  * _mat[9] * _mat[15] +
                 _mat[0]  * _mat[11] * _mat[13] +
                 _mat[8]  * _mat[1] * _mat[15] -
                 _mat[8]  * _mat[3] * _mat[13] -
                 _mat[12] * _mat[1] * _mat[11] +
                 _mat[12] * _mat[3] * _mat[9];

        inv[13] = _mat[0]  * _mat[9] * _mat[14] -
                  _mat[0]  * _mat[10] * _mat[13] -
                  _mat[8]  * _mat[1] * _mat[14] +
                  _mat[8]  * _mat[2] * _mat[13] +
                  _mat[12] * _mat[1] * _mat[10] -
                  _mat[12] * _mat[2] * _mat[9];

        inv[2] = _mat[1]  * _mat[6] * _mat[15] -
                 _mat[1]  * _mat[7] * _mat[14] -
                 _mat[5]  * _mat[2] * _mat[15] +
                 _mat[5]  * _mat[3] * _mat[14] +
                 _mat[13] * _mat[2] * _mat[7] -
                 _mat[13] * _mat[3] * _mat[6];

        inv[6] = -_mat[0]  * _mat[6] * _mat[15] +
                 _mat[0]  * _mat[7] * _mat[14] +
                 _mat[4]  * _mat[2] * _mat[15] -
                 _mat[4]  * _mat[3] * _mat[14] -
                 _mat[12] * _mat[2] * _mat[7] +
                 _mat[12] * _mat[3] * _mat[6];

        inv[10] = _mat[0]  * _mat[5] * _mat[15] -
                  _mat[0]  * _mat[7] * _mat[13] -
                  _mat[4]  * _mat[1] * _mat[15] +
                  _mat[4]  * _mat[3] * _mat[13] +
                  _mat[12] * _mat[1] * _mat[7] -
                  _mat[12] * _mat[3] * _mat[5];

        inv[14] = -_mat[0]  * _mat[5] * _mat[14] +
                  _mat[0]  * _mat[6] * _mat[13] +
                  _mat[4]  * _mat[1] * _mat[14] -
                  _mat[4]  * _mat[2] * _mat[13] -
                  _mat[12] * _mat[1] * _mat[6] +
                  _mat[12] * _mat[2] * _mat[5];

        inv[3] = -_mat[1] * _mat[6] * _mat[11] +
                 _mat[1] * _mat[7] * _mat[10] +
                 _mat[5] * _mat[2] * _mat[11] -
                 _mat[5] * _mat[3] * _mat[10] -
                 _mat[9] * _mat[2] * _mat[7] +
                 _mat[9] * _mat[3] * _mat[6];

        inv[7] = _mat[0] * _mat[6] * _mat[11] -
                 _mat[0] * _mat[7] * _mat[10] -
                 _mat[4] * _mat[2] * _mat[11] +
                 _mat[4] * _mat[3] * _mat[10] +
                 _mat[8] * _mat[2] * _mat[7] -
                 _mat[8] * _mat[3] * _mat[6];

        inv[11] = -_mat[0] * _mat[5] * _mat[11] +
                  _mat[0] * _mat[7] * _mat[9] +
                  _mat[4] * _mat[1] * _mat[11] -
                  _mat[4] * _mat[3] * _mat[9] -
                  _mat[8] * _mat[1] * _mat[7] +
                  _mat[8] * _mat[3] * _mat[5];

        inv[15] = _mat[0] * _mat[5] * _mat[10] -
                  _mat[0] * _mat[6] * _mat[9] -
                  _mat[4] * _mat[1] * _mat[10] +
                  _mat[4] * _mat[2] * _mat[9] +
                  _mat[8] * _mat[1] * _mat[6] -
                  _mat[8] * _mat[2] * _mat[5];

        det = _mat[0] * inv[0] + _mat[1] * inv[4] + _mat[2] * inv[8] + _mat[3] * inv[12];

        if (det == 0)
            return false;

        det = 1.0 / det;

        for (i = 0; i < 16; i++)
            inverse._mat[i] = inv[i] * det;

        return true;
    }

    void Transformation::Apply() const
    {
        glMultMatrixd(_mat);
    }

    Rotation::Rotation(): Transformation()
    {

    }

    Rotation::Rotation(double degree, DCoordinate3& axis)
    {
        double radian = degree * PI / 180.0;
        double cosine = cos(radian);
        double sine = sin(radian);

        _mat[0] = 1 + (axis[1] * axis[1]  + axis[2] * axis[2]) * (cosine - 1);
        _mat[1] = axis[0] * axis[1] * (1 - cosine) - axis[2] * sine;
        _mat[2] = axis[1] * sine + (1 - cosine) * axis[0] * axis[2];
        _mat[3] = 0.0;

        _mat[4] = axis[2] * sine - axis[0] * axis[1] * (1 - cosine);
        _mat[5] = 1 + (axis[0] * axis[0] + axis[2] * axis[2]) * (cosine - 1);
        _mat[6] = -axis[0] * sine - (1 - cosine) * axis[1] * axis[2];
        _mat[7] = 0.0;

        _mat[8] = -axis[1] * sine + (1 - cosine) * axis[0] * axis[2];
        _mat[9] = axis[0] * sine + (1 - cosine) * axis[1] * axis[2];
        _mat[10] = 1 + (axis[0] * axis[0] + axis[1] * axis[1]) * (cosine - 1);
        _mat[11] = 0.0;

        _mat[12] = 0.0;
        _mat[13] = 0.0;
        _mat[14] = 0.0;
        _mat[15] = 1.0;
    }

    Translate::Translate(): Transformation()
    {

    }

    Translate::Translate(double t_x, double t_y, double t_z): Transformation()
    {
        _mat[12] = t_x;
        _mat[13] = t_y;
        _mat[14] = t_z;
    }

    // output to stream
    std::ostream& operator <<(std::ostream& lhs, const Transformation& rhs)
    {
        lhs << "Transformation" << std::endl;
        for (unsigned int i = 0; i < 16; ++i)
        {
            lhs << rhs._mat[i];
            if ((i + 1) % 4 == 0)
            {
                lhs << std::endl;
            }
            else
            {
                lhs << ", ";
            }
        }
        lhs << std::endl;
     }
}
