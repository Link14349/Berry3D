#ifndef BERRY3D_DRAWS_H
#define BERRY3D_DRAWS_H

#define DRAW_LINE(fx, fy, tx ,ty) glBegin(GL_LINES); \
        glVertex2f(fx, fy); \
        glVertex2f(tx, ty); \
        glEnd();
#define DRAW_POINT(fx, fy) glBegin(GL_POINTS); \
        glVertex2f(fx, fy); \
        glEnd();

#endif //BERRY3D_DRAWS_H
