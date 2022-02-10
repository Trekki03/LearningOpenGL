
#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_ObjectID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &m_ObjectID);
}

void VertexArrayObject::SetVertexAttribPointer(VertexBuffer &vb, unsigned int index, int size, GLenum type, bool normalized, int stride, const void* offset) const
{
    Bind();
    vb.Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    Unbind();
    vb.Unbind();
}

void VertexArrayObject::EnableVertexAttribPointer(unsigned int index) const
{
    Bind();
    glEnableVertexAttribArray(index);
    Unbind();
    glEnableVertexAttribArray(0);
}
void VertexArrayObject::DisableVertexAttribPointer() const
{
    Bind();
    glEnableVertexAttribArray(0);
    Unbind();
}

void VertexArrayObject::AddIndexBuffer(IndexBuffer &ib) const
{
    Bind();
    ib.Bind();
    Unbind();
    ib.Unbind();
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(m_ObjectID);
}

void VertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}
