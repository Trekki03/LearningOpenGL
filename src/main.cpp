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

glm::vec3 cameraPos;
glm::vec3 direction;
glm::vec3 cameraUp;

float pitch = 90.0f;
float yaw = 0.0f;
float fov = 45.0f;

float deltaTime = 0.0f, lastFrame = 0.0f;

int main()
{
    cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
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

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vao.Bind();

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
        basicShader.SetUniformMatrix4fv("projection", 1, false, glm::value_ptr(projection));

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + direction, cameraUp);
        basicShader.SetUniformMatrix4fv("view", 1, false, glm::value_ptr(view));


        for(unsigned int x = 0; x < 10; x++)
        {
            for (unsigned int y = 0; y < 10; y++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(1.5*x - (5*1.5), 1.5*y-(5*1.5), 0));
                basicShader.SetUniformMatrix4fv("model", 1, false, glm::value_ptr(model));
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
            }
        }

        basicShader.Bind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


