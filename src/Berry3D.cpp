#include <cstdio>
#include "../include/Berry3D.h"
#include "../include/timestamp.h"
#include "../include/scene.h"
#include "../include/shader.h"

int Berry3D::Berry3D::render(void(*cb)()) {
    glfwMakeContextCurrent(win);
    float invh = 1 / height();
//    float x1 = -1, y1 = -1;
    while(!glfwWindowShouldClose(win)){
        glfwGetWindowSize(win, &w, &h);
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClear (GL_COLOR_BUFFER_BIT);
        glLineWidth(1);//设置线段宽度
        glColor3f(1.0,1.0,1.0);
//        renderTr(x1, y1, -1, -1, 0, 0, invh);
//        double xpos, ypos;
//        glfwGetCursorPos(win, &xpos, &ypos);
//        renderTr(-0.197132811, 0.197132811, -0.118279681, -0.118279681, -0.197132811, -0.197132811, invh);
        auto start = getCurrentTime();
        scene->render();
        if (cb) cb();
        auto end = getCurrentTime();
        glfwSetWindowTitle(win, (title + " FPS: " + std::to_string(1000 / (float)(end - start))).c_str());
        glfwSwapBuffers(win);
        glfwPollEvents();
//        x1 += invh;
//        if (x1 >= 1) {
//            x1 = -1;
//            y1 += invh;
//        }
    }
    glfwTerminate();
    return 0;
}

void Berry3D::Berry3D::use(Scene *s) {
    scene = s;
    scene->berry3D = this;
}