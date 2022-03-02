
#ifndef LEARNOPENGL_CAMERACONTROLLER_H
#define LEARNOPENGL_CAMERACONTROLLER_H

#include "Camera.h"
#include <vector>

class CameraController
{
private:
    unsigned int m_activeCameraIndex = 0;
    std::vector<Camera*> m_cameras;
public:
    CameraController() = default;
    void SetActiveCamera(unsigned long long int cameraID);
    unsigned long long int CreateCamera(glm::vec3 initialPosition, float initialPitch, float initialYaw, float initialFov);
    void DeregisterCamera(unsigned long long int cameraID);
    Camera* GetActiveCameraPointer();

    virtual ~CameraController();


};


#endif //LEARNOPENGL_CAMERACONTROLLER_H
