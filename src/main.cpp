#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "window_processing.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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
             0.5f,    0.5f,   0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //top right
             0.5f,   -0.5f,   0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, //bottom right
            -0.5f,   -0.5f,   0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //bottom left
            -0.5f,    0.5f,   0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f  //top left
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };



    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer ib(indices, sizeof(indices), GL_STATIC_DRAW);

    VertexArrayObject vao;
    vao.AddIndexBuffer(ib);
    vao.SetVertexAttribPointer(vb, 0, 3, GL_FLOAT, false, 9 * sizeof(float), nullptr);
    vao.SetVertexAttribPointer(vb, 1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (7 * sizeof(float)));
    vao.EnableVertexAttribPointer(0);
    vao.EnableVertexAttribPointer(1);

    ShaderProgram basicShader("res/shader/basic.vert", "res/shader/basic.frag");


    Texture2D boxTexture("res/textures/box.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);
    Texture2D logoTexture("res/textures/logo.png", GL_RGBA, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);


    boxTexture.SetTextureSlot(0);
    logoTexture.SetTextureSlot(1);
    basicShader.LinkTextureSlotToUniform("tex1", 0);
    basicShader.LinkTextureSlotToUniform("tex2", 1);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.25f, -0.25f, 0.0f));
        trans = glm::rotate(trans, (float)-glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        basicShader.SetUniformMatrix4fv("transform", 1, false, glm::value_ptr(trans));


        vao.Bind();
        basicShader.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


