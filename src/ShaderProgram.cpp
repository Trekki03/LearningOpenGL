#include "ShaderProgram.h"
#include <fstream>
#include <glad/glad.h>
#include <iostream>

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    std::string vertexShaderSource = GetShaderSrcStringFromFile(vertexShaderPath);
    std::string fragmentShaderSource = GetShaderSrcStringFromFile(fragmentShaderPath);

    m_programID = glCreateProgram();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    SetShaderSource(vertexShader, vertexShaderSource.c_str());
    CompileShader(vertexShader);
    AttachShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    SetShaderSource(fragmentShader, fragmentShaderSource.c_str());
    CompileShader(fragmentShader);
    AttachShader(fragmentShader);

    LinkShader();

    DeleteShader(vertexShader);
    DeleteShader(fragmentShader);

}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(m_programID);
}

std::string ShaderProgram::GetShaderSrcStringFromFile(const std::string &path)
{
    std::ifstream stream(path);
    std::string line, sourceCode;

    while (std::getline(stream, line))
    {
        sourceCode += (line + "\n");
    }
    return sourceCode;
}

void ShaderProgram::SetShaderSource(unsigned int shaderID, const char* shaderSrcString)
{
    glShaderSource(shaderID, 1, &shaderSrcString, nullptr);
}

void ShaderProgram::CompileShader(unsigned int shaderID)
{
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
    if(!m_result)
    {
        glGetShaderInfoLog(shaderID, 512, nullptr, m_log);
        std::cout << "[Shader Compilation Error]:" << std::endl << m_log << std::endl;
    }
}

void ShaderProgram::AttachShader(unsigned int shaderID) const
{
    glAttachShader(m_programID, shaderID);
}

void ShaderProgram::LinkShader()
{
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
    if(!m_result)
    {
        glGetProgramInfoLog(m_programID, 512, nullptr, m_log);
        std::cout << "[Linking Error]:" << std::endl << m_log << std::endl;
    }
}

void ShaderProgram::DeleteShader(unsigned int shaderID)
{
    glDeleteShader(shaderID);
}

void ShaderProgram::Bind() const
{
    glUseProgram(m_programID);
}
void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::setUniform4f(const char* name, vec4<float> data) const
{
    int uniformLocation = glad_glGetUniformLocation(m_programID, name);
    if(uniformLocation == -1)
    {
        std::cout << "Error while retrieving location of Uniform: " << name << std::endl;
        return;
    }
    Bind();
    glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
}
