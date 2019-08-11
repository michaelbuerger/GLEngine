#ifndef GLE_DIRECTIONAL_LIGHT_HPP
#define GLE_DIRECTIONAL_LIGHT_HPP

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "glm/common.hpp"

namespace GLEngine
{

class DirectionalLight
{
public:
    DirectionalLight(const glm::vec3 &position,
                     const glm::vec3 &ambientMultiplier, const glm::vec3 &diffuseMultiplier, const glm::vec3 &specularMultiplier);

    void Uniform(const ShaderProgram &shaderProgram, const GLuint &structArrayIndex);

    glm::vec3 rotation;

    glm::vec3 ambientMultiplier;
    glm::vec3 diffuseMultiplier;
    glm::vec3 specularMultiplier;
};

} // namespace GLEngine

#endif