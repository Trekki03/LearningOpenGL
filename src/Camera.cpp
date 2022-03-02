#include <iostream>
#include "Camera.h"

Camera::Camera(glm::vec3 position, float pitch, float yaw, float fov):
        m_pitch(pitch), m_yaw(yaw), m_fov(fov), m_xPos(position.x), m_yPos(position.y), m_zPos(position.z)
{ m_cameraID = (unsigned long long int) this; }

void Camera::AddFov(float fov)
{
    float newFov = m_fov + fov;
    if(newFov < 1.0f)
    {
        newFov = 1.0f;
    }
    else if (newFov > 45.0f)
    {
        newFov = 45.0f;
    }
    m_fov = newFov;
}

void Camera::AddPitch(float pitch)
{
    float newPitch = m_pitch + pitch;
    if(newPitch > 89.0f)
    {
        newPitch = 89.0f;
    }
    else if (newPitch < -89.0f)
    {
        newPitch = -89.0f;
    }
    m_pitch = newPitch;
}

void Camera::AddYaw(float yaw)
{ m_yaw += yaw; }

void Camera::SetFov(float fov)
{
    float newFov = fov;
    if(newFov < 1.0f)
    {
        newFov = 1.0f;
    }
    else if (newFov > 45.0f)
    {
        newFov = 45.0f;
    }
    m_fov = newFov;
}

void Camera::AddXPos(float xPos)
{ m_xPos += xPos; }

void Camera::AddYPos(float yPos)
{ m_yPos += yPos; }

void Camera::AddZPos(float zPos)
{ m_zPos += zPos; }

void Camera::AddPositionVector(glm::vec3 position)
{
    m_xPos += position.x;
    m_yPos += position.y;
    m_zPos += position.z;
}

void Camera::SetPitch(float pitch)
{
    float newPitch = pitch;
    if(newPitch > 89.0f)
    {
        newPitch = 89.0f;
    }
    else if (newPitch < -89.0f)
    {
        newPitch = -89.0f;
    }
    m_pitch = newPitch;
}

void Camera::SetYaw(float yaw)
{ m_yaw = yaw; }

void Camera::SetXPos(float xPos)
{ m_xPos = xPos; }

void Camera::SetYPos(float yPos)
{ m_yPos = yPos; }

void Camera::SetZPos(float zPos)
{ m_zPos = zPos; }

void Camera::SetPositionVector(glm::vec3 position)
{
    m_xPos = position.x;
    m_yPos = position.y;
    m_zPos = position.z;
}

unsigned long long int Camera::GetId() const
{ return m_cameraID;}

float Camera::GetFov() const
{ return m_fov; }

float Camera::GetYaw() const
{ return m_yaw; }

float Camera::GetPitch() const
{ return  m_pitch; }

glm::vec3 Camera::GetDirectionVector() const
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    return glm::normalize(direction);
}

glm::vec3 Camera::GetPositionVector() const
{ return {m_xPos, m_yPos, m_zPos}; }
