#ifndef BERRY3D_ITEM_H
#define BERRY3D_ITEM_H

#include <list>
#include <vector>
#include <string>
#include "math.h"
#include "material.h"

namespace Berry3D {
    struct BinContent {
        char* content;
        uint32_t len;
    };
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
        static void u32Bin(uint32_t iv, char* str, uint32_t& idx) {
            for (uint32_t i = 0xff, c = 0; c < 4; i <<= 8, c++) str[idx++] = (iv & i) >> (c << 3);
        }
        static void floatBin(float v, char* str, uint32_t& idx) {
            u32Bin(*((uint32_t*)(&v)), str, idx);
        }
        void tobe4(BinContent& bc) {// 转为.be4 4d文件格式
            char* content = new char[20 + points.size() * 12 + planes.size() * 24];// 18 + points.size() * 12 + planes.size() * 24个字符，算上\0就加一，再加上一位预防bug
            uint32_t idx = 6;
            strcpy(content, "be4f\x01\x03");// 1版本号00; 1文件类型3d模型; 4占位符，存planes存储地址; 8备用空间，暂无用处
            u32Bin(18 + points.size() * 12, content, idx);
            idx = 18;
            for (auto point : points) {
                floatBin(point->x, content, idx);
                floatBin(point->y, content, idx);
                floatBin(point->z, content, idx);
            }
            for (auto plane : planes) {
                u32Bin(plane->points[0], content, idx);
                u32Bin(plane->points[1], content, idx);
                u32Bin(plane->points[2], content, idx);
            }
            bc.content = content;
            bc.len = idx;
        }
    protected:
        Entity(float maxRadius) : maxRadius(maxRadius) {}
        // 这里的指针全部只能使用new分配，delete销毁
        struct PlaneEle {
            PlaneEle(Vector3* n, size_t i0, size_t i1, size_t i2, Material* m = nullptr)
                    : n(n), material(m) {
                points[0] = i0;
                points[1] = i1;
                points[2] = i2;
            }
            ~PlaneEle() { delete n; delete material; }
            Vector3* n;
            size_t points[3];
            Material* material;
        };
        float maxRadius;
        std::vector<Vector3 *> points;
        std::list<PlaneEle *> planes;
    };
}


#endif //BERRY3D_ITEM_H
