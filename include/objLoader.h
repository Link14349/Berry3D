#ifndef BERRY3D_OBJLOADER_H
#define BERRY3D_OBJLOADER_H

#include "loader.h"

namespace Berry3D {
    class ObjLoader : public Loader {
    public:
        ObjLoader(const std::string& filename) : Loader(filename) { }
        Entity* load();
    private:
    };
}


#endif //BERRY3D_OBJLOADER_H
