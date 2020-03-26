#ifndef BERRY3D_BERRY3D_H
#define BERRY3D_BERRY3D_H

#include <GLFW/glfw3.h>
#include "math.h"

namespace Berry3D {
    class Berry3D {
    public:
        Berry3D() { }
        int render();
    private:
        GLFWwindow* win;
    };
}


#endif //BERRY3D_BERRY3D_H
