#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/math/math.hpp"

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
glm::mat4 Transform::GetMatrix()
{
    if (m_transformationMatrixNeedsRecalc)
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotationMatrix = glm::toMat4(eulerToQuat(glm::radians(m_rotation)));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

        m_transformationMatrix = translationMatrix * (rotationMatrix * scaleMatrix);
        m_transformationMatrixNeedsRecalc = false;
    }

    return m_transformationMatrix;
}

} // namespace GLEngine