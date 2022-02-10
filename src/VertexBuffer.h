#ifndef LEARNOPENGL_VERTEXBUFFER_H
#define LEARNOPENGL_VERTEXBUFFER_H

#include "glad/glad.h"

class VertexBuffer
{
private:
    unsigned int m_bufferID;
public:
    VertexBuffer(const void* dataArray, unsigned int size, GLenum usage);
    ~VertexBuffer();
    void Bind() const;
    inline void Unbind() ;
};


#endif //LEARNOPENGL_VERTEXBUFFER_H
