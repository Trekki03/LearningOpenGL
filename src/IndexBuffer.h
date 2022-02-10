#ifndef LEARNOPENGL_INDEXBUFFER_H
#define LEARNOPENGL_INDEXBUFFER_H

#include "glad/glad.h"

class IndexBuffer
{
private:
    unsigned int m_bufferID;
public:
    IndexBuffer(const void* dataArray, unsigned int size, GLenum usage);
    ~IndexBuffer();
    void Bind() const;
    inline void Unbind() ;
};


#endif //LEARNOPENGL_INDEXBUFFER_H
