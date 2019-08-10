#ifndef GLE_CAMERA_HPP
#define GLE_CAMERA_HPP

#include "GLEngine/graphics/Transform.hpp"

namespace GLEngine
{

enum ProjectionMode
{
    GLE_CAMERA_MODE_PERSPECTIVE,
    GLE_CAMERA_MODE_ORTHOGRAPHIC
};

class Camera
{
public:
    Camera(const Transform &transform);
    Camera(const Transform &transform, const float &fov, const float &aspectRatio, const float &viewDistance, const ProjectionMode &projectionMode);

    void SetTransform(const Transform &transform);
    void SetFov(const float &fov);
    void SetAspectRatio(const float &aspectRatio);
    void SetViewDistance(const float &viewDistance);
    void SetProjectionMode(const ProjectionMode &cameraMode);

    float GetFov() const;
    float GetAspectRatio() const;
    float GetViewDistance() const;
    ProjectionMode GetProjectionMode() const;

    glm::mat4 GetViewMatrix();       // Inverse of transformation matrix
    glm::mat4 GetProjectionMatrix(); // Perspective or Orthographic

    Transform transform;

private:
    float m_fov;
    float m_aspectRatio;
    float m_nearClippingPlane;
    float m_farClippingPlane;

    ProjectionMode m_projectionMode;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    bool m_projectionMatrixNeedsRecalc;

    void RecalcViewMatrix();
    void RecalcProjectionMatrix();
};
} // namespace GLEngine

#endif