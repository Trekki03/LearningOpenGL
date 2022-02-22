#include "window_processing.h"
#include "glm/glm.hpp"

bool wireMode = false;
bool lastKeyState_V = false;

extern glm::vec3 cameraPos;
extern glm::vec3 direction;
extern glm::vec3 cameraUp;

extern float deltaTime;

extern float pitch;
extern float yaw;
extern float fov;

bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        if(lastKeyState_V)
        {
            return;
        }

        lastKeyState_V = true;
        if (wireMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireMode = false;
        } else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireMode = true;
        }

    }
    else if( (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) && lastKeyState_V)
    {
        lastKeyState_V = false;
    }




    const float cameraSpeed = 2.5 * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * direction;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * direction;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(direction, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(direction, cameraUp)) * cameraSpeed;
    }
}

float lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if(firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = !firstMouse;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    fov -= (float)xOffset;
    if(fov < 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov > 45.0f)
    {
        fov = 45.0f;
    }
}
