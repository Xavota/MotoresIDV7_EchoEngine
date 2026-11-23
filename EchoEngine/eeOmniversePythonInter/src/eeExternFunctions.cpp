#include <eeOmniverseApi.h>
#include <eeLogger.h>
#include <eeMemoryManager.h>
#include <eeResourceManager.h>

#include <FreeImage.h>

#include <string>

#define EXPORTABLE __declspec( dllexport )

using eeEngineSDK::Logger;
using eeEngineSDK::MemoryManager;
using eeEngineSDK::ResourceManager;
using eeEngineSDK::OmniverseManager;
using eeEngineSDK::OmniverseApi;


extern "C" {
EXPORTABLE int
pingLib()
{
  return 1;
}

std::string errorMessage;
EXPORTABLE const char*
initializeLib(bool liveEdit)
{
  Logger::startUp();
  MemoryManager::startUp();
  ResourceManager::startUp();
  OmniverseManager::startUp<OmniverseApi>();
#ifdef FREEIMAGE_LIB
  FreeImage_Initialise();
#endif // FREEIMAGE_LIB
  errorMessage = OmniverseManager::instance().init(liveEdit);
  return errorMessage.c_str();
}

std::string localPath;
EXPORTABLE const char*
getUserLocalPath(const char* IPAddress)
{
  localPath = OmniverseManager::instance().getUserLocalPath(IPAddress);
  return localPath.c_str();
}

std::string connUser;
EXPORTABLE const char*
getConnectedUsername(const char* IPAddress)
{
  connUser = OmniverseManager::instance().getConnectedUser(IPAddress);
  return connUser.c_str();
}

EXPORTABLE void
shutDown()
{
#ifdef FREEIMAGE_LIB
  FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB
  OmniverseManager::shutDown();
  ResourceManager::shutDown();
  MemoryManager::shutDown();
  Logger::shutDown();
}


EXPORTABLE void
createStage(const char* stageUrl)
{
  OmniverseManager::instance().createStage(stageUrl);
}
EXPORTABLE void
openStage(const char* stageUrl)
{
  OmniverseManager::instance().openStage(stageUrl);
}
EXPORTABLE void
closeStage()
{
  OmniverseManager::instance().closeStage();
}

EXPORTABLE int
getExisitingSessionsCount()
{
  return (int)OmniverseManager::instance().getExisitingSessionNames().size();
}

std::string sesName;
EXPORTABLE const char*
getExisitingSessionNames(int index)
{
  sesName = "";
  const auto& sessionNames = OmniverseManager::instance().getExisitingSessionNames();
  if (index < (int)sessionNames.size()) {
    sesName = sessionNames[index];
  }
  return sesName.c_str();
}
EXPORTABLE bool
joinSession(const char* sessionName)
{
  return OmniverseManager::instance().joinSession(sessionName);
}
EXPORTABLE bool
createNewSession(const char* sessionName)
{
  return OmniverseManager::instance().createNewSession(sessionName);
}
EXPORTABLE void
stopLiveSession()
{
  OmniverseManager::instance().stopLiveSession();
}
EXPORTABLE const char*
getActiveSessionName()
{
  sesName = OmniverseManager::instance().getActiveSessionName();
  return sesName.c_str();
}

EXPORTABLE void
copyFileToDest(const char* src, const char* dest)
{
  OmniverseManager::instance().copyFileToDest(src, dest);
}

std::string
getImageExt(std::string path)
{
  std::string ext;
  int pathSize = static_cast<int>(path.size());
  for (size_t i = pathSize - 1; i >= 0; --i) {
    if (path[i] == '.') {
      return ext;
    }
    ext = path[i] + ext;
  }
  return "";
}

EXPORTABLE bool
convertImage(const char* srcPath, const char* destPath)
{
  // Image format
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

  // Check the file signature and deduce its format
  fif = FreeImage_GetFileType(srcPath, 0);

  // If still unknown, try to guess the file format from the file extension
  if (fif == FIF_UNKNOWN)
  {
    fif = FreeImage_GetFIFFromFilename(srcPath);
  }

  // If still unkown, return NULL
  if (fif == FIF_UNKNOWN)
  {
    return false;
  }

  // Load texture
  FIBITMAP* dib = FreeImage_Load(fif, srcPath, 0);

  // Convert to RGB format
  dib = FreeImage_ConvertTo32Bits(dib);

  // Get raw data and dimensions
  DWORD width = FreeImage_GetWidth(dib);
  DWORD height = FreeImage_GetHeight(dib);

  if (dib && width != 0 && height != 0)
  {
    bool rState = false;
    std::string destExt = getImageExt(destPath);
    if (destExt == "png") {
      rState = FreeImage_Save(FIF_PNG, dib, destPath);
    }
    else if (destExt == "jpg") {
      rState = FreeImage_Save(FIF_JPEG, dib, destPath);
    }
    else if (destExt == "targa") {
      rState = FreeImage_Save(FIF_TARGA, dib, destPath);
    }
    else if (destExt == "dds") {
      rState = FreeImage_Save(FIF_DDS, dib, destPath);
    }

    FreeImage_Unload(dib);

    return rState;
  }

  return false;
}
}