#include "GLEngine/math/math.hpp"
#include "GLEngine/logging/Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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
    //GLE_ENGINE_INFO("Degree clamp input Y: {} | Degree clamp output Y: {}", v.y, degreeClamp(v.y));
    return glm::vec3(degreeClamp(v.x), degreeClamp(v.y), degreeClamp(v.z));
}

glm::quat eulerToQuat(const glm::vec3 &eulerAngles) { // takes radians in order XYZ and returns quaternion
    return glm::angleAxis(eulerAngles.x, glm::vec3(1, 0, 0)) 
    * glm::angleAxis(eulerAngles.y, glm::vec3(0, 1, 0)) 
    * glm::angleAxis(eulerAngles.z, glm::vec3(0, 0, 1));
}
} // namespace GLEngine