#ifndef GLE_TRANSFORM_HPP
#define GLE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace GLEngine
{

class Transform
{
public:
    Transform();
    Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);

    void SetPosition(const glm::vec3 &position);
    void SetEulerAngles(const glm::vec3 &rotation); // 0 - 360 (degrees)
    void SetRotation(const glm::quat &rotation);
    void SetScale(const glm::vec3 &scale);

    void RotateEulerAngles(const glm::vec3 &rotation); // 0 - 360 (degrees)

    glm::vec3 GetPosition() const;
    glm::vec3 GetEulerAngles() const; // 0 - 360 (degrees)
    glm::quat GetRotation() const;
    glm::vec3 GetScale() const;
    glm::mat4 GetMatrix();

    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);
    static glm::mat4 CreateTranslationMatrix(const glm::vec3 &position);
    static glm::mat4 CreateRotationMatrix(const glm::vec3 &rotation);
    static glm::mat4 CreateRotationMatrix(const glm::quat &rotation);
    static glm::mat4 CreateScaleMatrix(const glm::vec3 &scale);

private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
    glm::mat4 m_transformationMatrix;

    bool m_transformationMatrixNeedsRecalc;
};

} // namespace GLEngine

#endif