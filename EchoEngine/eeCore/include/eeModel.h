#pragma once
#include "eePrerequisitesCore.h"
#include "eeMesh.h"

namespace eeEngineSDK {
class EE_CORE_EXPORT Model
{
 public: 
  Model() = default;
  virtual 
  ~Model() = default;

  virtual bool
  loadFromFile(const String& fileName);
  virtual bool
  loadFromMeshes(const Vector<Mesh&>& meshes);
  virtual bool
  loadFromMeshes(const Vector<Pair<Mesh&, uint8>>& meshes, 
                 Vector<Texture*>& textures);

 private:
  Vector<Pair<Mesh&, uint8>> m_meshes;
  Vector<Texture*> m_textures;
};
}
