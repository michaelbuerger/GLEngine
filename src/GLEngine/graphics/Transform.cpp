#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/math/math.hpp"

#include <string>

namespace GLEngine
{

Transform::Transform()
{
    m_transformationMatrixNeedsRecalc = true;
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_rotation = degreeClamp(glm::vec3(0.0f, 0.0f, 0.0f));
    m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
}
Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    m_transformationMatrixNeedsRecalc = true;
    m_position = position;
    m_rotation = degreeClamp(rotation);
    m_scale = scale;
}

void Transform::SetPosition(const glm::vec3 &position)
{
    m_transformationMatrixNeedsRecalc = true;
    m_position = position;
}
void Transform::SetRotation(const glm::vec3 &rotation) // 0 - 360 (degrees)
{
    m_transformationMatrixNeedsRecalc = true;
    m_rotation = degreeClamp(rotation);
}
void Transform::SetScale(const glm::vec3 &scale)
{
    m_transformationMatrixNeedsRecalc = true;
    m_scale = scale;
}

void Transform::Translate(const glm::vec3 &translation)
{
    this->SetPosition(this->GetPosition() + translation);
}
void Transform::Rotate(const glm::vec3 &rotation) // 0 - 360 (degrees)
{
    this->SetRotation(this->GetRotation() + rotation);
}

glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::toMat4(eulerToQuat(glm::radians(rotation)));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * (rotationMatrix * scaleMatrix);
}
glm::mat4 CreateTranslationMatrix(const glm::vec3 &position)
{
    return glm::translate(glm::mat4(1.0f), position);
}
glm::mat4 CreateRotationMatrix(const glm::vec3 &rotation)
{
    return glm::toMat4(glm::quat(glm::radians(degreeClamp(rotation))));
}
glm::mat4 CreateScaleMatrix(const glm::vec3 &scale)
{
    return glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Transform::GetPosition() const
{
    return m_position;
}
glm::vec3 Transform::GetRotation() const // 0 - 360 (degrees)
{
    return m_rotation;
}
glm::vec3 Transform::GetScale() const
{
    return m_scale;
}

glm::vec3 Transform::Forward() {
    return glm::normalize(glm::vec3(this->GetMatrix()[2]));
}
/*glm::vec3 Transform::Up() {

}*/

glm::vec3 Transform::ForwardOfInverse() {
    return glm::normalize(glm::vec3(this->GetMatrixInverse()[2]));
}
/*glm::vec3 Transform::UpOfInverse() {

}*/

glm::mat4 Transform::GetMatrix()
{
    if (m_transformationMatrixNeedsRecalc)
    {
        RecalcTransformationMatrix();
        m_transformationMatrixNeedsRecalc = false;
    }

    return m_transformationMatrix;
}

glm::mat4 Transform::GetMatrixInverse() {
    if(m_transformationMatrixNeedsRecalc)
    {
        RecalcTransformationMatrix();
        m_transformationMatrixNeedsRecalc = false;
    }
    return m_inverseTransformationMatrix;
}

glm::mat4 Transform::GetNormalMatrix()
{
    if(m_transformationMatrixNeedsRecalc)
    {
        RecalcTransformationMatrix();
        m_transformationMatrixNeedsRecalc = false;
    }
    return m_normalMatrix;
}

void Transform::RecalcTransformationMatrix() {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
    glm::mat4 rotationMatrix = glm::toMat4(eulerToQuat(glm::radians(m_rotation)));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

    m_transformationMatrix = translationMatrix * (rotationMatrix * scaleMatrix);
    m_inverseTransformationMatrix = glm::inverse(m_transformationMatrix);
    m_normalMatrix = glm::transpose(m_inverseTransformationMatrix);
}

std::string Transform::DebugStr() {
    std::string str = "";
    str.append("[");
    str.append(std::to_string(m_position.x));
    str.append(", ");
    str.append(std::to_string(m_position.y));
    str.append(", ");
    str.append(std::to_string(m_position.z));
    str.append("], ");

    str.append("[");
    str.append(std::to_string(m_rotation.x));
    str.append(", ");
    str.append(std::to_string(m_rotation.y));
    str.append(", ");
    str.append(std::to_string(m_rotation.z));
    str.append("], ");

    str.append("[");
    str.append(std::to_string(m_scale.x));
    str.append(", ");
    str.append(std::to_string(m_scale.y));
    str.append(", ");
    str.append(std::to_string(m_scale.z));
    str.append("]");

    return str;
}

} // namespace GLEngine