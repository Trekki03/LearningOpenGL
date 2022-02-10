
#ifndef LEARNOPENGL_VERTEXARRAYOBJECT_H
#define LEARNOPENGL_VERTEXARRAYOBJECT_H
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArrayObject
{
private:
    unsigned int m_ObjectID{};
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void AddIndexBuffer(IndexBuffer &ib) const;
    void SetVertexAttribPointer(VertexBuffer &vb, unsigned int index, int size, GLenum type, bool normalized, int stride, const void* offset) const;
    void EnableVertexAttribPointer(unsigned int index) const;
    void DisableVertexAttribPointer() const;
    void Bind() const;
    void Unbind() const;
};


#endif //LEARNOPENGL_VERTEXARRAYOBJECT_H
