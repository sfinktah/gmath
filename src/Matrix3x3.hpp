/**
 *  ============================================================================
 *  MIT License
 *
 *  Copyright (c) 2016 Eric Phillips
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *  ============================================================================
 *
 *
 *  This file implements a series of math functions for manipulating a
 *  3x3 matrix.
 *
 *  Created by Eric Phillips on November 8, 2016.
 */

#pragma once

#include <math.h>



/**
 * Attempt to include a header file if the file exists.
 * If the file does not exist, create a dummy data structure for that type.
 * If it cannot be determined if it exists, just attempt to include it.
 */
#ifdef __has_include
#   if __has_include("Vector3.hpp")
#       include "Vector3.hpp"
#   else
        struct Vector3
        {
            union
            {
                struct
                {
                    double X;
                    double Y;
                    double Z;
                };
                double data[3];
            };

            inline Vector3() : X(0), Y(0), Z(0) {}
            inline Vector3(double data[]) : X(data[0]), Y(data[1]), Z(data[2])
                {}
            inline Vector3(double value) : X(value), Y(value), Z(value) {}
            inline Vector3(double x, double y) : X(x), Y(y), Z(0) {}
            inline Vector3(double x, double y, double z) : X(x), Y(y), Z(z) {}
        };
#   endif
#else
#   include "Vector3.hpp"
#endif


/**
 * Attempt to include a header file if the file exists.
 * If the file does not exist, create a dummy data structure for that type.
 * If it cannot be determined if it exists, just attempt to include it.
 */
#ifdef __has_include
#   if __has_include("Quaternion.hpp")
#       include "Quaternion.hpp"
#   else
        struct Quaternion
        {
            union
            {
                struct
                {
                    double X;
                    double Y;
                    double Z;
                    double W;
                };
                double data[4];
            };

            inline Quaternion() : X(0), Y(0), Z(0), W(1) {}
            inline Quaternion(double data[]) : X(data[0]), Y(data[1]),
                Z(data[2]), W(data[3]) {}
            inline Quaternion(Vector3 vector, double scalar) : X(vector.X),
                Y(vector.Y), Z(vector.Z), W(scalar) {}
            inline Quaternion(double x, double y, double z, double w) : X(x),
                Y(y), Z(z), W(w) {}
        };
#   endif
#else
#   include "Quaternion.hpp"
#endif


struct Matrix3x3
{
    union
    {
        struct
        {
            double D00;
            double D01;
            double D02;
            double D10;
            double D11;
            double D12;
            double D20;
            double D21;
            double D22;
        };
        double data[3][3];
    };


    /**
     * Constructors.
     */
    inline Matrix3x3();
    inline Matrix3x3(double data[]);
    inline Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2);
    inline Matrix3x3(double d00, double d01, double d02, double d10, double d11,
        double d12, double d20, double d21, double d22);


    /**
     * Constants for common Matrix3x3.
     */
    static inline Matrix3x3 Identity();
    static inline Matrix3x3 Zero();
    static inline Matrix3x3 One();


    /**
     * Converts a quaternion to a rotation matrix.
     * @param rotation: The input quaternion.
     * @return: A new rotation matrix.
     */
    static inline Matrix3x3 FromQuaternion(Quaternion rotation);

    /**
     * Returns the inverse of a matrix.
     * @param matrix: The input matrix.
     * @return: A new matrix.
     */
    static inline Matrix3x3 Inverse(Matrix3x3 matrix);

    /**
     * Returns true if a matrix is invertable.
     * @param matrix: The input matrix.
     * @return: A new matrix.
     */
    static inline bool IsInvertable(Matrix3x3 matrix);

    /**
     * Multiplies two matrices element-wise.
     * @param a: The left-hand side of the multiplication.
     * @param b: The right-hand side of the multiplication.
     * @return: A new matrix.
     */
    static inline Matrix3x3 Scale(Matrix3x3 a, Matrix3x3 b);

    /**
     * Converts a rotation matrix to a quaternion.
     * @param rotation: The input rotation matrix.
     * @return: A new quaternion.
     */
    static inline Quaternion ToQuaternion(Matrix3x3 rotation);

    /**
     * Returns the transpose of a matrix.
     * @param matrix: The input matrix.
     * @return: A new matrix.
     */
    static inline Matrix3x3 Transpose(Matrix3x3 matrix);

    /**
     * Operator overloading.
     */
    inline struct Matrix3x3& operator+=(const double rhs);
    inline struct Matrix3x3& operator-=(const double rhs);
    inline struct Matrix3x3& operator*=(const double rhs);
    inline struct Matrix3x3& operator/=(const double rhs);
    inline struct Matrix3x3& operator+=(const Matrix3x3 rhs);
    inline struct Matrix3x3& operator-=(const Matrix3x3 rhs);
    inline struct Matrix3x3& operator*=(const Matrix3x3 rhs);
};

