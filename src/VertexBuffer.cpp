//
// Created by trekk on 10.02.2022.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* dataArray, unsigned int size, GLenum usage)
{
    glGenBuffers(1, &m_bufferID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, dataArray, usage);
    Unbind();
}

VertexBuffer::~VertexBuffer()
{
    Unbind();
    glDeleteBuffers(1, &m_bufferID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

inline void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


