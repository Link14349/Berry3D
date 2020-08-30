#ifndef BERRY3D_CYLINDER_H
#define BERRY3D_CYLINDER_H

#include "math.h"
#include "item.h"

#define FINENESS 0.01f

namespace Berry3D {
    class Cylinder : public Entity {
    public:
        Cylinder(float r = 1, float h = 2, Color c = Color(1, 1, 1)) : Entity(sqrt(r * r + h * h)) {
//            points.push_back(new Vector3(W w, H h, D d));
//            planes.push_back(new PlaneEle(new Vector3(NX, NY, NZ), ID0, ID1, ID2, new Material(c, .7, .8, 1, 2)));
            h *= .5f;
            points.push_back(new Vector3(0, -h, 0));// 底平面原点
            points.push_back(new Vector3(0,  h, 0));// 顶平面原点
            const float THETA_STEP = FINENESS * 2 * PI / r;
            // 建立底部圆盘
            for (float theta = 0; ;  theta += THETA_STEP) {
                if (theta >= 2 * PI) {
                    points.push_back(new Vector3(0, -h, 1));// 底平面的点
                    points.push_back(new Vector3(0,  h, 1));// 顶平面的点
                    break;
                }
                points.push_back(new Vector3(sin(theta), -h, cos(theta)));// 底平面的点
                points.push_back(new Vector3(sin(theta),  h, cos(theta)));// 顶平面的点
            }
            const uint32_t C = (points.size() >> 1) - 1;
            for (uint32_t i = 0; i < C - 1; i++) {
                planes.push_back(new PlaneEle(new Vector3(0, -1, 0), 0, ((i + 1)) << 1, ((i + 2)) << 1, new Material(c, .7, .8, 1, 2)));// 底平面
                planes.push_back(new PlaneEle(new Vector3(0, 1, 0), 1, (((i + 1)) << 1) | 1, (((i + 2)) << 1) | 1, new Material(c, .7, .8, 1, 2)));// 顶平面
                // 上下面链接面
                planes.push_back(new PlaneEle(new Vector3(sin(i * THETA_STEP), 0, cos(i * THETA_STEP)), ((i + 1)) << 1, (((i + 1)) << 1) | 1, (((i + 2)) << 1) | 1, new Material(c, .7, .8, 1, 2)));
                planes.push_back(new PlaneEle(new Vector3(sin(i * THETA_STEP), 0, cos(i * THETA_STEP)), (((i + 2)) << 1) | 1, ((i + 1)) << 1, ((i + 2)) << 1, new Material(c, .7, .8, 1, 2)));
            }
        }
    };
}


#endif //BERRY3D_CYLINDER_H
