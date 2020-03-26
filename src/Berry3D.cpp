#include "../include/Berry3D.h"

int Berry3D::Berry3D::render() {
    if(!glfwInit()){
        return -1;
    }
    win = glfwCreateWindow(640, 480, "Berry3D", NULL, NULL);
    if(!win)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);
    while(!glfwWindowShouldClose(win)){
        glClearColor (0.0, 0.0, 0.0, 0.0);
        glClear (GL_COLOR_BUFFER_BIT);
        glLineWidth(1);//设置线段宽度
        glColor3f(1.0,1.0,1.0);
#define DRAW_LINE(fx, fy, tx ,ty) glBegin(GL_LINES); \
        glVertex2f(fx, fy); \
        glVertex2f(tx, ty); \
        glEnd();

        DRAW_LINE(0, 0, 1, 1)
        DRAW_LINE(0, 0, -1, -1)
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}