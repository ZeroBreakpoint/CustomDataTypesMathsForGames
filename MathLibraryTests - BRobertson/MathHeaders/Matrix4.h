#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include <string>
#include <cmath>

namespace MathClasses
{
    struct Matrix4
    {
    public:
        union {
            struct {
                Vector4 xAxis;
                Vector4 yAxis;
                Vector4 zAxis;
                Vector4 translation;
                float m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16;

            };
            Vector4 axis[4];
            float data[4][4];
            float v[16];
        };

        
        Matrix4() :

            xAxis(1.0f, 0.0f, 0.0f, 0.0f),
            yAxis(0.0f, 1.0f, 0.0f, 0.0f),
            zAxis(0.0f, 0.0f, 1.0f, 0.0f),
            translation(0.0f, 0.0f, 0.0f, 1.0f),



            m1(0.0f), m2(0.0f), m3(0.0f),
            m4(0.0f), m5(0.0f), m6(0.0f),
            m7(0.0f), m8(0.0f), m9(0.0f),
            m10(0.0f), m11(0.0f), m12(0.0f),
            m13(0.0f), m14(0.0f), m15(0.0f),
            m16(0.0f)

        { }

				

        Matrix4(float _m1, float _m2, float _m3,
                float _m4, float _m5, float _m6,
                float _m7, float _m8, float _m9,
                float _m10, float _m11, float _m12,
                float _m13, float _m14, float _m15,
                float _m16)
            :
            
            m1(_m1), m2(_m2), m3(_m3), m4(_m4),
            m5(_m5), m6(_m6), m7(_m7), m8(_m8),
            m9(_m9), m10(_m10), m11(_m11), m12(_m12),
            m13(_m13), m14(_m14), m15(_m15), m16(_m16),


            xAxis(_m1, _m5, _m9, _m13),
            yAxis(_m2, _m6, _m10, _m14),
            zAxis(_m3, _m7, _m11, _m15),
            translation(_m4, _m8, _m12, _m16)

            

            { }

        Matrix4(const float* values)
        {
            for (int i = 0; i < 16; ++i)
            {
                int row = i % 4;
                int col = i / 4;
                data[row][col] = values[i];
            }

            m1 = data[0][0]; m2 = data[1][0]; m3 = data[2][0]; m4 = data[3][0];
            m5 = data[0][1]; m6 = data[1][1]; m7 = data[2][1]; m8 = data[3][1];
            m9 = data[0][2]; m10 = data[1][2]; m11 = data[2][2]; m12 = data[3][2];
            m13 = data[0][3]; m14 = data[1][3]; m15 = data[2][3]; m16 = data[3][3];

            xAxis = Vector4(data[0][0], data[0][1], data[0][2], data[0][3]);
            yAxis = Vector4(data[1][0], data[1][1], data[1][2], data[1][3]);
            zAxis = Vector4(data[2][0], data[2][1], data[2][2], data[2][3]);
            translation = Vector4(data[3][0], data[3][1], data[3][2], data[3][3]);

        }



        static Matrix4 MakeIdentity()
        {
            Matrix4 identity;
            identity.m1 = 1.0f;
            identity.m2 = 0.0f;
            identity.m3 = 0.0f;

            identity.m4 = 0.0f;
            identity.m5 = 0.0f;
            identity.m6 = 1.0f;

            identity.m7 = 0.0f;
            identity.m8 = 0.0f;
            identity.m9 = 0.0f;

            identity.m10 = 0.0f;
            identity.m11 = 1.0f;
            identity.m12 = 0.0f;

            identity.m13 = 0.0f;
            identity.m14 = 0.0f;
            identity.m15 = 0.0f;
            identity.m16 = 1.0f;

            return identity;

        }


