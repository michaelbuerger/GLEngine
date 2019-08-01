#include "GLEngine/graphics/Camera.hpp"
#include "GLEngine/graphics/Transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GLEngine {
    Camera::Camera(const Transform &transform)
    {
        m_projectionMatrixNeedsRecalc = true;
        this->transform = transform;
        m_fov = 90.0f;
        m_aspectRatio = 16.0f/9.0f;
        m_projectionMode = GLE_CAMERA_MODE_PERSPECTIVE;
        this->SetViewDistance(100.0f);
    }
    Camera::Camera(const Transform &transform, const float &fov, const float &aspectRatio, const float &viewDistance, const ProjectionMode &projectionMode)
    {
        m_projectionMatrixNeedsRecalc = true;
        this->transform = transform;
        m_fov = fov;
        m_aspectRatio = aspectRatio;
        m_projectionMode = projectionMode;
        this->SetViewDistance(viewDistance);
    }

    void Camera::SetFov(const float &fov)
    {
        m_projectionMatrixNeedsRecalc = true;
        m_fov = fov;
    }
    void Camera::SetAspectRatio(const float &aspectRatio)
    {
        m_projectionMatrixNeedsRecalc = true;
        m_aspectRatio = aspectRatio;
    }
    void Camera::SetViewDistance(const float &viewDistance)
    {
        m_projectionMatrixNeedsRecalc = true;
        m_nearClippingPlane = 0.1f;
        m_farClippingPlane = viewDistance+m_nearClippingPlane;
    }
    void Camera::SetProjectionMode(const ProjectionMode &projectionMode)
    {
        m_projectionMatrixNeedsRecalc = true;
        m_projectionMode = projectionMode;
    }

    float Camera::GetFov() const 
    {
        return m_fov;
    }
    float Camera::GetAspectRatio() const 
    {
        return m_aspectRatio;
    }
    float Camera::GetViewDistance() const 
    {
        return m_farClippingPlane - m_nearClippingPlane;
    }
    ProjectionMode Camera::GetProjectionMode() const 
    {
        return m_projectionMode;
    }

    glm::mat4 Camera::GetViewMatrix() // Inverse of transformation matrix
    {
        RecalcViewMatrix();
        return m_viewMatrix;
    }
    glm::mat4 Camera::GetProjectionMatrix() // Perspective or Orthographic
    {
        if(m_projectionMatrixNeedsRecalc)
        {
            RecalcProjectionMatrix();
            m_projectionMatrixNeedsRecalc = false;
        }
        return m_projectionMatrix;
    }

    void Camera::RecalcViewMatrix()
    {
        if(transform.GetScale() != glm::vec3(1.0f, 1.0f, 1.0f)) {
            transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f)); // Override transform scale and account for lazy calculation
        }
        m_viewMatrix = transform.GetMatrixInverse();
    }
    void Camera::RecalcProjectionMatrix()
    {
        if(m_projectionMode == GLE_CAMERA_MODE_ORTHOGRAPHIC)
        {
            m_projectionMatrix = glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, m_nearClippingPlane, m_farClippingPlane);
        }
        if(m_projectionMode == GLE_CAMERA_MODE_PERSPECTIVE)
        {
            m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClippingPlane, m_farClippingPlane);
        }
    }
}