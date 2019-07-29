#include "GLEngine/math/math.hpp"
#include <glm/glm.hpp>
#include <cmath>

namespace GLEngine
{
float degreeClamp(const float &x)
{
    if (x >= 0)
    {
        return ((x / 360) - std::floor(x / 360)) * 360;
    }
    return 360 - degreeClamp(std::abs(x));
}

glm::vec3 degreeClamp(const glm::vec3 &v)
{
    return glm::vec3(degreeClamp(v.x), degreeClamp(v.y), degreeClamp(v.z));
}
} // namespace GLEngine