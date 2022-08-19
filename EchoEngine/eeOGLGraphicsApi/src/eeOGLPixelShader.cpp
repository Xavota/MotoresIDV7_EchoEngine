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
OGLPixelShader::compileFromFile(const WString& fileName,
                                const String& functionName,
                                const Vector<ShaderMacro>& macroDefinitions)
{
  File shaderFile;
  shaderFile.openFile(fileName, OPEN_TYPE::kReadOnly);
  String shaderString;
  shaderString = shaderFile.getContent();
  bool r = compileFromString(shaderString, functionName, macroDefinitions);
  shaderFile.close();
  return r;
}
bool
OGLPixelShader::compileFromString(const String& shaderString,
                                  const String& /*functionName*/,
                                  const Vector<ShaderMacro>& /*macroDefinitions*/)
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
    Logger::instance().fileLog("Pixel Shader failed to compile: " + infoLogStr, L"Logs/Genera_Log.txt", WARNING_LEVEL::kError);
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