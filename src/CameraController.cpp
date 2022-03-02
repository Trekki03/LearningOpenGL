
#include "CameraController.h"

CameraController::~CameraController()
{
    for(auto & m_camera : m_cameras)
    {
        delete m_camera;
    }
}

void CameraController::SetActiveCamera(unsigned long long int cameraID)
{
    for(unsigned int i = 0; i < m_cameras.size(); i++)
    {
        if(m_cameras.at(i)->GetId() == cameraID)
        {
            m_activeCameraIndex = i;
        }
    }
}

unsigned long long int CameraController::CreateCamera(glm::vec3 initialPosition, float initialPitch, float initialYaw, float initialFov)
{
    Camera* newCamera = new Camera(initialPosition, initialPitch, initialYaw, initialFov);
    m_cameras.push_back(newCamera);
    return newCamera->GetId();
}

void CameraController::DeregisterCamera(unsigned long long int cameraID)
{
    for(unsigned int i = 0; i < m_cameras.size(); i++)
    {
        if(m_cameras.at(i)->GetId() == cameraID)
        {
            m_cameras.erase(m_cameras.begin() + i);
        }
    }
}

Camera* CameraController::GetActiveCameraPointer()
{
    return m_cameras.at(m_activeCameraIndex);
}