#ifndef BERRY3D_ITEM_H
#define BERRY3D_ITEM_H

#include <list>
#include <vector>
#include "math.h"

namespace Berry3D {
    class Item {
    public:
        Item() { }
#define BERRY3D_ITEM_MOVE position.x -= p.x; position.y -= p.y; position.z += p.z;
        void forward(float step) {
            auto p = Vector3(0, 0, step, -rotation);
            BERRY3D_ITEM_MOVE
        }
        void left(float step) {
            auto p = Vector3(step, 0, 0, -rotation);
            BERRY3D_ITEM_MOVE
        }
        void up(float step) {
            auto p = Vector3(0, step, 0, -rotation);
            BERRY3D_ITEM_MOVE
        }
        void back(float step) { forward(-step); }
        void right(float step) { left(-step); }
        void down(float step) { up(-step); }
        virtual void rotate(const Vector3& r) { rotation += r; }
        Vector3 position;
        Vector3 rotation;
    };

    class Entity : public Item {
        friend class Camera;
        friend class Loader;
        friend class ObjLoader;
    public:
        virtual ~Entity() {
            for (auto& plane : planes) delete plane;
            for (auto& point : points) delete point;
        }
        inline void rotate(Vector3&& rt) {
            rotation += rt;
            rt.inverse();
            BERRY3D_VEC3_ROTATE_ARG_DEF
            Vector3::rotateArgCal(rt, BERRY3D_VEC3_ROTATE_ARG_PASS);
            for (auto& point : points) point->self_rotate(BERRY3D_VEC3_ROTATE_ARG_PASS);
            for (auto& plane : planes) plane->n->self_rotate(BERRY3D_VEC3_ROTATE_ARG_PASS);
        }
        void scale(float s) {
            for (auto& point : points) point->operator*=(s);
            maxRadius *= s;
        }
        void scale(const Vector3& vec) {
            auto max2 = 0;
            for (auto& point : points) {
                point->operator%=(vec);
                if (max2 < point->mod2()) max2 = point->mod2();
            }
            maxRadius = sqrt(max2);
        }
        float radius() { return maxRadius; }
        void moveOrigin(const Vector3& offset) {
            for (auto& point : points) point->operator-=(offset);
        }
    protected:
        Entity(float maxRadius) : maxRadius(maxRadius) {}
        // 这里的指针全部只能使用new分配，delete销毁
        struct PlaneEle {
            PlaneEle(Vector3* n, size_t i0, size_t i1, size_t i2, float c0 = 1, float c1 = 1, float c2 = 1)
                    : n(n) {
                points[0] = i0;
                points[1] = i1;
                points[2] = i2;
                color[0] = c0;
                color[1] = c1;
                color[2] = c2;
            }
            ~PlaneEle() { delete n; }
            Vector3* n;
            float color[3];
            size_t points[3];
        };
        float maxRadius;
        std::vector<Vector3 *> points;
        std::list<PlaneEle *> planes;
    };
}


#endif //BERRY3D_ITEM_H
