#ifndef BERRY3D_COLOR_H
#define BERRY3D_COLOR_H

#include "math.h"

namespace Berry3D {
    union Color {
        Color() { }
        Color(const Color& color) : vec(color.vec) { }
        Color(const Vector3& v) : vec(v) { }
        Color(float r, float g, float b) : vec(r, g, b) { }
        Vector3 vec;
        float rgb[3];
    };
}

#endif //BERRY3D_COLOR_H
