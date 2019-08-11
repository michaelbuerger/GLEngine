#include "GLEngine/graphics/PointLight.hpp"
#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "glm/common.hpp"

namespace GLEngine
{

PointLight::PointLight(const glm::vec3 position,
                       const glm::vec3 &ambientMultiplier, const glm::vec3 &diffuseMultiplier, const glm::vec3 &specularMultiplier,
                       const float &constant, const float &linear, const float &quadratic)
{
    this->position = position;
    this->ambientMultiplier = ambientMultiplier;
    this->diffuseMultiplier = diffuseMultiplier;
    this->specularMultiplier = specularMultiplier;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void PointLight::Uniform(const ShaderProgram &shaderProgram, const GLuint &structArrayIndex)
{
    shaderProgram.UniformVec3(("pointLight[" + std::to_string(structArrayIndex) + "].position").c_str(), this->position);
    shaderProgram.UniformVec3(("pointLight[" + std::to_string(structArrayIndex) + "].ambientMultiplier").c_str(), this->ambientMultiplier);
    shaderProgram.UniformVec3(("pointLight[" + std::to_string(structArrayIndex) + "].diffuseMultiplier").c_str(), this->diffuseMultiplier);
    shaderProgram.UniformVec3(("pointLight[" + std::to_string(structArrayIndex) + "].specularMultiplier").c_str(), this->specularMultiplier);
    shaderProgram.UniformFloat(("pointLight[" + std::to_string(structArrayIndex) + "].constant").c_str(), this->constant);
    shaderProgram.UniformFloat(("pointLight[" + std::to_string(structArrayIndex) + "].linear").c_str(), this->linear);
    shaderProgram.UniformFloat(("pointLight[" + std::to_string(structArrayIndex) + "].quadratic").c_str(), this->quadratic);
}

} // namespace GLEngine