#include "eeAudio.h"

namespace eeEngineSDK {
Audio::Audio(const char* path)
{
  // Open file stream for input as binary
  std::ifstream file(path, std::ios::in | std::ios::binary);

  // Read number of channels and sample rate
  file.seekg(22);
  file.read((char*)&numChannels, 2);
  file.read((char*)&samplingRate, 4);
  // Read bits per sample
  uint16 bitsPerSample = 0;
  file.seekg(34);
  file.read((char*)&bitsPerSample, 2);


  // Read size of data in bytes
  uint32 filePos = 28;
  char* chunkID = new char[4];
  memset(chunkID, 0, 4);
  uint32 length = 0;
  while (chunkID[0] != 'd'
      || chunkID[1] != 'a'
      || chunkID[2] != 't'
      || chunkID[3] != 'a') {
    filePos += length + 8;
    file.seekg(filePos);
    file.read(chunkID, 4);
    file.read((char*)&length, 4);
  }
  delete[] chunkID;


  // Allocate array to hold all the data as PCM samples
  count = length / (bitsPerSample / 8);
  data = new float[count];
  int16* readData = new int16[count];
  // Read PCM data
  file.read((char*)readData, length);

  for (uint32 i = 0; i < count; ++i) {
    data[i] = static_cast<float>(readData[i]) / 32768.0f;
  }

  file.close();
}
Audio::~Audio()
{
  delete[] data;
  data = nullptr;
}
}