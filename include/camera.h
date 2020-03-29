#ifndef BERRY3D_CAMERA_H
#define BERRY3D_CAMERA_H

#include "item.h"

namespace Berry3D {
    class Scene;
    class Camera : public Item {
        friend class Scene;
    public:
        Camera(Scene* scene = nullptr) : Item(), scene(scene), sight(0, 0, 1) { }
        virtual void rotate(const Vector3 &r) override {
            rotation += r;
            sight.self_rotate(r);
        }
        void render();
    protected:
        Scene* scene;
        Vector3 sight;
    };
    class FreeCamera : public Camera {
        friend class Scene;
    public:
        FreeCamera(Scene* scene = nullptr) : Camera(scene) { }
    };
}


#endif //BERRY3D_CAMERA_H
