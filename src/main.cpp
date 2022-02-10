#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "window_processing.h"
#include "ShaderProgram.h"

int main()
{
    glfwInit();
    //Set OpenGL Context to Version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    //Needed by MacOS
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
            0.5f,    0.5f,   0.0f,  //top right
            0.5f,    -0.5f,  0.0f,  //bottom right
            -0.5f,   -0.5f,   0.0f, //bottom left
            -0.5f,   0.5f,   0.0f //top left
    };

    unsigned int indicesRed[] = {
            0, 1, 3
    };
    unsigned int indicesBlue[] = {
            1, 2, 3
    };


    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer ibRed(indicesRed, sizeof(indicesRed), GL_STATIC_DRAW);
    IndexBuffer ibBlue(indicesBlue, sizeof(indicesBlue), GL_STATIC_DRAW);

    VertexArrayObject vaoRed;
    vaoRed.AddIndexBuffer(ibRed);
    vaoRed.SetVertexAttribPointer(vb, 0, 3, GL_FLOAT, false, 3*sizeof(float), nullptr);
    vaoRed.EnableVertexAttribPointer(0);

    VertexArrayObject vaoBlue;
    vaoBlue.AddIndexBuffer(ibBlue);
    vaoBlue.SetVertexAttribPointer(vb, 0, 3, GL_FLOAT, false, 3*sizeof(float), nullptr);
    vaoBlue.EnableVertexAttribPointer(0);

    ShaderProgram basicRedShader("res/shader/basic.vert", "res/shader/red.frag");
    ShaderProgram basicBlueShader("res/shader/basic.vert", "res/shader/blue.frag");

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vaoRed.Bind();
        basicRedShader.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        vaoBlue.Bind();
        basicBlueShader.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


