#ifndef BERRY3D_BERRY3D_H
#define BERRY3D_BERRY3D_H

#include <string>
#include <GLFW/glfw3.h>
#include "math.h"
#include "scene.h"

namespace Berry3D {
    class Scene;
    class Berry3D {
    public:
        Berry3D(const std::string& title, int w = 800, int h = 800) : scene(nullptr), win(nullptr), title(title), w(w), h(h) {
            if(!glfwInit())
                exit(-1);
            win = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
            if(!win)
            {
                glfwTerminate();
                exit(-1);
            }
        }
        int render();
        float width() { return w; }
        float height() { return h; }
        void setKeyEvent(void (*cb)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(win, cb); }
        void setAfterRendering(void (*ar)(Scene*)) { afterRendering = ar; }
        void use(Scene* s);
    private:
        int w, h;
        GLFWwindow* win;
        Scene* scene;
        void (*afterRendering)(Scene*) = nullptr;
        std::string title;
    };
}


#endif //BERRY3D_BERRY3D_H
#include "scene.h"
#include "item.h"
#include "camera.h"
#include "cube.h"
#include "plane.h"
#include "loader.h"
#include "objLoader.h"