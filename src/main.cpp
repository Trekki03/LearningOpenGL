#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "window_processing.h"
#include "ShaderProgram.h"
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

    //Texture box
    unsigned int box;
    glGenTextures(1, &box);
    glBindTexture(GL_TEXTURE_2D, box);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("res/textures/box.jpg", &width, &height, &nrChannels, 0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error reading Texture Image (box)" << std::endl;
    }

    stbi_image_free(data);



    //Texture Logo
    unsigned int logo;
    glGenTextures(1, &logo);
    glBindTexture(GL_TEXTURE_2D, logo);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    //width, height, nrChannels already existing
    //data already existing
    data = stbi_load("res/textures/logo.png", &width, &height, &nrChannels, 0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error reading Texture Image (logo)" << std::endl;
    }

    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, box);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, logo);

    basicShader.setUniform1i("tex1", 0);
    basicShader.setUniform1i("tex2", 1);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.Bind();
        basicShader.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


