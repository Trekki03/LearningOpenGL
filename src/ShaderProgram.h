
#ifndef LEARNOPENGL_SHADERPROGRAM_H
#define LEARNOPENGL_SHADERPROGRAM_H


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
private:
    static const char* GetShaderSrcStringFromFile(const char* path);
    static void SetShaderSource(unsigned int shaderID,  const char* shaderSrcString);
    void CompileShader(unsigned int shaderID);
    void AttachShader(unsigned int shaderID) const;
    void LinkShader();
    static void DeleteShader(unsigned int shaderID);

};


#endif //LEARNOPENGL_SHADERPROGRAM_H
