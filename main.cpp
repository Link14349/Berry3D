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

float theta = 0;
auto la = new Berry3D::Light(Berry3D::Color(0, 2, 0), Berry3D::Vector3(0, 10, 10));
auto lb = new Berry3D::Light(Berry3D::Color(0, 0, 2), Berry3D::Vector3(0, 10, 0));

int main() {
    scene.use(&camera);
    berry3D.use(&scene);
    berry3D.setKeyEvent(callback);
    scene.setAmbientLight(Berry3D::Color(0, 1, 0));
    scene.addLight(la);
    scene.addLight(lb);
    Berry3D::ObjLoader objLoader("torus.obj");
    auto obj = objLoader.load();
    obj->scale(.01f);
    obj->rotate(Berry3D::Vector3(0, 0, M_PI_2));
    scene.push(obj);
    Berry3D::BinContent bc{};
    obj->tobe4(bc);
    auto fp = fopen( "ring.be4d" , "w" );
    fwrite(bc.content, bc.len , 1, fp);
    fclose(fp);
    berry3D.render([]() {
        la->position.x = 10 * cos(theta);
        lb->position.y = 10 * cos(theta + PI);
        theta += PI / 90;
    });
    scene.autoClear();
    return 0;
}
