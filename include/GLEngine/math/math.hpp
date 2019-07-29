#ifndef GLE_MATH_HPP
#define GLE_MATH_HPP

#include <glm/glm.hpp>

namespace GLEngine
{
float degreeClamp(const float &x);
glm::vec3 degreeClamp(const glm::vec3 &v);
} // namespace GLEngine

#endif