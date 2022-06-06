#include "eeOGLPixelShader.h"
#pragma warning(push)
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <eeLogger.h>

#include "eeFile.h"

namespace eeEngineSDK {
OGLPixelShader::~OGLPixelShader()
{
  release();
}
bool
OGLPixelShader::compileFromFile(const String& fileName)
{
  File shaderFile;
  shaderFile.OpenFile(fileName, OPEN_TYPE::kReadOnly);
  String shaderString;
  shaderString = shaderFile.GetContent();
  bool r = compileFromString(shaderString);
  shaderFile.Close();
  return r;
}
bool
OGLPixelShader::compileFromString(const String& shaderString)
{
  m_shader = glCreateShader(GL_FRAGMENT_SHADER);
  auto shStr = shaderString.c_str();
  glShaderSource(m_shader, 1, &shStr, nullptr);
  glCompileShader(m_shader);

  int  success;
  char infoLog[512];
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(m_shader, 512, nullptr, infoLog);
    String infoLogStr = infoLog;
    Logger::instance().FileLog("Pixel Shader failed to compile: " + infoLogStr, "Logs/Genera_Log.txt", WARNING_LEVEL::kError);
    return false;
  }
  return true;
}
void
OGLPixelShader::release()
{
  glDeleteShader(m_shader);
}
}