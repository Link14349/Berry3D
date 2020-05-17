#ifndef BERRY3D_BMPLOADER_H
#define BERRY3D_BMPLOADER_H

#include <cstdint>
#include "imageLoader.h"

namespace Berry3D {
    class BMPLoader : public ImageLoader {
    public:
        BMPLoader(const std::string& filename) : ImageLoader(filename) { }
        uint8_t* load();
        ~BMPLoader() { fclose(file); }
    private:

    };
}


#endif //BERRY3D_BMPLOADER_H
