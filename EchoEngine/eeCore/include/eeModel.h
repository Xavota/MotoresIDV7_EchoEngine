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
  loadFromMeshes(Vector<SPtr<Mesh>> meshes);
  virtual bool
  loadFromMeshes(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                 const Vector<SPtr<Texture>>& textures);

 private:
  Vector<Pair<SPtr<Mesh>, uint8>> m_meshes;
  Vector<SPtr<Texture>> m_textures;
};
}
