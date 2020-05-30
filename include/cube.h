#ifndef BERRY3D_CUBE_H
#define BERRY3D_CUBE_H

#include "item.h"

namespace Berry3D {
    class Cube : public Entity {
    public:
        Cube(float w = 1, float h = 1, float d = 1, Color c = Color(1, 1, 1)) : Entity(sqrt(w * w + h * h + d * d)) {
#define BERRY3D_CUBE_POINTS_DEF(W, H, D, ID) points.push_back(new Vector3(W w, H h, D d));
#define BERRY3D_PLANES_DEF(NX, NY, NZ, ID0, ID1, ID2) planes.push_back(new PlaneEle(new Vector3(NX, NY, NZ), ID0, ID1, ID2, new Material(c, .7, .8, 1, 2)));
            BERRY3D_CUBE_POINTS_DEF( , , , 0);
            BERRY3D_CUBE_POINTS_DEF( , , -, 1);
            BERRY3D_CUBE_POINTS_DEF( , -, , 2);
            BERRY3D_CUBE_POINTS_DEF( , -, -, 3);
            BERRY3D_CUBE_POINTS_DEF(-, , , 4);
            BERRY3D_CUBE_POINTS_DEF(-, , -, 5);
            BERRY3D_CUBE_POINTS_DEF(-, -, , 6);
            BERRY3D_CUBE_POINTS_DEF(-, -, -, 7);
            BERRY3D_PLANES_DEF(1, 0, 0, 1, 2, 3);
            BERRY3D_PLANES_DEF(1, 0, 0, 0, 1, 2);
            BERRY3D_PLANES_DEF(-1, 0, 0, 5, 6, 7);
            BERRY3D_PLANES_DEF(-1, 0, 0, 4, 5, 6);
            BERRY3D_PLANES_DEF(0, -1, 0, 3, 6, 7);
            BERRY3D_PLANES_DEF(0, -1, 0, 2, 3, 6);
            BERRY3D_PLANES_DEF(0, 1, 0, 1, 4, 5);
            BERRY3D_PLANES_DEF(0, 1, 0, 0, 1, 4);
            BERRY3D_PLANES_DEF(0, 0, 1, 2, 4, 6);
            BERRY3D_PLANES_DEF(0, 0, 1, 0, 2, 4);
            BERRY3D_PLANES_DEF(0, 0, -1, 3, 5, 7);
            BERRY3D_PLANES_DEF(0, 0, -1, 1, 3, 5);
        }
        ~Cube() { }
    private:
    };
}

#endif //BERRY3D_CUBE_H
