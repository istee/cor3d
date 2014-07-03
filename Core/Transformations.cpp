#include "Transformations.h"
#include <GL/glew.h>

namespace cagd
{
    Transformation::Transformation()
    {
        for (int i = 0; i < 16; ++i)
        {
            _mat[i] = (i % 5) ? 0.0 : 1.0;
        }
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

    DCoordinate3 Transformation::operator *(const DCoordinate3& rhs) const
    {
        double w = 0.0;

        for (int j = 0; j < 3; ++j)
        {
            w += _mat[3 + 4 * j] * rhs[j];
        }
        w += _mat[15];

        DCoordinate3 result;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                result[i] += _mat[i + 4 * j] * rhs[i];
            }
            result[i] += _mat[i + 12];
        }

        result /= w;

        return result;
    }

    void Transformation::Apply() const
    {
        glMultMatrixd(_mat);
    }
}
