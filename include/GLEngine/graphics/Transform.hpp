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
    //Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);

    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::vec3 &rotation); // 0 - 360 (degrees)
    //void SetRotation(const glm::quat &rotation);
    void SetScale(const glm::vec3 &scale);

    void Rotate(const glm::vec3 &rotation); // 0 - 360 (degrees)

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const; // 0 - 360 (degrees)
    //glm::quat GetRotation() const;
    glm::vec3 GetScale() const;

    glm::vec3 Forward();
    //glm::vec3 Up();

    glm::vec3 ForwardOfInverse(); // Forward based on inverse transformation matrix
    //glm::vec3 UpOfInverse(); // Up based on inverse transformation matrix

    glm::mat4 GetMatrix();
    glm::mat4 GetMatrixInverse();
    glm::mat4 GetNormalMatrix();
    void RecalcTransformationMatrix(); // Note that this will be automatically run

    static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
    //static glm::mat4 CreateTransformationMatrix(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);
    static glm::mat4 CreateTranslationMatrix(const glm::vec3 &position);
    static glm::mat4 CreateRotationMatrix(const glm::vec3 &rotation);
    //static glm::mat4 CreateRotationMatrix(const glm::quat &rotation);
    static glm::mat4 CreateScaleMatrix(const glm::vec3 &scale);

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    glm::mat4 m_transformationMatrix;
    glm::mat4 m_inverseTransformationMatrix;
    glm::mat4 m_normalMatrix;

    bool m_transformationMatrixNeedsRecalc;
};

} // namespace GLEngine

#endif