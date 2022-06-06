#include "eeOGLIndexBuffer.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace eeEngineSDK {
OGLIndexBuffer::OGLIndexBuffer(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
}
OGLIndexBuffer::~OGLIndexBuffer()
{
  release();
}
bool
OGLIndexBuffer::initData(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
  if (!IndexBuffer::initData(dataSize, batchSize, data)) {
    return false;
  }

  glGenBuffers(1, &m_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize,
               reinterpret_cast<const void*>(data),
               GL_STATIC_DRAW);

  return true;
}
void
OGLIndexBuffer::updateData(const Byte* data)
{
  IndexBuffer::updateData(data);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size(),
               reinterpret_cast<const void*>(data),
               GL_STATIC_DRAW);
}
void
OGLIndexBuffer::release()
{
  glDeleteBuffers(1, &m_buffer);
}
void
OGLIndexBuffer::set()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}
}