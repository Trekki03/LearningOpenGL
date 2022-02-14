
#ifndef LEARNOPENGL_TEXTURE2D_H
#define LEARNOPENGL_TEXTURE2D_H

#include <glad/glad.h>

class Texture2D
{
private:
    unsigned int m_textureID{};

public:
    Texture2D(const char *texturePath, GLenum inputFormat, int internalFormat,
              int sAxisWarpMode, int tAxisWarpMode, int downscalingFilter, int upscalingFilter, bool mipmap);

    ~Texture2D();
    void GenerateMipmaps() const;
    unsigned int GetTextureID() const;
    void Bind() const;
    void Unbind() const;
    void SetTextureSlot(int slot);
};


#endif //LEARNOPENGL_TEXTURE2D_H
