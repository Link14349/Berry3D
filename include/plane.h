#ifndef BERRY3D_PLANE_H
#define BERRY3D_PLANE_H

#include "item.h"

namespace Berry3D {
    class Plane : public Entity {
    public:
        Plane(float w = 1, float h = 1) : Entity(sqrt(w * w + h * h)) {
            points.push_back(new Vector3(w, h, 0));
            points.push_back(new Vector3(-w, h, 0));
            points.push_back(new Vector3(w, -h, 0));
            planes.push_back(new PlaneEle(new Vector3(0, 0, 0), 0, 1, 2));
        }
        ~Plane() { }
    private:
    };
}

#endif //BERRY3D_PLANE_H
