#ifndef BERRY3D_IMAGELOADER_H
#define BERRY3D_IMAGELOADER_H

#include <string>
#include <cstdio>

namespace Berry3D {
    class ImageLoader {
    public:
        ImageLoader(const std::string& filename) : file(fopen(filename.c_str(), "rb")) { }
        virtual ~ImageLoader() = 0;
    protected:
        FILE* file;
    };
}


#endif //BERRY3D_IMAGELOADER_H
