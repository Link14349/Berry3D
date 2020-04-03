#include <iostream>
#include <fstream>
#include "include/Berry3D.h"

Berry3D::Berry3D berry3D("Berry3D");
Berry3D::Scene scene;
Berry3D::FreeCamera camera;

static void callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_KEY_W:
            camera.forward(1);
            break;
        case GLFW_KEY_S:
            camera.forward(-1);
            break;
        case GLFW_KEY_A:
            camera.left(1);
            break;
        case GLFW_KEY_D:
            camera.left(-1);
            break;
        case GLFW_KEY_UP:
            camera.rotate(Berry3D::Vector3(-PI / 90, 0, 0));
            break;
        case GLFW_KEY_DOWN:
            camera.rotate(Berry3D::Vector3(PI / 90, 0, 0));
            break;
        case GLFW_KEY_LEFT:
            camera.rotate(Berry3D::Vector3(0, PI / 90, 0));
            break;
        case GLFW_KEY_RIGHT:
            camera.rotate(Berry3D::Vector3(0, -PI / 90, 0));
            break;
    }
}

int main() {
    scene.use(&camera);
    berry3D.use(&scene);
    berry3D.setKeyEvent(callback);
    Berry3D::ObjLoader loader("link.obj");
    auto obj = loader.load();
    obj->scale(2);
    camera.position.z = -10;
    obj->rotate(Berry3D::Vector3(PI, 0, 0));
    obj->position.y = 10;
    berry3D.setAfterRendering([](Berry3D::Scene* scene) {
        scene->items.front()->rotate(Berry3D::Vector3(0, PI / 180, 0));
    });
    scene.push(obj);
    berry3D.render();
    delete obj;
    return 0;
}
