#include "eeModel.h"

#include <eeLogger.h>

#include "eeResourceManager.h"
#include <eeQuaternion.h>
#include <eeMath.h>
#include "eeSkeletalMesh.h"
#include "eeSkeletal.h"
#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include <eeMemoryManager.h>

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& fileName,
                    const String& name,
                    const Vector<SPtr<Texture>>& textures)
{
  auto* importer = new Assimp::Importer();
  const aiScene* scene = importer->ReadFile
  (
    fileName,
    aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );
  if (!scene) {
    Logger::instance().ConsoleLog(importer->GetErrorString());
    delete importer;
    return false;
  }

  m_name = name;

  /*  GET NAME  */
  //String name;
  //bool point = false;
  //auto fileSize = static_cast<int32>(fileName.size());
  //for (int32 i = fileSize - 1; i >= 0; --i) {
  //  if (!point) {
  //    if (fileName[i] == '.') {
  //      point = true;
  //    }
  //  }
  //  else {
  //    if (fileName[i] != '/' && fileName[i] != '\\') {
  //      name = fileName[i] + name;
  //    }
  //    else { break; }
  //  }
  //}


  /*  GET TEXTURES  */

  /*for (int32 j = 0; j < scene->mNumMeshes; j++)
  {
    m_textures.push_back(vector<Texture>());
  }

  eSTATUS stat;/**/

  /*if (scene->HasMaterials())
  {
    aiString path;

    for (int32 i = 0; i < scene->mNumMaterials; i++)
    {
      int32 meshIndex = -1;
      for (int32 j = 0; j < scene->mNumMeshes; j++)
      {
        if (scene->mMeshes[j]->mMaterialIndex == i)
        {
          meshIndex = j;
        }
      }

      if (meshIndex != -1)
      {
        if (scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {

          aiGetMaterialTexture(scene->mMaterials[i], aiTextureType_DIFFUSE, 0, &path);

          aiString completePath;
          completePath.Append(fileName.c_str());
          completePath.Append("/../../Textures/");
          completePath.Append(path.C_Str());

          aiString completeName;
          completeName.Append("Texture ");
          completeName.Append(completePath.C_Str());
          cout << "\tPath: " << completePath.C_Str() << endl;
          eSTATUS stat = GraphicsModule::TextureManager::CreateTextureFromFile({ completePath.C_Str() }, completeName.C_Str(), Flags, dim);
          if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
          {
            setTexture(meshIndex, GraphicsModule::TextureManager::GetTexture(completeName.C_Str()));
          }
          else
          {
            cout << "Textura no cargada" << endl;
            setTexture(meshIndex, GraphicsModule::TextureManager::GetTexture("Base Texture"));
          }
        }
        else
        {
          Vector<string> completePathDiffuse(1);
          completePathDiffuse[0].append(fileName.c_str());
          completePathDiffuse[0].append("/../../Textures/M_");
          completePathDiffuse[0].append(name.c_str());
          completePathDiffuse[0].append("_Albedo");
          if (dim == eDIMENSION::TEXTURE2D)
            completePathDiffuse[0].append(".jpg");
          else if (dim == eDIMENSION::TEX_CUBE)
          {
#if defined(DX11)
            completePathDiffuse[0].append(".dds");
#elif defined(OGL)

            for (int32 i = 1; i < 6; i++)
            {
              completePathDiffuse.push_back(completePathDiffuse[0]);
              completePathDiffuse[i].append(to_string(i));
              completePathDiffuse[i].append(".jpg");
            }
            completePathDiffuse[0].append("0.jpg");
#endif
          }
          stat = TextureManager::CreateTextureFromFile({ completePathDiffuse }, name + "_Albedo", Flags, dim);
          //GetManager()->getShader().AddPassInputTexture("Lights", "diffuse");
          if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
          {
            for (int32 i = 0; i < scene->mNumMeshes; i++)
            {
              setTexture(i, TextureManager::GetTexture(name + "_Albedo"));
            }
          }
          else if (stat == eSTATUS::FAIL)
          {
            for (int32 i = 0; i < scene->mNumMeshes; i++)
            {
              setTexture(i, TextureManager::GetTexture("Base Texture"));
            }
          }
        }
      }
    }/**/
    /*  }
      else
      {
        Vector<string> completePathDiffuse(1);
        completePathDiffuse[0].append(fileName.c_str());
        completePathDiffuse[0].append("/../../Textures/M_");
        completePathDiffuse[0].append(name.c_str());
        completePathDiffuse[0].append("_Albedo");
        if (dim == eDIMENSION::TEXTURE2D)
          completePathDiffuse[0].append(".jpg");
        else if (dim == eDIMENSION::TEX_CUBE)
        {
    #if defined(DX11)
          completePathDiffuse[0].append(".dds");
    #elif defined(OGL)

          for (int32 i = 1; i < 6; i++)
          {
            completePathDiffuse.push_back(completePathDiffuse[0]);
            completePathDiffuse[i].append(to_string(i));
            completePathDiffuse[i].append(".jpg");
          }
          completePathDiffuse[0].append("0.jpg");
    #endif
        }
        stat = TextureManager::CreateTextureFromFile({ completePathDiffuse }, name + "_Albedo", Flags, dim);
        //GetManager()->getShader().AddPassInputTexture("Lights", "diffuse");
        if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
        {
          for (int32 i = 0; i < scene->mNumMeshes; i++)
          {
            setTexture(i, TextureManager::GetTexture(name + "_Albedo"));
          }
        }
        else if (stat == eSTATUS::FAIL)
        {
          for (int32 i = 0; i < scene->mNumMeshes; i++)
          {
            setTexture(i, TextureManager::GetTexture("Base Texture"));
          }
        }
      }

      string completePathNormal;
      completePathNormal.append(fileName.c_str());
      completePathNormal.append("/../../Textures/M_");
      completePathNormal.append(name.c_str());
      completePathNormal.append("_Normal.jpg");
      stat = TextureManager::CreateTextureFromFile({ completePathNormal }, name + "_Normal", Flags, dim);
      //GetManager()->getShader().AddPassInputTexture("Lights", "diffuse");
      if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture(name + "_Normal"));
        }
      }
      else if (stat == eSTATUS::FAIL)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture("Base Normal"));
        }
      }

      string completePathSpecular;
      completePathSpecular.append(fileName.c_str());
      completePathSpecular.append("/../../Textures/M_");
      completePathSpecular.append(name.c_str());
      completePathSpecular.append("_Metallic.jpg");
      stat = TextureManager::CreateTextureFromFile({ completePathSpecular }, name + "_Specular", Flags, dim);
      //GetManager()->getShader().AddPassInputTexture("Lights", "diffuse");
      if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture(name + "_Specular"));
        }
      }
      else if (stat == eSTATUS::FAIL)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture("Base Texture"));
        }
      }

      string completePathAO;
      completePathAO.append(fileName.c_str());
      completePathAO.append("/../../Textures/M_");
      completePathAO.append(name.c_str());
      completePathAO.append("_AO.jpg");
      stat = TextureManager::CreateTextureFromFile({ completePathAO }, name + "_AO", Flags, dim);
      //GetManager()->getShader().AddPassInputTexture("Lights", "diffuse");
      if (stat == eSTATUS::OK || stat == eSTATUS::REPITED)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture(name + "_AO"));
        }
      }
      else if (stat == eSTATUS::FAIL)
      {
        for (int32 i = 0; i < scene->mNumMeshes; i++)
        {
          setTexture(i, TextureManager::GetTexture("Base Texture"));
        }
      }
      //TextureManager::CreateTextureFromFile("C:/Users/marad/OneDrive/Documents/GitHub/Graficas1_Mara/Graficos1/bin/Models/Textures/M_Pistola_Normal.jpg", "norm", MODEL_LOAD_FORMAT_BGRA);
      //setTexture(TextureManager::GetTexture("norm"));
      //GetManager()->getShader().AddPassInputTexture("Lights", "normal");
      //TextureManager::CreateTextureFromFile("C:/Users/marad/OneDrive/Documents/GitHub/Graficas1_Mara/Graficos1/bin/Models/Textures/M_Pistola_Metallic.jpg", "spec", MODEL_LOAD_FORMAT_BGRA);
      //setTexture(TextureManager::GetTexture("spec"));
      //GetManager()->getShader().AddPassInputTexture("Lights", "specular");/**/


      /*  LOAD MESH  */

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound( 99999.99f,  99999.99f,  99999.99f);
  float maxDistance = 0.0f;
      //----Vertices----
  for (uint32 i = 0; i < scene->mNumMeshes; ++i) {
    Vector<SimpleVertex> vertices;
    aiMesh* AssimpMesh = scene->mMeshes[i];

    for (uint32 j = 0; j < AssimpMesh->mNumVertices; ++j) {
      SimpleVertex v;
      //---Pos
      if (AssimpMesh->HasPositions()) {
        const aiVector3D& vertex = AssimpMesh->mVertices[j];
        v.position.x = vertex.x;
        maxBound.x = v.position.x > maxBound.x ? v.position.x : maxBound.x;
        minBound.x = v.position.x < minBound.x ? v.position.x : minBound.x;
        v.position.y = vertex.y;
        maxBound.y = v.position.y > maxBound.y ? v.position.y : maxBound.y;
        minBound.y = v.position.y < minBound.y ? v.position.y : minBound.y;
        v.position.z = vertex.z;
        maxBound.z = v.position.z > maxBound.z ? v.position.z : maxBound.z;
        minBound.z = v.position.z < minBound.z ? v.position.z : minBound.z;
        v.position.w = 1.0f;

        float distance = Math::pow(Math::pow(v.position.x, 2.0f)
                                 + Math::pow(v.position.y, 2.0f)
                                 + Math::pow(v.position.z, 2.0f), 0.5f);

        maxDistance = distance > maxDistance ? distance : maxDistance;
      }
      else {
        v.position = Vector4f{};
      }

      //---UVs
      //for (int32 k = 0; k < scene->mMeshes[i]->mMaterialIndex; ++k)
    //	{
      if (AssimpMesh->HasTextureCoords(0)) {
        const aiVector3D& uv = AssimpMesh->mTextureCoords[0][j];
        v.uvCoord.x = uv.x;
        v.uvCoord.y = uv.y;
        v.uvCoord.z = 0.0f;
        v.uvCoord.w = 0.0f;
      }
      //}

      //---Norms
      if (AssimpMesh->HasNormals()) {
        const aiVector3D& norm = AssimpMesh->mNormals[j];
        v.normal.x = norm.x;
        v.normal.y = norm.y;
        v.normal.z = norm.z;
        v.normal.w = 0.0f;
      }
      else {
        v.normal = Vector4f{};
      }

      vertices.push_back(v);
    }

    //---Tan/Bin
    /*for (int32 j = 0; j * 3 + 2 < scene->mMeshes[i]->mNumVertices; ++j)
    {
      aiVector3D deltaPos1 = scene->mMeshes[i]->mVertices[j * 3 + 1] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaPos2 = scene->mMeshes[i]->mVertices[j * 3 + 2] - scene->mMeshes[i]->mVertices[j * 3];
      aiVector3D deltaUV1 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 1] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      aiVector3D deltaUV2 = scene->mMeshes[i]->mTextureCoords[0][j * 3 + 2] - scene->mMeshes[i]->mTextureCoords[0][j * 3];
      float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
      aiVector3D tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
      aiVector3D bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

      vertices[j * 3 + 0].Binormal.x = bitangent.x;
      vertices[j * 3 + 0].Binormal.y = bitangent.y;
      vertices[j * 3 + 0].Binormal.z = bitangent.z;

      vertices[j * 3 + 1].Binormal.x = bitangent.x;
      vertices[j * 3 + 1].Binormal.y = bitangent.y;
      vertices[j * 3 + 1].Binormal.z = bitangent.z;

      vertices[j * 3 + 2].Binormal.x = bitangent.x;
      vertices[j * 3 + 2].Binormal.y = bitangent.y;
      vertices[j * 3 + 2].Binormal.z = bitangent.z;


      vertices[j * 3 + 0].Tangente.x = tangent.x;
      vertices[j * 3 + 0].Tangente.y = tangent.y;
      vertices[j * 3 + 0].Tangente.z = tangent.z;

      vertices[j * 3 + 1].Tangente.x = tangent.x;
      vertices[j * 3 + 1].Tangente.y = tangent.y;
      vertices[j * 3 + 1].Tangente.z = tangent.z;

      vertices[j * 3 + 2].Tangente.x = tangent.x;
      vertices[j * 3 + 2].Tangente.y = tangent.y;
      vertices[j * 3 + 2].Tangente.z = tangent.z;
    }/**/



    Vector<uint32> indices;

    for (uint32 j = 0; j < AssimpMesh->mNumFaces; ++j) {
      for (uint32 k = 0; k < AssimpMesh->mFaces[j].mNumIndices; ++k) {
        indices.push_back(AssimpMesh->mFaces[j].mIndices[k]);
      }
    }/**/
    /*for (int32 j = 0; j < vertices.size(); ++j)
    {
      indices.push_back(j);
    }/**/

    auto& resourseManager = ResourceManager::instance();
    auto& memoryMan = MemoryManager::instance();

    SPtr<Mesh> mesh = memoryMan.newPtr<Mesh>();
    mesh->loadFromArray(vertices, indices);
    m_meshes.emplace_back
    (
      make_pair
      (
        mesh,
        textures.size() > AssimpMesh->mMaterialIndex
        ? textures[AssimpMesh->mMaterialIndex]
        : resourseManager.getResourceTexture("Default")
      )
    );

    indices.clear();
    vertices.clear();
  }

  m_boundSphere.setCenter({ 0.0f, 0.0f, 0.0f });
  m_boundSphere.setRadious(maxDistance);

  m_boundCube.setA({ minBound.x, maxBound.y, maxBound.z });
  m_boundCube.setSize(maxBound - minBound);

  delete importer;
  return true;
}
bool
Model::loadFromMeshes(Vector<SPtr<Mesh>> meshes,
                      const String& name)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  m_name = name;

  auto& resourseManager = ResourceManager::instance();

  for (const auto& m : meshes) {
    //m_meshes.push_back(MakePair<Mesh&, uint8>(m, 0u));
    m_meshes.emplace_back
    (
      Pair<SPtr<Mesh>, SPtr<Texture>>
      (
        m,
        resourseManager.getResourceTexture("Default")
      )
    );
  }
  return true;
}
bool
Model::loadFromMeshes(const Vector<Pair<SPtr<Mesh>, SPtr<Texture>>>& meshes,
                      const String& name)
{
  if (meshes.empty()) {
    Logger::instance().ConsoleLog("Empty info loading model");
    return false;
  }

  m_name = name;

  m_meshes = meshes;
  return true;
}
Vector<Pair<SPtr<Mesh>, SPtr<Texture>>> Model::getMeshes()
{
  return m_meshes;
}
Vector<SPtr<Texture>> Model::getTextures()
{
  Vector<SPtr<Texture>> textures;
  for (auto& m : m_meshes)  {
    textures.push_back(m.second);
  }
  return textures;
}
void Model::setTexture(SPtr<Texture> texture, int32 index)
{
  if (static_cast<int32>(m_meshes.size()) > index) {
    m_meshes[index].second = texture;
  }
}

