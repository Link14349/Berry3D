#ifndef BERRY3D_SCENE_H
#define BERRY3D_SCENE_H

#include <list>
#include <cmath>
#include "Berry3D.h"
#include "item.h"
#include "math.h"
#include "camera.h"
#include "color.h"
#include "lights.h"

namespace Berry3D {
    class Berry3D;
    class Scene {
        friend class Camera;
        friend class Berry3D;
    public:
        Scene() : camera(nullptr) { setAlpha(PI * 0.66); setBeta(PI * 0.66); }
        void use(Camera* cam) { camera = cam; cam->scene = this; }
        void render() { camera->render(); }
        void setAlpha(float a) { half_alpha = a * .5f; ta = tan(half_alpha); }
        void setBeta(float b) { half_beta = b * .5f; tb = tan(half_beta); }
        void push(Entity* item) { items.push_back(item); }
        void autoClear() {
            for (auto& entity : items) delete entity;
            for (auto& light : lights) delete light;
        }
        void addLight(Light* light) { lights.push_back(light); }
        void setAmbientLight(const Color& color) { ambientLightColor.vec = color.vec; }
        std::list<Entity*> items;
    private:
        float ta, tb;
        float half_alpha, half_beta;
        Camera* camera;
        Berry3D* berry3D;
        Color ambientLightColor;
        std::list<Light*> lights;
    };
}


#endif //BERRY3D_SCENE_H
