#include <cmath>
#include "../include/scene.h"
#include "../include/camera.h"

void Berry3D::Camera::render() {
#define NEAR_Z 0.1
#define FAR_Z 1000
    const float SIZE = scene->berry3D->width();
    float height_width = scene->berry3D->height() / scene->berry3D->width();
    auto ta = scene->ta;
    auto tb = scene->tb;
    auto half_alpha = scene->half_alpha;
    auto half_beta = scene->half_beta;
//    const auto invTan_halfPI_sub_halfbeta = 1 / tan(PI * 0.5f - half_beta);
    static Plane3D screenPlane(Vector3(0, 0, 1), Vector3(0, 0, NEAR_Z));
    BERRY3D_VEC3_ROTATE_ARG_DEF
    Vector3::rotateArgCal(-rotation, BERRY3D_VEC3_ROTATE_ARG_PASS);
    auto& items = scene->items;
    const float MIN_LEN_RATIO = 1 / SIZE;// 1px
    for (auto& item : items) {
        auto& points = item->points;
        auto& planes = item->planes;
#define transToCamPosition(NAME, point, itemWorldPoint) NAME = ((point) + (itemWorldPoint) - (position)).rotate_new(BERRY3D_VEC3_ROTATE_ARG_PASS);
#define transToCamPositionOrig(NAME, itemWorldPoint) auto NAME##_cam = ((itemWorldPoint) - (position)).rotate(BERRY3D_VEC3_ROTATE_ARG_PASS);
        transToCamPositionOrig(itemPosition, item->position);
        if (item->radius() / (itemPosition_cam.z * ta) <= MIN_LEN_RATIO) {
            itemPosition_cam.mappingTo(ta, tb);
            DRAW_POINT(itemPosition_cam.x, itemPosition_cam.y)
            continue;
        }
        if (itemPosition_cam.z + item->maxRadius <= NEAR_Z || itemPosition_cam.z + item->maxRadius > FAR_Z) continue;// 近裁面和远裁面的判断
        if ((abs(itemPosition_cam.x) - item->maxRadius > ta * (itemPosition_cam.z + item->maxRadius)) || (abs(itemPosition_cam.y) - item->maxRadius > tb * (itemPosition_cam.z + item->maxRadius)))
            continue;
        if (transedPointsSize < points.size()) {
            delete[] transedPoints;
            transedPoints = new Vector3*[transedPointsSize = points.size()];
        }
        for (size_t i = 0; i < points.size(); i++) transedPoints[i] = nullptr;
        for (auto& plane : planes) {
            if (plane->n->operator*(position - *points[plane->points[0]] - item->position) < 0) continue;
#define getPoint(ID) if (!transedPoints[plane->points[ID]]) transToCamPosition(transedPoints[plane->points[ID]], *points[plane->points[ID]], item->position)
#define mapToScreen(ID) if (transedPoints[plane->points[ID]]->z != INFINITY) { if (transedPoints[plane->points[ID]]->z < NEAR_Z) continue; transedPoints[plane->points[ID]]->mappingTo(ta, tb, height_width); }
            if (abs(points[plane->points[0]]->operator-(*points[plane->points[1]]).mod() * 0.5 / (points[plane->points[0]]->z * ta)) <= MIN_LEN_RATIO) {
                getPoint(0)
                mapToScreen(0)
                DRAW_POINT(transedPoints[plane->points[0]]->x, transedPoints[plane->points[0]]->y)
                continue;
            }
            getPoint(0)
            getPoint(1)
            getPoint(2)
            mapToScreen(0)
            mapToScreen(1)
            mapToScreen(2)
            DRAW_LINE(transedPoints[plane->points[0]]->x, transedPoints[plane->points[0]]->y, transedPoints[plane->points[1]]->x, transedPoints[plane->points[1]]->y)
            DRAW_LINE(transedPoints[plane->points[1]]->x, transedPoints[plane->points[1]]->y, transedPoints[plane->points[2]]->x, transedPoints[plane->points[2]]->y)
            DRAW_LINE(transedPoints[plane->points[2]]->x, transedPoints[plane->points[2]]->y, transedPoints[plane->points[0]]->x, transedPoints[plane->points[0]]->y)
        }
        // 最后清理内存
        for (size_t i = 0; i < points.size(); i++) delete transedPoints[i];
    }
}