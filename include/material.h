#ifndef BERRY3D_MATERIAL_H
#define BERRY3D_MATERIAL_H

#include "math.h"
#include "color.h"
#include "Bitmap.h"

namespace Berry3D {
    class Material {
    public:
        Material(Color c, float ka, float kd, float ks, float power)
        : color(c),
        ka(ka), kd(kd), ks(ks), power(power),
        ra(c.vec * ka), rd(c.vec * kd), rs(c.vec * ks)
        { }
        Color color;// 表面颜色
        float ka, kd, ks, power;// 环境光反射系数, 散射光反射系数, 镜面反射光反射系数, 镜面反射指数
        Color ra, rd, rs;// 环境光, 散射光, 镜面反射光颜色
    };
}


#endif //BERRY3D_MATERIAL_H
