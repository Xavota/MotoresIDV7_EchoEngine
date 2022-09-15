#pragma once
#include "eePrerequisitesUtilities.h"

namespace eeEngineSDK {
EE_UTILITY_EXPORT void
loadSerializedSize(File& fileToLoad, SIZE_T& sizeToLoad, uint8 sizeTSize);
EE_UTILITY_EXPORT void
serializeString(File& oFile, const String& stringToSerialize);
EE_UTILITY_EXPORT void
loadSerializedString(File& iFile, String& stringToLoad, uint8 sizeOfSizeT);
EE_UTILITY_EXPORT void
getFileName(WString filePath, String& fileName);
}