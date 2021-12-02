#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/math/math.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace GLEngine
{

Transform::Transform()
{
    this->m_Transform(VEC3F_ZERO, VEC3F_ZERO, VEC3F_ONE);
}
Transform::Transform(const glm::vec3 &position)
{
    this->m_Transform(position, VEC3F_ZERO, VEC3F_ONE);
}
Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation)
{
    this->m_Transform(position, rotation, VEC3F_ONE);
}
Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    this->m_Transform(position, rotation, scale);
}

/* Does initialization work for constructors */
void Transform::m_Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
{
    m_transformationMatrixNeedsRecalc = true;
    m_position = position;
    this->SetRotation(rotation);
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
    m_quaternionNeedsRecalc = true;
    m_rotation = degreeClamp(rotation);
}
void Transform::SetQuaternion(const glm::quat &quaternion)
{
    m_quaternionNeedsRecalc = false; // override need for recalc based on euler angles (as quat is explicitly set here)
    m_quaternion = quaternion;
    this->SetRotation(glm::eulerAngles(m_quaternion));
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
glm::quat Transform::GetQuaternion() // should use internally unless it is known for sure that quaternion does not need to be recalculated
{
    if(m_quaternionNeedsRecalc)
    {
        m_quaternion = eulerToQuat(m_rotation); // doesn't call this->SetQuaternion() as this recalculates eulerAngles

        m_quaternionNeedsRecalc = false;
    }
    return m_quaternion;
}
glm::vec3 Transform::GetScale() const
{
    return m_scale;
}

glm::vec3 Transform::GetRight()
{
    RecalcTransformationMatrixIfNeeded();

    return m_right;
}
glm::vec3 Transform::GetUp()
{
    RecalcTransformationMatrixIfNeeded();

    return m_up;
}
glm::vec3 Transform::GetForward()
{
    RecalcTransformationMatrixIfNeeded();

    return m_forward;
}

glm::mat4 Transform::GetMatrix()
{
    RecalcTransformationMatrixIfNeeded();

    return m_transformationMatrix;
}

glm::mat4 Transform::GetMatrixInverse()
{
    RecalcTransformationMatrixIfNeeded();

    return m_inverseTransformationMatrix;
}

glm::mat4 Transform::GetNormalMatrix()
{
    RecalcTransformationMatrixIfNeeded();

    return m_normalMatrix;
}

void Transform::RecalcTransformationMatrixIfNeeded()
{
    if(m_transformationMatrixNeedsRecalc) 
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotationMatrix = glm::toMat4(this->GetQuaternion());
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

        m_transformationMatrix = translationMatrix * (rotationMatrix * scaleMatrix);
        m_inverseTransformationMatrix = glm::inverse(m_transformationMatrix);
        m_normalMatrix = glm::transpose(m_inverseTransformationMatrix);

        m_right = glm::normalize(glm::vec3(m_inverseTransformationMatrix[0])) * glm::vec3(1.0f, 1.0f, -1.0f);
        m_up = glm::normalize(glm::vec3(m_inverseTransformationMatrix[1])) * glm::vec3(1.0f, 1.0f, 1.0f);
        m_forward = glm::normalize(glm::vec3(m_inverseTransformationMatrix[2])) * glm::vec3(1.0f, 1.0f, -1.0f); // flip z-axis

        m_transformationMatrixNeedsRecalc = false;
    }
}

std::string Transform::DebugStr() const
{
    return this->DebugStr(2);
}

std::string Transform::DebugStr(uint precision) const
{
    std::stringstream strStream;

    strStream << std::fixed << std::setprecision(precision);
    strStream << "Position [";
    strStream << m_position.x;
    strStream << ", ";
    strStream << m_position.y;
    strStream << ", ";
    strStream << m_position.z;
    strStream << "], \n";

    strStream << "Rotation [";
    strStream << m_rotation.x;
    strStream << ", ";
    strStream << m_rotation.y;
    strStream << ", ";
    strStream << m_rotation.z;
    strStream << "], \n";

    strStream << "Scale    [";
    strStream << m_scale.x;
    strStream << ", ";
    strStream << m_scale.y;
    strStream << ", ";
    strStream << m_scale.z;
    strStream << "]";

    return strStream.str();
}

} // namespace GLEngine