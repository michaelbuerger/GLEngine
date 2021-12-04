#include "GLEngine/math/math.hpp"
#include "GLEngine/logging/Log.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cmath>
#include <string>
#include <sstream>

namespace GLEngine
{
float degreeClamp(const float &x)
{
    if(x < 0) // only calculate clamped value if needed
    {
        return 360 - fmodf32(-x, 360);
    }

    if(x > 360)  // only calculate clamped value if needed
    {
        return 0 + fmodf32(x, 360);
    }

    return x;
}

glm::vec3 degreeClamp(const glm::vec3 &v)
{
    //GLE_ENGINE_INFO("Degree clamp input Y: {} | Degree clamp output Y: {}", v.y, degreeClamp(v.y));
    return glm::vec3(degreeClamp(v.x), degreeClamp(v.y), degreeClamp(v.z));
}

glm::quat eulerToQuat(const glm::vec3 &eulerAngles) { // takes euler angles in degrees (in order XYZ) and returns quaternion
    return glm::angleAxis(glm::radians(eulerAngles.x), glm::vec3(1, 0, 0)) 
    * glm::angleAxis(glm::radians(eulerAngles.y), glm::vec3(0, 1, 0)) 
    * glm::angleAxis(glm::radians(eulerAngles.z), glm::vec3(0, 0, 1));
}

float sinDegrees(const float &degrees)
{
    return glm::sin(glm::radians(degrees));
}

float cosDegrees(const float &degrees)
{
    return glm::cos(glm::radians(degrees));
}

float tanDegrees(const float &degrees)
{
    return glm::tan(glm::radians(degrees));
}

std::string debugVec3(glm::vec3 vec)
{
    std::stringstream strStream;
    strStream << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return strStream.str();
}
} // namespace GLEngine