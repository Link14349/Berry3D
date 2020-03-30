#include <iostream>

/*size_t mem_count = 0;

void* operator new(size_t size) {
    mem_count++;
    auto p = malloc(size);
    std::clog << "n" << p << "\n";
    return p;
}
void operator delete(void* p) {
    mem_count++;
    std::clog << "d" << p << "\n";
    free(p);
}*/

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

#define LEN 20

int main() {
    Berry3D::Cube* cubes[LEN * LEN * LEN];
    scene.use(&camera);
    for (float i = 0; i < LEN; i++) {
        for (float j = 0; j < LEN; j++) {
            for (float k = 0; k < LEN; k++) {
                auto cube = cubes[(size_t)(i * LEN * LEN + j * LEN + k)] = new Berry3D::Cube;
                cube->position.x = -i + LEN * 0.5f;
                cube->position.y = -j + LEN * 0.5f;
                cube->position.z = -k + LEN * 0.5f;
                scene.push(cube);
            }
        }
    }
//    Berry3D::Cube cube;
//    scene.push(&cube);
    berry3D.use(&scene);
    berry3D.setKeyEvent(callback);
//    berry3D.setAfterRendering([](Berry3D::Scene* scene) {
//        scene->items.front()->rotate(Berry3D::Vector3(PI / 180, PI / 180, PI / 180));
//    });
    camera.position.z = -LEN;
    berry3D.render();
    for (size_t i = 0; i < LEN * LEN * LEN; i++) delete cubes[i];
    return 0;
}
