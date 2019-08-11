#ifndef GLE_POINT_LIGHT_HPP
#define GLE_POINT_LIGHT_HPP

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "glm/common.hpp"

namespace GLEngine
{

class PointLight
{
public:
    PointLight(const glm::vec3 position,
               const glm::vec3 &ambientMultiplier, const glm::vec3 &diffuseMultiplier, const glm::vec3 &specularMultiplier,
               const float &constant, const float &linear, const float &quadratic);

    void Uniform(const ShaderProgram &shaderProgram, const GLuint &structArrayIndex);

    glm::vec3 position;

    glm::vec3 ambientMultiplier;
    glm::vec3 diffuseMultiplier;
    glm::vec3 specularMultiplier;

    float constant;
    float linear;
    float quadratic;
};

} // namespace GLEngine

#endif