inline Matrix3x3 operator-(Matrix3x3 rhs);
inline Matrix3x3 operator+(Matrix3x3 lhs, const double rhs);
inline Matrix3x3 operator-(Matrix3x3 lhs, const double rhs);
inline Matrix3x3 operator*(Matrix3x3 lhs, const double rhs);
inline Matrix3x3 operator/(Matrix3x3 lhs, const double rhs);
inline Matrix3x3 operator+(const double lhs, Matrix3x3 rhs);
inline Matrix3x3 operator-(const double lhs, Matrix3x3 rhs);
inline Matrix3x3 operator*(const double lhs, Matrix3x3 rhs);
inline Matrix3x3 operator+(Matrix3x3 lhs, const Matrix3x3 rhs);
inline Matrix3x3 operator-(Matrix3x3 lhs, const Matrix3x3 rhs);
inline Matrix3x3 operator*(Matrix3x3 lhs, const Matrix3x3 rhs);
inline Vector3 operator*(Matrix3x3 lhs, const Vector3 rhs);
inline bool operator==(const Matrix3x3 lhs, const Matrix3x3 rhs);
inline bool operator!=(const Matrix3x3 lhs, const Matrix3x3 rhs);



/*******************************************************************************
 * Implementation
 */

Matrix3x3::Matrix3x3() : D00(1), D01(0), D02(0), D10(0), D11(1), D12(0), D20(0),
    D21(0), D22(1) {}
Matrix3x3::Matrix3x3(double data[]) : D00(data[0]), D01(data[1]), D02(data[2]),
    D10(data[3]), D11(data[4]), D12(data[5]), D20(data[6]), D21(data[7]),
    D22(data[8]) {}
Matrix3x3::Matrix3x3(Vector3 row0, Vector3 row1, Vector3 row2) : D00(row0.X),
    D01(row0.Y), D02(row0.Z), D10(row1.X), D11(row1.Y), D12(row1.Z),
    D20(row2.X), D21(row2.Y), D22(row2.Z) {}
Matrix3x3::Matrix3x3(double d00, double d01, double d02, double d10, double d11,
    double d12, double d20, double d21, double d22) : D00(d00), D01(d01),
    D02(d02), D10(d10), D11(d11), D12(d12), D20(d20), D21(d21), D22(d22) {}


