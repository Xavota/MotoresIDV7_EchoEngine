#include "eeOGLGraphicsApi.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <eeMemoryManager.h>

#include "eeOGLVertexShader.h"
#include "eeOGLPixelShader.h"

#include "eeOGLVertexBuffer.h"
#include "eeOGLIndexBuffer.h"


#include <eeResourceManager.h>

#include <eeFile.h>

namespace eeEngineSDK {
OGLGraphicsApi::~OGLGraphicsApi()
{
  release();
}
bool
OGLGraphicsApi::initialize()
{
  if (!GraphicsApi::initialize()) {
    return false;
  }

  if (!glfwInit()) {
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); ONLY FOR MAC OS X

  return true;
}
bool
OGLGraphicsApi::appIsRunning()
{
  return
  !glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(m_mainWindow->getWindowPtr()));
}
bool
OGLGraphicsApi::initializeBasics()
{
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    return false;
  }
  return true;
}
bool
OGLGraphicsApi::initializeScreen(void* callback,
                                 uint32 witdh,
                                 uint32 height,
                                 const String& displayName)
{
  if (!GraphicsApi::initializeScreen(callback, witdh, height, displayName)) {
    return false;
  }
  return true;
}
void
OGLGraphicsApi::processEvents()
{
  glfwPollEvents();
}
void
OGLGraphicsApi::clearRenderTargets(Vector<SPtr<Texture>> /*rtvs*/,
                                   Color /*screenColor*/)
{
}
void
OGLGraphicsApi::cleanDepthStencils(Vector<SPtr<Texture>> /*dsvs*/)
{
}
void
OGLGraphicsApi::setRenderTargets(Vector<SPtr<Texture>> /*rtvs*/, SPtr<Texture> /*dsv*/)
{
}
void
OGLGraphicsApi::unsetRenderTargets()
{
}
void
OGLGraphicsApi::setTextures(Vector<SPtr<Texture>> textures, uint32 startSlot)
{
  static uint32 startTextIndex = GL_TEXTURE0;
  
  static auto& memoryMan = MemoryManager::instance();
  
  Vector<SPtr<OGLTexture>> texVec;
  for (auto& t : textures) {
    SPtr<OGLTexture> tex = memoryMan.reinterpretPtr<OGLTexture>(t);
  
    if (tex) {
      texVec.push_back(tex);
    }
  }
  
  auto texCount = static_cast<uint32>(texVec.size());
  for (uint32 i = 0; i < texCount; ++i) {
    glActiveTexture(GL_TEXTURE0 + startSlot + i);
    glBindTexture(GL_TEXTURE_2D, texVec[i]->getShaderResource());
  }
}
void
OGLGraphicsApi::unsetTextures(uint32 /*textureCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::setVSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                                     uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::unsetVSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::setPSConstantBuffers(Vector<SPtr<ConstantBuffer>> /*buffers*/,
                                     uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::unsetPSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::setVertexBuffers(Vector<SPtr<VertexBuffer>> buffers,
                                 Vector<uint32> offsets,
                                 uint32 /*startSlot*/)
{
  auto& memoryMan = MemoryManager::instance();
  for (auto& b : buffers) {
    auto oglBuffer = memoryMan.reinterpretPtr<OGLVertexBuffer>(b);

    if (oglBuffer) {
      glBindBuffer(GL_ARRAY_BUFFER, oglBuffer->getResource());
    }
  }
}
void
OGLGraphicsApi::unsetVertexBuffers(uint32 /*buffersCount*/,
                                   uint32 /*startSlot*/)
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void
OGLGraphicsApi::setIndexBuffer(SPtr<IndexBuffer> /*buffers*/,
                               uint32 /*offsets*/)
{
}
void
OGLGraphicsApi::unsetIndexBuffer()
{
}
void
OGLGraphicsApi::setViewports(Vector<ViewportDesc> descs)
{
  for (auto& d : descs) {
    glViewport(static_cast<GLint>(d.topLeftX),
               static_cast<GLint>(d.topLeftY),
               static_cast<GLsizei>(d.width),
               static_cast<GLsizei>(d.height));
  }
  
}
void
OGLGraphicsApi::setPrimitiveTopology(ePRIMITIVE_TOPOLOGY::E /*topology*/)
{
}
void
OGLGraphicsApi::setShaderPrograms(SPtr<VertexShader> vertexShader,
                                  SPtr<HullShader> hullShader,
                                  SPtr<DomainShader> domainShader,
                                  SPtr<PixelShader> pixelShader)
{
  auto& memoryMan = MemoryManager::instance();
  auto oglVShader = memoryMan.reinterpretPtr<OGLVertexShader>(vertexShader);
  auto oglPShader = memoryMan.reinterpretPtr<OGLPixelShader>(pixelShader);

  static uint32 shaderProgram = 0;
  if (oglVShader && oglPShader)
  {
    if (shaderProgram != 0) glDeleteProgram(shaderProgram);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, oglVShader->getShaderIndex());
    glAttachShader(shaderProgram, oglPShader->getShaderIndex());
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
      String infoLogStr = infoLog;
      Logger::instance().FileLog("Shaders failed to link: " + infoLogStr, L"Logs/Genera_Log.txt", WARNING_LEVEL::kError);
    }
    else {
      glUseProgram(shaderProgram);
    }
  }
}
void
OGLGraphicsApi::present(uint32 /*syncInterval*/, uint32 /*flags*/)
{
  glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(m_mainWindow->getWindowPtr()));
}
void
OGLGraphicsApi::release()
{
  glfwTerminate();
}
void
OGLGraphicsApi::resizeWindow(Point2D /*newSize*/)
{
}
void
OGLGraphicsApi::drawIndexed(uint32 indicesCount) const
{
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

EE_EXTERN EE_PLUGIN_EXPORT void
initPlugin()
{
  GraphicsApi::startUp<OGLGraphicsApi>();
}
}