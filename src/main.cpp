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

              //Front
              -0.5f,   -0.5f,  0.5f,    0.0f,   0.0f,    // 0
              0.5f,    -0.5f,  0.5f,    1.0f,   0.0f,    // 1
              0.5f,   0.5f,  0.5f,   1.0f,  1.0f,   // 2
              -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,   // 3

              //Right Side
              0.5f,   -0.5f, 0.5f,   0.0f,  0.0f,   // 4
              0.5,    -0.5f, -0.5f,  1.0f,  0.0f,   // 5
              0.5f,   0.5f,  -0.5f,  1.0f,  1.0f,   // 6
              0.5f,   0.5f,  0.5f,   0.0f,  1.0f,   // 7

              //Back
              0.5f,   -0.5f, -0.5f,  0.0f,  0.0f,   // 8
              -0.5f,  -0.5f, -0.5f,  1.0f,  0.0f,   // 9
              -0.5f,  0.5f,  -0.5f,  1.0f,  1.0f,   // 10
              0.5f,   0.5f,  -0.5f,  0.0f,  1.0f,   // 11

              //Left Side
              -0.5f,  -0.5f, -0.5f,  0.0f,  0.0f,   // 12
              -0.5f,  -0.5f, 0.5f,   1.0f,  0.0f,   // 13
              -0.5f,  0.5f,  0.5f,   1.0f,  1.0f,   // 14
              -0.5f,  0.5f,  -0.5f,  0.0f,  1.0f,   // 15

              //Bottom
              0.5f,   -0.5f, -0.5f,  1.0f,  0.0f,   // 16
              -0.5f,  -0.5f, -0.5f,  0.0f,  0.0f,   // 17
              -0.5f,  -0.5f, 0.5f,   0.0f,  1.0f,   // 18
              0.5f,   -0.5f, 0.5f,   1.0f,  1.0f,   // 19

              //Top
              -0.5f, 0.5f, 0.5f,  0.0f, 0.0f,   // 20
              0.5f,  0.5f, 0.5f,  1.0f, 0.0f,   // 21
              0.5f,  0.5f, -0.5f, 1.0f, 1.0f,   // 22
              -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // 23
    };

    unsigned int indices[] = {

            //Front
            0,   1,   3,
            1,   2,   3,

            //Right Side
            4,   5,   7,
            5,   6,  7,

            //Back
            8,  9,  11,
            9,  10, 11,

            //Left Side
            12, 13, 15,
            13, 14, 15,

            //Bottom
            16, 17, 19,
            17, 18, 19,

            //Top
            20, 21, 23,
            21, 22, 23

    };



    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer ib(indices, sizeof(indices), GL_STATIC_DRAW);

    VertexArrayObject vao;
    vao.AddIndexBuffer(ib);
    vao.SetVertexAttribPointer(vb, 0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
    vao.SetVertexAttribPointer(vb, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    vao.EnableVertexAttribPointer(0);
    vao.EnableVertexAttribPointer(1);

    ShaderProgram basicShader("res/shader/basic.vert", "res/shader/basic.frag");


    Texture2D boxTexture("res/textures/box.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);
    Texture2D logoTexture("res/textures/logo.png", GL_RGBA, GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);


    boxTexture.SetTextureSlot(0);
    logoTexture.SetTextureSlot(1);
    basicShader.LinkTextureSlotToUniform("tex1", 0);
    basicShader.LinkTextureSlotToUniform("tex2", 1);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f,  -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f,  -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f,  -7.5f),
            glm::vec3(1.3f,  -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f,  -2.5f),
            glm::vec3(1.5f,  0.2f,  -1.5f),
            glm::vec3(-1.3f, 1.0f,  -1.5f)
    };

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.Bind();
        basicShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));

        for(unsigned int i = 0; i < 10; i++)
        {
            float angle = 20.0f * (float)i + (float)glfwGetTime() * 20.0f;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            basicShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f*sin((float)glfwGetTime())-4.0f));
            basicShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));
        }

        basicShader.Bind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


