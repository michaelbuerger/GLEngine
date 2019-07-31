#ifndef GLE_MATH_HPP
#define GLE_MATH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace GLEngine
{
float degreeClamp(const float &x);
glm::vec3 degreeClamp(const glm::vec3 &v);
glm::quat eulerToQuat(const glm::vec3 &eulerAngles);
} // namespace GLEngine

#endif