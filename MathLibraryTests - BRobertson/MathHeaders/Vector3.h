#pragma once
#include <string>
#include <cmath>


namespace MathClasses
{
    struct Vector3
    {
    public:

        Vector3() : x{0}, y{0}, z{0}
        {
        }

        Vector3(float _x, float _y, float _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        union
        {
            struct { float x, y, z; };
            struct { float r, g, b; };
            float data[3];
        };

        const float& operator [](int dim) const
        {
            return data[dim];
        }

        operator const float* () const { return data; }

        Vector3 operator +(const Vector3& rhs) const
        {
            Vector3 sum;
            sum.x = x + rhs.x;
            sum.y = y + rhs.y;
            sum.z = z + rhs.z;

            return sum;
        }

        Vector3 operator -(const Vector3& rhs) const
        {
            Vector3 subtract;
            subtract.x = x - rhs.x;
            subtract.y = y - rhs.y;
            subtract.z = z - rhs.z;

            return subtract;
        }

       


        bool operator == (const Vector3& rhs) const
        {
            float xDist = fabsf(x - rhs.x);
            float yDist = fabsf(y - rhs.y);
            float zDist = fabsf(z - rhs.z);

            const float THRESHOLD = 0.00001f;

            return xDist < THRESHOLD && yDist < THRESHOLD && zDist < THRESHOLD;

        }

        bool operator != (const Vector3& rhs) const
        {
            return !(*this == rhs);
        }

        float Magnitude() const
        {
            return sqrtf(x * x + y * y + z * z);

        }

        float MagnitudeSqr() const
        {
            return x * x + y * y + z * z;
        }

       
        void Normalise()
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                x /= m;
                y /= m;
                z /= m;
            }
        }

        Vector3 Normalised() const
        {
            float m = Magnitude();
            if (m != 0.0f)
            {
                return Vector3(x / m, y / m, z / m);
            }
            else
            {
                return Vector3();
            }
        }
        

        Vector3 operator*(float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        friend Vector3 operator*(float scalar, const Vector3& vec) {
            return vec * scalar;
        }

        float Dot(const Vector3& rhs)
        {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        Vector3 Vector3::Cross(const Vector3& rhs) const {
            return Vector3(y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x);
        }

        std::string ToString() const
        {
            return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
        }

        
    };
};