String
Model::getName()
{
  return m_name;
}

const Sphere&
Model::getBoundingSphere()
{
  return m_boundSphere;
}

const BoxAAB&
Model::getBoundingBox()
{
  return m_boundCube;
}

SPtr<Model> Model::cube = nullptr;
SPtr<Model> Model::tetrahedron = nullptr;
SPtr<Model> Model::cone = nullptr;
SPtr<Model> Model::cylinder = nullptr;
SPtr<Model> Model::sphere = nullptr;
SPtr<Model> Model::capsule = nullptr;
SPtr<Model> Model::SAQ = nullptr;
void Model::initPrimitives()
{
  Vector<SimpleVertex> vertices;
  Vector<uint16> indices;

  vertices = 
  {
    // Front
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f,  1.0f, 0.0f)
    },

    // Back
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  0.0f, -1.0f, 0.0f)
    },

    // Left
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f(-1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Right
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f)
    },

    // Up
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f,  0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f)
    },

    // Down
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 0.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f,  0.5f, 1.0f),
      Vector4f( 1.0f,  1.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f( 0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 1.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    },
    SimpleVertex
    {
      Vector4f(-0.5f, -0.5f, -0.5f, 1.0f),
      Vector4f( 0.0f,  0.0f,  0.0f, 0.0f),
      Vector4f( 0.0f, -1.0f,  0.0f, 0.0f)
    }
  };

  indices =
  {
    0u, 2u, 1u,
    0u, 3u, 2u,

    4u, 6u, 5u,
    4u, 7u, 6u,

    8u, 10u, 9u,
    8u, 11u, 10u,

    12u, 14u, 13u,
    12u, 15u, 14u,

    16u, 18u, 17u,
    16u, 19u, 18u,

    20u, 22u, 21u,
    20u, 23u, 22u
  };

  auto& memoryManager = MemoryManager::instance();

  SPtr<Mesh> cubeMesh = memoryManager.newPtr<Mesh>();
  cubeMesh->loadFromArray
  (
    vertices,
    indices
  );

  cube = memoryManager.newPtr<Model>();
  cube->loadFromMeshes
  (
    Vector<SPtr<Mesh>>
    {
      cubeMesh
    },
    "Cube"
  );
}
}