#ifndef BERRY3D_LOADER_H
#define BERRY3D_LOADER_H

#include "item.h"
#include <fstream>
#include <string>

namespace Berry3D {
    class Loader {
    public:
        Loader(const std::string& filename) { file.open(filename, std::ios::in); }
        virtual Entity* load() = 0;
    protected:
        std::fstream file;
    };
}


#endif //BERRY3D_LOADER_H
