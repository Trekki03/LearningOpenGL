#include "Camera.h"

Camera::Camera(glm::vec3 position, float pitch, float yaw, float fov):
        m_pitch(pitch), m_yaw(yaw), m_fov(fov), m_xPos(position.x), m_yPos(position.y), m_zPos(position.z)
{ m_cameraID = (unsigned long long int) this; }

inline void Camera::AddFov(float fov)
{
    m_fov += fov;
    if(fov < 1.0f) { fov = 1.0f; }
    else if (fov > 45.0f) { fov = 45.0f; }
}

inline void Camera::AddPitch(float pitch)
{
    m_pitch += pitch;

    if(pitch > 89.0f) { pitch = 89.0f; }
    else if (pitch < -89.0f) { pitch = -89.0f; }
}

inline void Camera::AddYaw(float yaw)
{ m_yaw += yaw; }

inline void Camera::SetFov(float fov)
{
    m_fov = fov;

    if(fov < 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov > 45.0f)
    {
        fov = 45.0f;
    }
}

inline void Camera::AddXPos(float xPos)
{ m_xPos += xPos; }

inline void Camera::AddYPos(float yPos)
{ m_yPos += yPos; }

inline void Camera::AddZPos(float zPos)
{ m_zPos += zPos; }

inline void Camera::AddPositionVector(glm::vec3 position)
{
    m_xPos += position.x;
    m_yPos += position.y;
    m_zPos += position.z;
}

inline void Camera::SetPitch(float pitch)
{
    m_pitch = pitch;

    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}

inline void Camera::SetYaw(float yaw)
{ m_yaw = yaw; }

inline void Camera::SetXPos(float xPos)
{ m_xPos = xPos; }

inline void Camera::SetYPos(float yPos)
{ m_yPos = yPos; }

inline void Camera::SetZPos(float zPos)
{ m_zPos = zPos; }

inline void Camera::SetPositionVector(glm::vec3 position)
{
    m_xPos = position.x;
    m_yPos = position.y;
    m_zPos = position.z;
}

inline unsigned long long int Camera::GetId() const
{ return m_cameraID;}

inline float Camera::GetFov() const
{ return m_fov; }

inline float Camera::GetYaw() const
{ return m_yaw; }

inline float Camera::GetPitch() const
{ return  m_pitch; }

inline glm::vec3 Camera::GetDirectionVector() const
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    return glm::normalize(direction);
}

inline glm::vec3 Camera::GetPositionVector() const
{ return {m_xPos, m_yPos, m_zPos}; }
