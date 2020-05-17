#ifndef BERRY3D_LIGHTS_H
#define BERRY3D_LIGHTS_H

#include "color.h"

namespace Berry3D {
    class Light {
    public:
        Light(Color c, const Vector3& pos) : color(c), position(pos) {}
        Color color;
        Vector3 position;
    };
}


#endif //BERRY3D_LIGHTS_H
