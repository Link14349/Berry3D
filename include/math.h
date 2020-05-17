#ifndef BERRY3D_MATH_H
#define BERRY3D_MATH_H

#include <cmath>

namespace Berry3D {
#ifndef PI
#define PI 3.14159265358979323846
#endif
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
        Vector3(float a, float b, float c, const Vector3& vec) : x(a), y(b), z(c) { self_rotate(vec); }
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
        void inverse() {
            x = -x;
            y = -y;
            z = -z;
        }
        Vector3 operator-(const Vector3& vector3) const { return Vector3(x - vector3.x, y - vector3.y, z - vector3.z);}
        Vector3 operator-() const { return Vector3(-x, -y, -z); }
        // 点积
        float operator*(const Vector3& vector3) const {
            return MATH_VEC_OP(x, *) + MATH_VEC_OP(y, *) + MATH_VEC_OP(z, *);
        }
        // 向量积
        Vector3 operator%(const Vector3& vector3) const { return Vector3(MATH_VEC_OP(x, *), MATH_VEC_OP(y, *), MATH_VEC_OP(z, *)); }
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
        void setAllZero() { x = y = z = 0; }
        void mappingTo(float ta, float tb, float height_width = 1) {
            x /= z * ta;
            y /= z * tb * height_width;
            z = INFINITY;
        }
        bool operator==(const Vector3& vector3) const { return MATH_VEC_OP(x, ==) && MATH_VEC_OP(y, ==) && MATH_VEC_OP(z, ==); }
#define BERRY3D_VEC3_ROTATE_ARG_PASS SSX, CSX, CSY, SSY, CSZ, SSZ
#define BERRY3D_VEC3_ROTATE_ARG_DEF float BERRY3D_VEC3_ROTATE_ARG_PASS;
#define BERRY3D_VEC3_ROTATE_X (x * CSY + y * SSX * SSY - z * CSX * SSY) * CSZ + (y * CSX + z * SSX) * SSZ
#define BERRY3D_VEC3_ROTATE_Y (y * CSX + z * SSX) * CSZ - (x * CSY + y * SSX * SSY - z * CSX * SSY) * SSZ
#define BERRY3D_VEC3_ROTATE_Z x * SSY - y * SSX * CSY + z * CSX * CSY
#define BERRY3D_VEC3_ROTATE_X_TMP (tmpx * CSY + tmpy * SSX * SSY - tmpz * CSX * SSY) * CSZ + (tmpy * CSX + tmpz * SSX) * SSZ
#define BERRY3D_VEC3_ROTATE_Y_TMP (tmpy * CSX + tmpz * SSX) * CSZ - (tmpx * CSY + tmpy * SSX * SSY - tmpz * CSX * SSY) * SSZ
#define BERRY3D_VEC3_ROTATE_Z_TMP tmpx * SSY - tmpy * SSX * CSY + tmpz * CSX * CSY
#define BERRY3D_VEC3_ROTATE_ARG_INIT(PRE) PRE SSX = sin(s.x); \
        PRE CSX = cos(s.x); \
        PRE CSY = cos(s.y); \
        PRE SSY = sin(s.y); \
        PRE CSZ = cos(s.z); \
        PRE SSZ = sin(s.z);
        static void rotateArgCal(const Vector3& s, float& SSX, float& CSX, float& CSY, float& SSY, float& CSZ, float& SSZ) {
            BERRY3D_VEC3_ROTATE_ARG_INIT( )
        }
        Vector3 rotate(const Vector3& s) const {
            BERRY3D_VEC3_ROTATE_ARG_INIT(const float)
            return Vector3(
                    BERRY3D_VEC3_ROTATE_X,
                    BERRY3D_VEC3_ROTATE_Y,
                    BERRY3D_VEC3_ROTATE_Z
            );
        }
        Vector3* rotate_new(const Vector3& s) const {
            BERRY3D_VEC3_ROTATE_ARG_INIT(const float)
            return new Vector3(
                    BERRY3D_VEC3_ROTATE_X,
                    BERRY3D_VEC3_ROTATE_Y,
                    BERRY3D_VEC3_ROTATE_Z
            );
        }
        Vector3 rotate(float SSX, float CSX, float CSY, float SSY, float CSZ, float SSZ) const {
            return Vector3(
                    BERRY3D_VEC3_ROTATE_X,
                    BERRY3D_VEC3_ROTATE_Y,
                    BERRY3D_VEC3_ROTATE_Z
            );
        }
        Vector3* rotate_new(float SSX, float CSX, float CSY, float SSY, float CSZ, float SSZ) const {
            return new Vector3(
                    BERRY3D_VEC3_ROTATE_X,
                    BERRY3D_VEC3_ROTATE_Y,
                    BERRY3D_VEC3_ROTATE_Z
            );
        }
        void self_rotate(const Vector3& s) {
            BERRY3D_VEC3_ROTATE_ARG_INIT(const float)
            auto tmpx = x, tmpy = y, tmpz = z;
            x = BERRY3D_VEC3_ROTATE_X_TMP;
            y = BERRY3D_VEC3_ROTATE_Y_TMP;
            z = BERRY3D_VEC3_ROTATE_Z_TMP;
        }
        void self_rotate(float SSX, float CSX, float CSY, float SSY, float CSZ, float SSZ) {
            auto tmpx = x, tmpy = y, tmpz = z;
            x = BERRY3D_VEC3_ROTATE_X_TMP;
            y = BERRY3D_VEC3_ROTATE_Y_TMP;
            z = BERRY3D_VEC3_ROTATE_Z_TMP;
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
