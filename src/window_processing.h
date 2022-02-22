
#ifndef LEARNOPENGL_WINDOW_PROCESSING_H
#define LEARNOPENGL_WINDOW_PROCESSING_H
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
#endif //LEARNOPENGL_WINDOW_PROCESSING_H
