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
            camera.rotate(Berry3D::Vector3(PI / 90, 0, 0));
            break;
        case GLFW_KEY_DOWN:
            camera.rotate(Berry3D::Vector3(-PI / 90, 0, 0));
            break;
        case GLFW_KEY_LEFT:
            camera.rotate(Berry3D::Vector3(0, PI / 90, 0));
            break;
        case GLFW_KEY_RIGHT:
            camera.rotate(Berry3D::Vector3(0, -PI / 90, 0));
            break;
        case GLFW_KEY_I:
            std::cout << camera.position.x << ", " << camera.position.y << ", " << camera.position.z << std::endl;
            std::cout << camera.rotation.x << ", " << camera.rotation.y << ", " << camera.rotation.z << std::endl;
            break;
    }
}

int main() {
    scene.use(&camera);
    berry3D.use(&scene);
    berry3D.setKeyEvent(callback);
    scene.setAmbientLight(Berry3D::Color(0, 1, 0));
    scene.addLight(new Berry3D::Light(Berry3D::Color(0, 2, 0), Berry3D::Vector3(0, 10, -10)));
#define LEN 1
//    camera.rotation.x = -0.174533;
//    camera.rotation.y = 0;
//    camera.rotation.z = 0;
//    camera.position.x = 4;
//    camera.position.y = 0.623607;
//    camera.position.z = -6.00845;
    Berry3D::ObjLoader objLoader("link.obj");
    auto obj = objLoader.load();
    obj->rotate(Berry3D::Vector3(0, PI, 0));
    obj->position.z = obj->radius();
    obj->position.y = -obj->radius() * 0.5;
    scene.push(obj);
//    camera.position.z = -2 * LEN;
//    for (int i = 0; i < LEN; i++)
//        for (int j = 0; j < LEN; j++)
//            for (int k = 0; k < LEN; k++) {
//                auto plane = new Berry3D::Plane;
//                plane->position.x = i * 2 - LEN;
//                plane->position.y = j * 2 - LEN;
//                plane->position.z = k * 2 - LEN;
//                scene.push(plane);
//            }
    berry3D.render();
    scene.autoClear();
    return 0;
}
