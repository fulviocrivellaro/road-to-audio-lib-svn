#pragma once

#include "BaseAudioSource.h"
#include "sndfile.h"
#include <string>

class WavReader :
	public BaseAudioSource
{
public:
	WavReader(const std::string filename);
	~WavReader(void);

	unsigned int processChunk(unsigned int chunkSize);

private:
	std::string mFilename;
	SNDFILE* mSndFile;

	SF_INFO mInfo;
};

