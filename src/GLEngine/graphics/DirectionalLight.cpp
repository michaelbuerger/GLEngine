#include "GLEngine/graphics/DirectionalLight.hpp"
#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "glm/common.hpp"

namespace GLEngine
{

DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &ambientMultiplier, const glm::vec3 &diffuseMultiplier, const glm::vec3 &specularMultiplier)
{
    this->direction = direction;
    this->ambientMultiplier = ambientMultiplier;
    this->diffuseMultiplier = diffuseMultiplier;
    this->specularMultiplier = specularMultiplier;
}

void DirectionalLight::Uniform(const ShaderProgram &shaderProgram, const GLuint &structArrayIndex)
{
    shaderProgram.UniformVec3(("directionalLight[" + std::to_string(structArrayIndex) + "].direction").c_str(), this->direction);
    shaderProgram.UniformVec3(("directionalLight[" + std::to_string(structArrayIndex) + "].ambientMultiplier").c_str(), this->ambientMultiplier);
    shaderProgram.UniformVec3(("directionalLight[" + std::to_string(structArrayIndex) + "].diffuseMultiplier").c_str(), this->diffuseMultiplier);
    shaderProgram.UniformVec3(("directionalLight[" + std::to_string(structArrayIndex) + "].specularMultiplier").c_str(), this->specularMultiplier);
}

} // namespace GLEngine