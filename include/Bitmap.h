#ifndef BERRY3D_BITMAP_H
#define BERRY3D_BITMAP_H


#include <cstddef>
#include "color.h"

namespace Berry3D {
    class Bitmap {
    public:
        Bitmap(size_t w, size_t h) : len(w * h), width(w), height(h), data(new Color[len]) { }
        size_t len;
        size_t width;
        size_t height;
        Color* data;
    };
}


#endif //BERRY3D_BITMAP_H
