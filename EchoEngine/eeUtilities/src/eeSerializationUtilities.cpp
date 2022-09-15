#include "eeSerializationUtilities.h"

#include "eeFile.h"
#include "eeStringUtilities.h"

namespace eeEngineSDK {
void
loadSerializedSize(File& fileToLoad, SIZE_T& sizeToLoad, uint8 sizeTSize)
{
  if (sizeTSize == 4) {
    uint32 byte4Size = 0;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&byte4Size),
                         sizeof(uint32));
    sizeToLoad = static_cast<SIZE_T>(byte4Size);
  }
  else if (sizeTSize == 8) {
    uint64 byte8Size = 0;
    fileToLoad.readBytes(reinterpret_cast<Byte*>(&byte8Size),
                         sizeof(uint64));
    sizeToLoad = static_cast<SIZE_T>(byte8Size);
  }
}
void
serializeString(File& oFile, const String& stringToSerialize)
{
  if (oFile.isOpen()) {
    SIZE_T stringLength = stringToSerialize.size();
    oFile.writeBytes(reinterpret_cast<Byte*>(&stringLength), sizeof(SIZE_T));
    for (SIZE_T i = 0; i < stringLength; ++i) {
      char c = stringToSerialize[i];
      oFile.writeBytes(reinterpret_cast<Byte*>(&c), sizeof(char));
    }
  }
}
void
loadSerializedString(File& iFile, String& stringToLoad, uint8 sizeOfSizeT)
{
  if (iFile.isOpen()) {
    SIZE_T readStringLength = 0;
    loadSerializedSize(iFile, readStringLength, sizeOfSizeT);

    stringToLoad.clear();
    for (SIZE_T i = 0; i < readStringLength; ++i) {
      char c = 0;
      iFile.readBytes(reinterpret_cast<Byte*>(&c),
        sizeof(char));

      stringToLoad += c;
    }
  }
}
void
getFileName(WString filePath, String& fileName)
{
  String pathW2S = eeWStringtoString(filePath);
  bool readingName = false;
  auto pathSize = static_cast<int64>(pathW2S.size());
  for (int64 i = pathSize - 1; i >= 0; --i) {
    if (!readingName) {
      if (pathW2S[i] == '.') {
        readingName = true;
      }
    }
    else {
      if (pathW2S[i] == '/' || pathW2S[i] == '\\') {
        break;
      }
      //resourceName.insert(resourceName.end() - 1, pathW2S[i]);
      fileName = pathW2S[i] + fileName;
    }
  }
}
}