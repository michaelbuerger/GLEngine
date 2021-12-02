#include "GLEngine/graphics/SpotLight.hpp"
#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "glm/common.hpp"

namespace GLEngine
{

SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const float &cutoffDegrees, const float &cutoffOuterDegrees,
                     const glm::vec3 &ambientMultiplier, const glm::vec3 &diffuseMultiplier, const glm::vec3 &specularMultiplier,
                     const float &constant, const float &linear, const float &quadratic)
{
    this->position = position;
    this->direction = direction;
    this->ambientMultiplier = ambientMultiplier;
    this->diffuseMultiplier = diffuseMultiplier;
    this->specularMultiplier = specularMultiplier;
    this->cutoffDegrees = cutoffDegrees;
    this->cutoffOuterDegrees = cutoffOuterDegrees;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void SpotLight::Uniform(const ShaderProgram &shaderProgram, const GLuint &structArrayIndex)
{
    shaderProgram.UniformVec3(("spotLight[" + std::to_string(structArrayIndex) + "].position").c_str(), this->position);
    shaderProgram.UniformVec3(("spotLight[" + std::to_string(structArrayIndex) + "].direction").c_str(), this->direction);
    shaderProgram.UniformFloat(("spotLight[" + std::to_string(structArrayIndex) + "].cutoff").c_str(), glm::cos(glm::radians(this->cutoffDegrees)));
    shaderProgram.UniformFloat(("spotLight[" + std::to_string(structArrayIndex) + "].cutoffOuter").c_str(), glm::cos(glm::radians(this->cutoffOuterDegrees)));
    shaderProgram.UniformVec3(("spotLight[" + std::to_string(structArrayIndex) + "].ambientMultiplier").c_str(), this->ambientMultiplier);
    shaderProgram.UniformVec3(("spotLight[" + std::to_string(structArrayIndex) + "].diffuseMultiplier").c_str(), this->diffuseMultiplier);
    shaderProgram.UniformVec3(("spotLight[" + std::to_string(structArrayIndex) + "].specularMultiplier").c_str(), this->specularMultiplier);
    shaderProgram.UniformFloat(("spotLight[" + std::to_string(structArrayIndex) + "].constant").c_str(), this->constant);
    shaderProgram.UniformFloat(("spotLight[" + std::to_string(structArrayIndex) + "].linear").c_str(), this->linear);
    shaderProgram.UniformFloat(("spotLight[" + std::to_string(structArrayIndex) + "].quadratic").c_str(), this->quadratic);
}

} // namespace GLEngine