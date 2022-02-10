#include "window_processing.h"


bool wireMode = false;
bool lastKeyState_W = false;


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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if(lastKeyState_W)
        {
            return;
        }

        lastKeyState_W = true;
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
    else if( (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) && lastKeyState_W)
    {
        lastKeyState_W = false;
    }
}