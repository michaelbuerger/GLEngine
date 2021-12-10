#ifndef GLE_MATH_HPP
#define GLE_MATH_HPP

#define VEC3F_ZERO glm::vec3(0.0f, 0.0f, 0.0f)
#define VEC3F_ONE glm::vec3(1.0f, 1.0f, 1.0f)

#define VEC3F_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define VEC3F_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define VEC3F_FORWARD glm::vec3(0.0f, 0.0f, -1.0f)

#define QUATF_IDENTITY glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // rotation equivalent to -z heading

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

namespace GLEngine
{
float degreeClamp(const float &x);
glm::vec3 degreeClamp(const glm::vec3 &v);
glm::quat eulerToQuat(const glm::vec3 &eulerAngles);

float sinDegrees(const float &degrees);
float cosDegrees(const float &degrees);
float tanDegrees(const float &degrees);

std::string debugVec3(glm::vec3 vec);
} // namespace GLEngine

#endif