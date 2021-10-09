#pragma once
#include "eePrerequisitesCore.h"

namespace eeEngineSDK {
class Model
{
 public: 
  Model() = default;
  virtual 
  ~Model() = default;

  virtual bool
  loadFromFile(const String& fileName) = 0;
  virtual bool
  loadFromMeshes(const Vector<Mesh>& meshes) = 0;

 private:
  Pair<Mesh, uint8> m_meshes;
  Vector<Texture*> m_textures;
};
}
