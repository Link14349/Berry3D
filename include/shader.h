#ifndef BERRY3D_SHADER_H
#define BERRY3D_SHADER_H

#include "../include/draws.h"
#include <GLFW/glfw3.h>
#include <algorithm>

namespace Berry3D {
    /*
            * (p0)
           / \
          /   \
     (p2)*-----*(p1)
    */
    inline void renderFlatBottomTr(float x0, float y0, float x1, float y1, float x2, float invHeight);// Because it's flat bottomed, the value of y2 is equal to the value of y1
    /*
     (p1)*-----*(p2)
          \   /
           \ /
            * (p0)
    */
    inline void renderFlatTopTr(float x0, float y0, float x1, float y1, float x2, float invHeight);
    /*
              == * (p0)
            ==   /
          ==    /
     (p2)*     /
          \   /
           \ /
            * (p1)
    */
    inline void renderTr(float x0, float y0, float x1, float y1, float x2, float y2, float invHeight);
}

void Berry3D::renderTr(float x0, float y0, float x1, float y1, float x2, float y2, float invHeight) {
    if (y1 > y0) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    if (y2 > y0) {
        std::swap(y0, y2);
        std::swap(x0, x2);
    }
    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }
    if (abs(y0 - y1) <= 0.001) {
        renderFlatTopTr(x2, y2, x0, y0, x1, invHeight);
        return;
    }
    auto tmp = (y2 - y0) * (x0 - x1) / (y0 - y1) + x0;
    renderFlatBottomTr(x0, y0, x2, y2, tmp, invHeight);
    renderFlatTopTr(x1, y1, x2, y2, tmp, invHeight);
}
void Berry3D::renderFlatBottomTr(float x0, float y0, float x1, float y1, float x2, float invHeight) {
    float left_dxdy = (x2 - x0) / (y1 - y0) * invHeight;
    float right_dxdy = (x1 - x0) / (y1 - y0) * invHeight;
    float s = x2, e = x1;
    for (float y = y1; y <= y0; y += invHeight) {
        DRAW_LINE(s, y, e, y)
        s += left_dxdy;
        e += right_dxdy;
    }
}
void Berry3D::renderFlatTopTr(float x0, float y0, float x1, float y1, float x2, float invHeight) {
    float left_dxdy = (x0 - x1) / (y1 - y0) * invHeight;
    float right_dxdy = (x0 - x2) / (y1 - y0) * invHeight;
    float s = x1, e = x2;
    for (float y = y1; y >= y0; y -= invHeight) {
        DRAW_LINE(s, y, e, y)
        s += left_dxdy;
        e += right_dxdy;
    }
}

#endif //BERRY3D_SHADER_H
