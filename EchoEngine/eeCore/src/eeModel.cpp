#include "eeModel.h"
#include "eeResourceManager.h"
#pragma warning(push, 0)   
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

namespace eeEngineSDK {
bool
Model::loadFromFile(const String& fileName)
{
  Assimp::Importer* importer = nullptr;
  const aiScene* scene = nullptr;

  importer = new Assimp::Importer();
  scene = importer->ReadFile
  (
    fileName,
    aiProcess_Triangulate
    | aiProcess_GenSmoothNormals
    | aiProcess_OptimizeMeshes
    | aiProcess_OptimizeGraph
    | aiProcess_JoinIdenticalVertices
    | aiProcess_CalcTangentSpace
    | aiProcessPreset_TargetRealtime_MaxQuality
    | aiProcess_ConvertToLeftHanded
  );
  if (!scene)
  {
    std::cout << importer->GetErrorString() << std::endl;
    return false;
  }

  /*  GET NAME  */
  String name = "";
  bool point = false;
  int32 fileSize = static_cast<int32>(fileName.size());
  for (int32 i = fileSize - 1; i >= 0; --i)
  {
    if (!point)
    {
      if (fileName[i] == '.')
      {
        point = true;
      }
    }
    else
    {
      if (fileName[i] != '/' && fileName[i] != '\\')
        name = fileName[i] + name;
      else
        break;
    }
  }


  /*  GET TEXTURES  */

  m_textures.push_back(ResourceManager::instance().getResourceTexture("Default"));

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
          std::vector<string> completePathDiffuse(1);
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
        std::vector<string> completePathDiffuse(1);
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

      //----Vertices----
  for (uint32 i = 0; i < scene->mNumMeshes; ++i)
  {
    Vector<SimpleVertex> vertices;

    for (uint32 j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
    {
      SimpleVertex v;
      //---Pos
      if (scene->mMeshes[i]->HasPositions())
      {
        v.position.x = scene->mMeshes[i]->mVertices[j].x;
        v.position.y = scene->mMeshes[i]->mVertices[j].y;
        v.position.z = scene->mMeshes[i]->mVertices[j].z;
        v.position.w = 1.0f;
      }
      else
      {
        v.position = Vector4f{};
      }

      //---UVs
      //for (int32 k = 0; k < scene->mMeshes[i]->mMaterialIndex; ++k)
    //	{
      if (scene->mMeshes[i]->HasTextureCoords(0))
      {
        v.uvCoord.x = scene->mMeshes[i]->mTextureCoords[0][j].x;
        v.uvCoord.y = scene->mMeshes[i]->mTextureCoords[0][j].y;
        v.uvCoord.z = 0.0f;
        v.uvCoord.w = 0.0f;
      }
      //}

      //---Norms
      if (scene->mMeshes[i]->HasNormals())
      {
        v.normal.x = scene->mMeshes[i]->mNormals[j].x;
        v.normal.y = scene->mMeshes[i]->mNormals[j].y;
        v.normal.z = scene->mMeshes[i]->mNormals[j].z;
        v.normal.w = 0.0f;
      }
      else
      {
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

    for (uint32 j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
    {
      for (uint32 k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; ++k)
      {
        indices.push_back(scene->mMeshes[i]->mFaces[j].mIndices[k]);
      }
    }/**/
    /*for (int32 j = 0; j < vertices.size(); ++j)
    {
      indices.push_back(j);
    }/**/

    m_meshes.push_back
    (
      make_pair
      (
        ResourceManager::instance().loadMeshFromVertexArray
        (
          vertices,
          indices,
          "Mesh_" + name + std::to_string(m_meshes.size())
        ),
        0
      )
    );

    indices.clear();
    vertices.clear();
  }

  return true;
}
bool
Model::loadFromMeshes(Vector<SPtr<Mesh>> meshes)
{
  m_textures.push_back(ResourceManager::instance().getResourceTexture("Default"));

  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return false;
  }

  for (SPtr<Mesh> m : meshes)
  {
    //m_meshes.push_back(MakePair<Mesh&, uint8>(m, 0u));
    m_meshes.push_back(Pair<SPtr<Mesh>, uint8>(m, static_cast<uint8>(0u)));
  }
  return true;
}
bool
Model::loadFromMeshes(const Vector<Pair<SPtr<Mesh>, uint8>>& meshes,
                      const Vector<SPtr<Texture>>& textures)
{
  m_textures.push_back(ResourceManager::instance().getResourceTexture("Default"));

  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return false;
  }

  m_meshes = meshes;
  uint32 texturesCount = static_cast<uint32>(textures.size());
  for (uint32 i = 0; i < texturesCount; ++i)
  {
    m_textures.push_back(textures[i]);
  }
  return true;
}
Vector<Pair<SPtr<Mesh>, uint8>> Model::getMeshes()
{
  return m_meshes;
}
void Model::setMeshes(Vector<SPtr<Mesh>> meshes)
{
  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return;
  }

  for (SPtr<Mesh> m : meshes)
  {
    //m_meshes.push_back(MakePair<Mesh&, uint8>(m, 0u));
    m_meshes.push_back(Pair<SPtr<Mesh>, uint8>(m, static_cast<uint8>(0u)));
  }
}
void Model::setMeshes(Vector<Pair<SPtr<Mesh>, uint8>> meshes)
{
  if (meshes.empty())
  {
    std::cout << "Empty info loading model" << std::endl;
    return;
  }

  m_meshes = meshes;
}
Vector<SPtr<Texture>> Model::getTextures()
{
  return m_textures;
}
}