#include "eeOGLVertexBuffer.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <eeVertex.h>


namespace eeEngineSDK {
OGLVertexBuffer::OGLVertexBuffer(SIZE_T dataSize,
                                 uint32 batchSize,
                                 const Byte* data)
{
  initData(dataSize, batchSize, data);
}
OGLVertexBuffer::~OGLVertexBuffer()
{
  release();
}
bool
OGLVertexBuffer::initData(SIZE_T dataSize, uint32 batchSize, const Byte* data)
{
  if (!VertexBuffer::initData(dataSize, batchSize, data)) {
    return false;
  }

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_buffer);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
  
  int32 offset = 0;
  if (batchSize >= sizeof(SimplexVertex)) {
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(0);
    offset += 4;
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(1);
    offset += 4;
  }
  if (batchSize >= sizeof(ComplexVertex)) {
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(2);
    offset += 4;
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(3);
    offset += 4;
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(4);
    offset += 4;
  }
  if (batchSize > sizeof(ComplexVertex)) {
    auto bonesCount = static_cast<int32>((batchSize - offset) * 0.5f);
    glVertexAttribPointer(5, bonesCount, GL_INT, GL_FALSE, batchSize, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, bonesCount, GL_FLOAT, GL_FALSE, batchSize, (void*)(offset * sizeof(float) + bonesCount * sizeof(int32)));
    glEnableVertexAttribArray(6);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return true;
}
void
OGLVertexBuffer::updateData(const Byte* data)
{
  VertexBuffer::updateData(data);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ARRAY_BUFFER, m_data.size(), data, GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void
OGLVertexBuffer::release()
{
  glDeleteBuffers(1, &m_buffer);
}
void
OGLVertexBuffer::set()
{
  glBindVertexArray(m_vao);
}
}