        Vector4 operator*(const Vector4& vec) const
        {
            return Vector4(
                xAxis.Dot(vec),
                yAxis.Dot(vec),
                zAxis.Dot(vec),
                translation.Dot(vec)
            );
        }
        

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;

            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    float sum = 0.0f;
                    for (int k = 0; k < 4; ++k) {
                        sum += data[i][k] * other.data[k][j];
                    }
                    result.data[i][j] = sum;
                }
            }

            return result;
        }


        bool operator==(const Matrix4& rhs) const
        {
            const float THRESHOLD = 0.00001f;

            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    if (fabsf(data[i][j] - rhs.data[i][j]) > THRESHOLD)
                        return false;
                }
            }
            return true;
        }

        bool operator != (const Matrix4& rhs) const
        {
            return !(*this == rhs);
        }

        Matrix4 Transposed() const
        {
            return Matrix4(m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15, m4, m8, m12, m16);
        }

        std::string ToString() const {
            std::string str;
            for (int j = 0; j < 4; ++j) {
                for (int i = 0; i < 4; ++i) {
                    str += std::to_string(data[i][j]);
                    if (i != 3 || j != 3)
                        str += ", ";
                }
            }
            return str;
        }

        void Matrix4::setScaled(float x, float y, float z) {   
            xAxis = { x, 0, 0, 0 };
            yAxis = { 0, y, 0, 0 };
            zAxis = { 0, 0, z, 0 };
            translation = { 0, 0, 0, 1 };
        }

        void Matrix4::setRotateX(float radians) {
            xAxis = { 1, 0, 0, 0 };
            yAxis = { 0, cosf(radians), -sinf(radians), 0 };
            zAxis = { 0, sinf(radians), cosf(radians), 0 };
            translation = { 0, 0, 0, 1 };
        }

        void Matrix4::SetRotateY(float radians)
        {
            xAxis = { cosf(radians), 0, sinf(radians), 0 };
            yAxis = { 0, 1, 0, 0 };
            zAxis = { -sinf(radians), 0, cosf(radians), 0 };
            translation = { 0, 0, 0, 1 };
        }

        void Matrix4::SetRotateZ(float radians)
        {
            xAxis = { cosf(radians), sinf(radians), 0, 0 };
            yAxis = { -sinf(radians), cosf(radians), 0, 0 };
            zAxis = { 0, 0, 1, 0 };
            translation = { 0, 0, 0, 1 };
        }
        

        static Matrix4 MakeTranslation(float x, float y, float z)
        {
                return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 1.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 1.0f, 0.0f,
                               x, y, z, 1.0f);
        }

        static Matrix4 MakeTranslation(const Vector3& vec)
        {
                 return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 1.0f, 0.0f,
                                vec.x, vec.y, vec.z, 1.0f);

        }



        static Matrix4 MakeRotateX(float a)
        {
            return Matrix4(1, 0, 0, 0,
                           0, cosf(a), -sinf(a), 0,
                           0, sinf(a), cosf(a), 0,
                           0, 0, 0, 1);
        }

        static Matrix4 MakeRotateY(float a)
        {
            return Matrix4(cosf(a), 0, sinf(a), 0,
                           0, 1, 0, 0,
                           -sinf(a), 0, cosf(a), 0,
                           0, 0, 0, 1);
        }

        static Matrix4 MakeRotateZ(float a)
        {
            return Matrix4(cosf(a), sinf(a), 0, 0,
                          -sinf(a), cosf(a), 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
        }


        float Matrix4::Magnitude() const
        {
            return translation.Magnitude();
        }



        void Normalize()
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                xAxis /= m;
                yAxis /= m;
                zAxis /= m;
                translation /= m;
            }
        }


        static Matrix4 MakeEuler(float pitch, float yaw, float roll)
        {
            Matrix4 x = MakeRotateX(pitch);
            Matrix4 y = MakeRotateY(yaw);
            Matrix4 z = MakeRotateZ(roll);
            return z * y * x;
        }

        static Matrix4 MakeEuler(Vector3 rot)
        {
            return MakeEuler(rot.x, rot.y, rot.z);
        }

        static Matrix4 MakeScale(float xScale, float yScale, float zScale)
        {
                return Matrix4(xScale, 0.0f, 0.0f, 0.0f,
                               0.0f, yScale, 0.0f, 0.0f,
                               0.0f, 0.0f, zScale, 0.0f,
                               0.0f, 0.0f, 0.0f, 1.0f);
        }

        static Matrix4 MakeScale(const Vector3& scale)
        {
            return MakeScale(scale.x, scale.y, scale.z);
        }

    };
	}
