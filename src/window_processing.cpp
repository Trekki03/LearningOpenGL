#include "window_processing.h"
#include "glm/glm.hpp"

bool wireMode = false;
bool lastKeyState_V = false;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern float deltaTime;


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
        cameraPos += cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}