Matrix3x3 Matrix3x3::Identity()
{
    return Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

Matrix3x3 Matrix3x3::Zero()
{
    return Matrix3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

Matrix3x3 Matrix3x3::One()
{
    return Matrix3x3(1, 1, 1, 1, 1, 1, 1, 1, 1);
}


Matrix3x3 Matrix3x3::Scale(Matrix3x3 a, Matrix3x3 b)
{
    Matrix3x3 m;
    m.D00 = a.D00 * b.D00;
    m.D01 = a.D01 * b.D01;
    m.D02 = a.D02 * b.D02;
    m.D10 = a.D10 * b.D10;
    m.D11 = a.D11 * b.D11;
    m.D12 = a.D12 * b.D12;
    m.D20 = a.D20 * b.D20;
    m.D21 = a.D21 * b.D21;
    m.D22 = a.D22 * b.D22;
    return m;
}

Matrix3x3 Matrix3x3::Transpose(Matrix3x3 matrix)
{
    double tmp;
    tmp = matrix.D01;
    matrix.D01 = matrix.D10;
    matrix.D10 = tmp;
    tmp = matrix.D02;
    matrix.D02 = matrix.D20;
    matrix.D20 = tmp;
    tmp = matrix.D12;
    matrix.D12 = matrix.D21;
    matrix.D21 = tmp;
    return matrix;
}


struct Matrix3x3& Matrix3x3::operator+=(const double rhs)
{
    D00 += rhs; D01 += rhs; D02 += rhs;
    D10 += rhs; D11 += rhs; D12 += rhs;
    D20 += rhs; D21 += rhs; D22 += rhs;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator-=(const double rhs)
{
    D00 -= rhs; D01 -= rhs; D02 -= rhs;
    D10 -= rhs; D11 -= rhs; D12 -= rhs;
    D20 -= rhs; D21 -= rhs; D22 -= rhs;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator*=(const double rhs)
{
    D00 *= rhs; D01 *= rhs; D02 *= rhs;
    D10 *= rhs; D11 *= rhs; D12 *= rhs;
    D20 *= rhs; D21 *= rhs; D22 *= rhs;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator/=(const double rhs)
{
    D00 /= rhs; D01 /= rhs; D02 /= rhs;
    D10 /= rhs; D11 /= rhs; D12 /= rhs;
    D20 /= rhs; D21 /= rhs; D22 /= rhs;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator+=(const Matrix3x3 rhs)
{
    D00 += rhs.D00; D01 += rhs.D01; D02 += rhs.D02;
    D10 += rhs.D10; D11 += rhs.D11; D12 += rhs.D12;
    D20 += rhs.D20; D21 += rhs.D21; D22 += rhs.D22;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator-=(const Matrix3x3 rhs)
{
    D00 -= rhs.D00; D01 -= rhs.D01; D02 -= rhs.D02;
    D10 -= rhs.D10; D11 -= rhs.D11; D12 -= rhs.D12;
    D20 -= rhs.D20; D21 -= rhs.D21; D22 -= rhs.D22;
    return *this;
}

struct Matrix3x3& Matrix3x3::operator*=(const Matrix3x3 rhs)
{
    Matrix3x3 m;
    m.D00 = D00 * rhs.D00 + D01 * rhs.D10 + D02 * rhs.D20;
    m.D01 = D00 * rhs.D01 + D01 * rhs.D11 + D02 * rhs.D21;
    m.D02 = D00 * rhs.D02 + D01 * rhs.D12 + D02 * rhs.D22;
    m.D10 = D10 * rhs.D00 + D11 * rhs.D10 + D12 * rhs.D20;
    m.D11 = D10 * rhs.D01 + D11 * rhs.D11 + D12 * rhs.D21;
    m.D12 = D10 * rhs.D02 + D11 * rhs.D12 + D12 * rhs.D22;
    m.D20 = D20 * rhs.D00 + D21 * rhs.D10 + D22 * rhs.D20;
    m.D21 = D20 * rhs.D01 + D21 * rhs.D11 + D22 * rhs.D21;
    m.D22 = D20 * rhs.D02 + D21 * rhs.D12 + D22 * rhs.D22;
    *this = m;
    return *this;
}

Matrix3x3 operator-(Matrix3x3 rhs) { return rhs * -1; }
Matrix3x3 operator+(Matrix3x3 lhs, const double rhs) { return lhs += rhs; }
Matrix3x3 operator-(Matrix3x3 lhs, const double rhs) { return lhs -= rhs; }
Matrix3x3 operator*(Matrix3x3 lhs, const double rhs) { return lhs *= rhs; }
Matrix3x3 operator/(Matrix3x3 lhs, const double rhs) { return lhs /= rhs; }
Matrix3x3 operator+(const double lhs, Matrix3x3 rhs) { return rhs += lhs; }
Matrix3x3 operator-(const double lhs, Matrix3x3 rhs) { return rhs -= lhs; }
Matrix3x3 operator*(const double lhs, Matrix3x3 rhs) { return rhs *= lhs; }
Matrix3x3 operator+(Matrix3x3 lhs, const Matrix3x3 rhs) { return lhs += rhs; }
Matrix3x3 operator-(Matrix3x3 lhs, const Matrix3x3 rhs) { return lhs -= rhs; }
Matrix3x3 operator*(Matrix3x3 lhs, const Matrix3x3 rhs) { return lhs *= rhs; }

Vector3 operator*(Matrix3x3 lhs, const Vector3 rhs)
{
    Vector3 v;
    v.X = lhs.D00 * rhs.X + lhs.D01 * rhs.Y + lhs.D02 * rhs.Z;
    v.Y = lhs.D10 * rhs.X + lhs.D11 * rhs.Y + lhs.D12 * rhs.Z;
    v.Z = lhs.D20 * rhs.X + lhs.D21 * rhs.Y + lhs.D22 * rhs.Z;
    return v;
}

bool operator==(const Matrix3x3 lhs, const Matrix3x3 rhs)
{
    return lhs.D00 == rhs.D00 &&
        lhs.D01 == rhs.D01 &&
        lhs.D02 == rhs.D02 &&
        lhs.D10 == rhs.D10 &&
        lhs.D11 == rhs.D11 &&
        lhs.D12 == rhs.D12 &&
        lhs.D20 == rhs.D20 &&
        lhs.D21 == rhs.D21 &&
        lhs.D22 == rhs.D22;
}

bool operator!=(const Matrix3x3 lhs, const Matrix3x3 rhs)
{
    return !(lhs == rhs);
}