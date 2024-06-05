#pragma once
#include <string>
#include <cmath>

namespace MathClasses
{
    struct Vector4
    {
    public:

        Vector4() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }
        {
        }

        Vector4(float _x, float _y, float _z, float _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        union {
            struct { float x, y, z, w; };
            float data[4];
        };

         const float& operator [](int dim)
        {
            return data[dim];
        }  

        const float& operator [](int dim) const
        {
            return data[dim];
        }

        operator const float* () const { return data; }

        Vector4& operator+=(const Vector4& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        Vector4& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
            return *this;
        }

        Vector4 operator*(const Vector4& rhs) const
        {
            return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }


        Vector4 operator +(const Vector4& rhs)
        {
			  Vector4 sum;
              sum.x = x + rhs.x;
			  sum.y = y + rhs.y;
              sum.z = z + rhs.z;
              sum.w = w + rhs.w;

              return sum;
        }

        Vector4 operator -(const Vector4& rhs)
        {
              Vector4 subtract;
              subtract.x = x - rhs.x;
              subtract.y = y - rhs.y;
              subtract.z = z - rhs.z;
              subtract.w = w - rhs.w;

              return subtract;
        }


        bool operator == (const Vector4& rhs) const
        {
            float xDist = fabsf(x - rhs.x);
            float yDist = fabsf(y - rhs.y);
            float zDist = fabsf(z - rhs.z);
            float wDist = fabsf(w - rhs.w);

            const float THRESHOLD = 0.00001f;

            return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD;

        }

        bool operator != (const Vector4& rhs) const
        {
            return !(*this == rhs);
        }

        float Magnitude() const
        {
            return sqrtf(x * x + y * y + z * z + w * w);
        }

        float MagnitudeSqr() const
        {
            return x * x + y * y + z * z + w * w;
        }

        void Normalise()
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                x /= m;
                y /= m;
                z /= m;
                w /= m;
            }
        }

        Vector4 Normalised() const
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                return Vector4(x / m, y / m, z / m, w / m);
            }
            else
            {
                return Vector4();
            }
        }

        Vector4 operator*(float scalar) const {
            return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        friend Vector4 operator*(float scalar, const Vector4& vec) {
            return vec * scalar;
        }

        float Vector4::Dot(const Vector4& rhs) const {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }

        Vector4 Vector4::Cross(const Vector4& rhs)
        {
            return Vector4(y * rhs.z - z * rhs.y,
                           z * rhs.x - x * rhs.z,
                           x * rhs.y - y * rhs.x,
                           0);
        }

        std::string ToString() const
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
        }

    };
}