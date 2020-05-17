#include <cstdio>
#include "../include/Berry3D.h"
#include "../include/timestamp.h"
#include "../include/scene.h"

int Berry3D::Berry3D::render() {
    glfwMakeContextCurrent(win);
    while(!glfwWindowShouldClose(win)){
        glfwGetWindowSize(win, &w, &h);
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClear (GL_COLOR_BUFFER_BIT);
        glLineWidth(1);//设置线段宽度
        glColor3f(1.0,1.0,1.0);
        auto start = getCurrentTime();
        scene->render();
        if (afterRendering) afterRendering(scene);
        auto end = getCurrentTime();
        glfwSetWindowTitle(win, (title + " FPS: " + std::to_string(1000 / (float)(end - start))).c_str());
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void Berry3D::Berry3D::use(Scene *s) {
    scene = s;
    scene->berry3D = this;
}