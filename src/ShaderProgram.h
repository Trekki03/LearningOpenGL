
#ifndef LEARNOPENGL_SHADERPROGRAM_H
#define LEARNOPENGL_SHADERPROGRAM_H

#include <string>

template<typename T>
struct vec4
{
    T x;
    T y;
    T z;
    T w;
};

class ShaderProgram
{
private:
    unsigned m_programID{};
    char m_log[512];
    int m_result;
public:
    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~ShaderProgram();
    void Bind() const;
    static void Unbind() ;
    void setUniform4f(const char* name, vec4<float> data) const;
    void setUniform1i(const char* name, int data) const;
private:
    static std::string GetShaderSrcStringFromFile(const std::string &path);
    static void SetShaderSource(unsigned int shaderID,  const char* shaderSrcString);
    void CompileShader(unsigned int shaderID);
    void AttachShader(unsigned int shaderID) const;
    void LinkShader();
    static void DeleteShader(unsigned int shaderID);

};


#endif //LEARNOPENGL_SHADERPROGRAM_H
