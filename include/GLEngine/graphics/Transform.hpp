#ifndef GLE_TRANSFORM_HPP
#define GLE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

namespace GLEngine
{

class Transform
{
public:
    Transform();
    Transform(const glm::vec3 &position);
    Transform(const glm::vec3 &position, const glm::vec3 &rotation);
    Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);

    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation); // 0 - 360 (degrees)
    void SetQuaternion(const glm::quat &quaternion);
    void SetScale(const glm::vec3 &scale);

    void Translate(const glm::vec3 &translation);
    void Rotate(const float &pitch, const float &yaw, const float &roll);
    void Rotate(const glm::vec3 &rotationXYZ);

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::quat GetQuaternion(); // not const as m_quaternion will be calculated and set here if needed
    glm::vec3 GetScale() const;

    glm::vec3 GetRight(); // not const as RecalcTransformationMatrix will be called here
    glm::vec3 GetUp(); // not const as RecalcTransformationMatrix will be called here
    glm::vec3 GetForward(); // not const as RecalcTransformationMatrix will be called here

    glm::mat4 GetMatrix();
    glm::mat4 GetMatrixInverse();
    glm::mat4 GetNormalMatrix();
    void RecalcTransformationMatrixIfNeeded(); // Note that this will be automatically run

    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    //static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);
    static glm::mat4 CreateTranslationMatrix(const glm::vec3 &position);
    static glm::mat4 CreateRotationMatrix(const glm::vec3 &rotation);
    //static glm::mat4 CreateRotationMatrix(const glm::quat &rotation);
    static glm::mat4 CreateScaleMatrix(const glm::vec3 &scale);

    std::string DebugStr() const;
    std::string DebugStr(uint precision) const;

private:
    void m_Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    void m_RecalcRightUpForward();

    glm::vec3 m_position;
    //glm::vec3 m_rotation;
    glm::quat m_quaternion;
    glm::vec3 m_scale;

    glm::vec3 m_right;
    glm::vec3 m_up;
    glm::vec3 m_forward;

    glm::mat4 m_transformationMatrix;
    glm::mat4 m_inverseTransformationMatrix;
    glm::mat4 m_normalMatrix;

    bool m_transformationMatrixNeedsRecalc; // transformationMatrix is calculated lazily, it only gets calculated when requested or explicitly told to recalculate
};

} // namespace GLEngine

#endif
