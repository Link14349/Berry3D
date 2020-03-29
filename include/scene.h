#ifndef BERRY3D_SCENE_H
#define BERRY3D_SCENE_H

#include <list>
#include <cmath>
#include "Berry3D.h"
#include "item.h"
#include "math.h"
#include "camera.h"

namespace Berry3D {
    class Scene {
        friend class Camera;
    public:
        Scene() : camera(nullptr) { setAlpha(PI * 0.66); setBeta(PI * 0.66); }
        void use(Camera* cam) { camera = cam; cam->scene = this; }
        void render() { camera->render(); }
        void setAlpha(float a) { half_alpha = a * .5f; ta = tan(half_alpha); }
        void setBeta(float b) { half_beta = b * .5f; tb = tan(half_beta); }
        void push(Entity* item) { items.push_back(item); }
        std::list<Entity*> items;
    private:
        float ta, tb;
        float half_alpha, half_beta;
        Camera* camera;
    };
}


#endif //BERRY3D_SCENE_H
