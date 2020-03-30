#include <cmath>
#include "../include/scene.h"
#include "../include/camera.h"

void Berry3D::Camera::render() {
#define NEAR_Z 0.1
#define FAR_Z 1000
    auto ta = scene->ta;
    auto tb = scene->tb;
    auto half_alpha = scene->half_alpha;
    auto half_beta = scene->half_beta;
    const auto invTan_halfPI_sub_halfbeta = 1 / tan(PI * 0.5f - half_beta);
    static Plane3D screenPlane(Vector3(0, 0, 1), Vector3(0, 0, NEAR_Z));
    BERRY3D_VEC3_ROTATE_ARG_DEF
    Vector3::rotateArgCal(-rotation, BERRY3D_VEC3_ROTATE_ARG_PASS);
    auto& items = scene->items;
    Vector3** transedPoints = nullptr;
    size_t transedPointsSize = 0;
    for (auto& item : items) {
        auto& points = item->points;
        auto& planes = item->planes;
#define transToCamPosition(NAME, point, itemWorldPoint) NAME = ((point) + (itemWorldPoint) - (position)).rotate_new(BERRY3D_VEC3_ROTATE_ARG_PASS);
#define transToCamPositionOrig(NAME, itemWorldPoint) auto NAME##_cam = ((itemWorldPoint) - (position)).rotate(BERRY3D_VEC3_ROTATE_ARG_PASS);
        transToCamPositionOrig(itemPosition, item->position);
        if (itemPosition_cam.z + item->maxRadius <= NEAR_Z || itemPosition_cam.z + item->maxRadius > FAR_Z) continue;// 近裁面和远裁面的判断
        if ((abs(itemPosition_cam.x) - item->maxRadius > tan(half_alpha) * (itemPosition_cam.z + item->maxRadius)) || (abs(itemPosition_cam.y) - item->maxRadius > tan(half_beta) * (itemPosition_cam.z + item->maxRadius))) continue;
        if (transedPointsSize < points.size()) {
            delete[] transedPoints;
            transedPoints = new Vector3*[transedPointsSize = points.size()];
        }
        for (size_t i = 0; i < points.size(); i++) transedPoints[i] = nullptr;
        struct CamPlane {
            CamPlane(Vector3* p0, Vector3* p1, Vector3* p2) { points[0] = p0; points[1] = p1; points[2] = p2; }
            ~CamPlane() { }
            // 这里的指针必须全部new分配
            Vector3* points[3];
        };
        for (auto& plane : planes) {
#define getPoint(ID) if (!transedPoints[plane->points[ID]]) transToCamPosition(transedPoints[plane->points[ID]], *item->points[plane->points[ID]], item->position)
            getPoint(0)
            // 0~1
            if (plane->n->operator*(sight) >= 0)
                continue;// 背面
            getPoint(1)
            getPoint(2)
#define mapToScreen(ID) if (plane_.points[ID]->z != INFINITY) { /*if (plane_.points[ID]->z < NEAR_Z) continue;*/ plane_.points[ID]->mappingTo(ta, tb); }
            CamPlane plane_(transedPoints[plane->points[0]], transedPoints[plane->points[1]], transedPoints[plane->points[2]]);
            mapToScreen(0)
            mapToScreen(1)
            mapToScreen(2)
            DRAW_LINE(plane_.points[0]->x, plane_.points[0]->y, plane_.points[1]->x, plane_.points[1]->y)
            DRAW_LINE(plane_.points[1]->x, plane_.points[1]->y, plane_.points[2]->x, plane_.points[2]->y)
            DRAW_LINE(plane_.points[2]->x, plane_.points[2]->y, plane_.points[0]->x, plane_.points[0]->y)

        }
        // 最后清理内存
        for (size_t i = 0; i < points.size(); i++) delete transedPoints[i];
    }
    delete[] transedPoints;
}