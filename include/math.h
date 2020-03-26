#ifndef BERRY3D_MATH_H
#define BERRY3D_MATH_H

#include <cmath>

namespace Berry3D {
    float sqrt(float);
    class Vector2 {
    public:
        Vector2(float a = 0, float b = 0) : x(a), y(b) { }
        Vector2(const Vector2& vector2) : x(vector2.x), y(vector2.y) { }
        Vector2 operator-() const { return Vector2(-x, -y); }
        float x, y;
    };
#define POW(n) (n * n)
    class Vector3 {
    public:
        Vector3(float a = 0, float b = 0, float c = 0) : x(a), y(b), z(c) { }
        Vector3(const Vector3& vector3) : x(vector3.x), y(vector3.y), z(vector3.z) { }
#define MATH_VEC_OP(NAME, OP) NAME OP vector3.NAME
        Vector3 operator+(const Vector3& vector3) const { return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);}
        Vector3& operator+=(const Vector3& vector3) {
            MATH_VEC_OP(x, +=);
            MATH_VEC_OP(y, +=);
            MATH_VEC_OP(z, +=);
            return *this;
        }
        Vector3& operator-=(const Vector3& vector3) {
            MATH_VEC_OP(x, -=);
            MATH_VEC_OP(y, -=);
            MATH_VEC_OP(z, -=);
            return *this;
        }
        Vector3 operator-(const Vector3& vector3) const { return Vector3(x - vector3.x, y - vector3.y, z - vector3.z);}
        Vector3 operator-() const { return Vector3(-x, -y, -z); }
        // 点积
        float operator*(const Vector3& vector3) const {
            return MATH_VEC_OP(x, *) + MATH_VEC_OP(y, *) + MATH_VEC_OP(y, *);
        }
        // 向量积
        Vector3 operator%(const Vector3& vector3) const { return Vector3(MATH_VEC_OP(x, *), MATH_VEC_OP(y, *), MATH_VEC_OP(y, *)); }
        Vector3& operator%=(const Vector3& vector3) {
            MATH_VEC_OP(x, *=);
            MATH_VEC_OP(y, *=);
            MATH_VEC_OP(z, *=);
            return *this;
        }
        Vector3& operator*=(float n) {
            x *= n;
            y *= n;
            z *= n;
            return *this;
        }
        Vector3 operator*(float n) const { return Vector3(x * n, y * n, z * n); }
        [[nodiscard]] float mod() const { return sqrt(POW(x) + POW(y) + POW(z)); }
        [[nodiscard]] float mod2() const { return POW(x) + POW(y) + POW(z); }
        [[nodiscard]] Vector3 norm() const {
            auto invLen = 1 / mod();
            return Vector3(x * invLen, y * invLen, z * invLen);
        }
        [[nodiscard]] Vector2 mappingTo(float ta, float tb) const {
            return Vector2(x / (2 * z * ta), -y / (2 * z * tb));
        }
        bool operator==(const Vector3& vector3) const { return MATH_VEC_OP(x, ==) && MATH_VEC_OP(y, ==) && MATH_VEC_OP(z, ==); }
        Vector3 rotate(const Vector3& s) const {
            const float SSX = sin(s.x);
            const float CSX = cos(s.x);
            const float CSY = cos(s.y);
            const float SSY = sin(s.y);
            const float CSZ = cos(s.z);
            const float SSZ = sin(s.z);
            return Vector3(
                    (x * CSY + y * SSX * SSY - z * CSX * SSY) * CSZ + (y * CSX + z * SSX) * SSZ,
                    (y * CSX + z * SSX) * CSZ - (x * CSY + y * SSX * SSY - z * CSX * SSY) * SSZ,
                    x * SSY - y * SSX * CSY + z * CSX * CSY
            );
        }
        static void rotateArgCal(const Vector3& s, float& SSX, float& CSX, float& CSY, float& SSY, float& CSZ, float& SSZ) {
            SSX = sin(s.x);
            CSX = cos(s.x);
            CSY = cos(s.y);
            SSY = sin(s.y);
            CSZ = cos(s.z);
            SSZ = sin(s.z);
        }
        Vector3 rotatePreTra(float SSX, float CSX, float CSY, float SSY, float CSZ, float SSZ) const {
            return Vector3(
                    (x * CSY + y * SSX * SSY - z * CSX * SSY) * CSZ + (y * CSX + z * SSX) * SSZ,
                    (y * CSX + z * SSX) * CSZ - (x * CSY + y * SSX * SSY - z * CSX * SSY) * SSZ,
                    x * SSY - y * SSX * CSY + z * CSX * CSY
            );
        }
        float x, y, z;
    };
    class Parmline3D {
    public:
        Parmline3D(const Vector3& a0, const Vector3& a1) : p0(a0), p1(a1), v(a1 - a0), v_(v.norm()) { }
        Vector3 p0, p1, v, v_;
    };
    class Plane3D {
    public:
        Plane3D(const Vector3& n, const Vector3& d) : n(n), p(d) { }
        Vector3 n, p;
    };
    Vector3 intersParmlinePlane(const Parmline3D& parmline, const Plane3D& plane);
}


#endif //BERRY3D_MATH_H
