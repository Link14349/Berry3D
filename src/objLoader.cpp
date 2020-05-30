#include <string>
#include <iostream>
#include <sstream>
#include "../include/objLoader.h"

Berry3D::Entity *Berry3D::ObjLoader::load() {
    auto entity = new Entity(0);
    float maxRadius2 = 0;
    std::string mod;
    std::vector<Vector3*> ns;
    while (!file.eof()) {
        mod[0] = '0';
        file >> mod;
        switch (mod[0]) {
            case '0': goto END;
            default:
                getline(file, mod);
                break;
            case 'v':
                switch (mod[1]) {
                    case 'n':// vn
                    {
                        float x, y, z;
                        file >> x >> y >> z;
                        ns.push_back(new Vector3(x, y, z));
                        break;
                    }
                    case 't': break;
                    default:
                        float x, y, z;
                        file >> x >> y >> z;
                        float r = x * x + y * y + z * z;
                        if (r > maxRadius2) maxRadius2 = r;
                        entity->points.push_back(new Vector3(x, y, z));
                        break;
                }
                break;
            case 'f':
                std::string vertexInfo;
                file >> vertexInfo;
                auto slashPos = vertexInfo.find('/');
                if (slashPos == std::string::npos) {// 说明是直接的顶点序列
                    int aId = atoi(vertexInfo.c_str()), bId, cId;
                    file >> bId >> cId;
                    entity->planes.push_back(new Entity::PlaneEle(new Vector3(), aId, bId, cId));
                } else {
                    std::string test(vertexInfo.substr(0, slashPos));
                    int aId = atoi(vertexInfo.substr(0, slashPos).c_str()), bId, cId;
                    vertexInfo.erase(0, slashPos + 1);
                    slashPos = vertexInfo.find('/');
                    vertexInfo.erase(0, slashPos + 1);
                    int nId = atoi(vertexInfo.c_str());
#define BERRY3D_OBJ_LOAD_FACE_GET(l) file >> vertexInfo; slashPos = vertexInfo.find('/'); l##Id = atoi(vertexInfo.substr(0, slashPos).c_str()); vertexInfo.erase(0, slashPos);
                    BERRY3D_OBJ_LOAD_FACE_GET(b)
                    BERRY3D_OBJ_LOAD_FACE_GET(c)
                    nId--, aId--, bId--, cId--;
                    // (ns[nId]->x + 1) * 0.5, (ns[nId]->y + 1) * 0.5, (ns[nId]->z + 1) * 0.5)
                    entity->planes.push_back(new Entity::PlaneEle(new Vector3(*ns[nId]), aId, bId, cId, new Material(Color(0, 0.5, 1.0), 0.9, 0.8, 0.9, 2)));
                }
                break;
        }
    }
    END:
    for (auto& vec : ns) delete vec;
    entity->maxRadius = sqrt(maxRadius2);
    return entity;
}
