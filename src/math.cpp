#include "../include/math.h"

float Berry3D::sqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int *) &x;
    i = 0x5f375a86 - (i >> 1);
    x = *(float *) &i;
    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);

    return 1 / x;
}
Berry3D::Vector3 Berry3D::intersParmlinePlane(const Parmline3D &parmline, const Plane3D &plane)  {
    auto& p0 = parmline.p0;
    auto& v_ = parmline.v_;
    auto n = plane.n;
    auto d = (plane.p - p0) * n / (v_ * n);
    return (v_ * d) + p0;
}