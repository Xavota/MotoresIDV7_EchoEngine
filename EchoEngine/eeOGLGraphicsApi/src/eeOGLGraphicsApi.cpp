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
OGLGraphicsApi::clearRenderTargets(const Vector<WPtr<Texture>>& /*rtvs*/,
                                   Color /*screenColor*/)
{
}
void
OGLGraphicsApi::cleanDepthStencils(const Vector<WPtr<Texture>>& /*dsvs*/)
{
}
void
OGLGraphicsApi::setRenderTargets(const Vector<WPtr<Texture>>& /*rtvs*/,
                                 WPtr<Texture> /*dsv*/)
{
}
void
OGLGraphicsApi::unsetRenderTargets()
{
}
void
OGLGraphicsApi::setTextures(const Vector<WPtr<Texture>>& textures, uint32 startSlot)
{
  static uint32 startTextIndex = GL_TEXTURE0;
  
  static auto& memoryMan = MemoryManager::instance();
  
  Vector<WPtr<OGLTexture>> texVec;
  for (auto& t : textures) {
    auto tex = memoryMan.reinterpretPtr<OGLTexture>(t.lock());
  
    if (tex) {
      texVec.push_back(tex);
    }
  }
  
  auto texCount = static_cast<uint32>(texVec.size());
  for (uint32 i = 0; i < texCount; ++i) {
    glActiveTexture(GL_TEXTURE0 + startSlot + i);
    glBindTexture(GL_TEXTURE_2D, texVec[i].lock()->getShaderResource());
  }
}
void
OGLGraphicsApi::unsetTextures(uint32 /*textureCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::unsetVSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::unsetPSConstantBuffers(uint32 /*buffersCount*/, uint32 /*startSlot*/)
{
}
void
OGLGraphicsApi::setVertexBuffers(const Vector<WPtr<VertexBuffer>>& buffers,
                                 const Vector<uint32>& /*offsets*/,
                                 uint32 /*startSlot*/)
{
  auto& memoryMan = MemoryManager::instance();
  for (auto& b : buffers) {
    auto oglBuffer = memoryMan.reinterpretPtr<OGLVertexBuffer>(b.lock());

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
OGLGraphicsApi::unsetIndexBuffer()
{
}
void
OGLGraphicsApi::setViewports(const Vector<ViewportDesc>& descs)
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
OGLGraphicsApi::setShaderPrograms(WPtr<VertexShader> vertexShader,
                                  WPtr<HullShader> hullShader,
                                  WPtr<DomainShader> domainShader,
                                  WPtr<PixelShader> pixelShader)
{
  auto& memoryMan = MemoryManager::instance();
  auto oglVShader = memoryMan.reinterpretPtr<OGLVertexShader>(vertexShader.lock());
  auto oglPShader = memoryMan.reinterpretPtr<OGLPixelShader>(pixelShader.lock());

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