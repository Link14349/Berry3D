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
#define LEN 30
//    camera.rotation.x = -0.174533;
//    camera.rotation.y = 0;
//    camera.rotation.z = 0;
//    camera.position.x = 4;
//    camera.position.y = 0.623607;
//    camera.position.z = -6.00845;
    camera.position.z = -2.69090748;
    auto cube = new Berry3D::Cube(1.69090748, 1.69090748, 1.69090748);
    scene.push(cube);
//    camera.position.z = -2 * LEN;
//    for (int i = 0; i < LEN; i++)
//        for (int j = 0; j < LEN; j++)
//            for (int k = 0; k < LEN; k++) {
//                auto cube = new Berry3D::Cube;
//                cube->position.x = i * 2 - LEN;
//                cube->position.y = j * 2 - LEN;
//                cube->position.z = k * 2 - LEN;
//                scene.push(cube);
//            }
    berry3D.render();
    scene.autoClear();
    return 0;
}
