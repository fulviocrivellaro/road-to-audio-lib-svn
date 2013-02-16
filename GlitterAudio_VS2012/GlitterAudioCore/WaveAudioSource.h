#pragma once

#include <string>
#include <stdio.h>

#include "IAudioSource.h"

class WaveAudioSource :
	public IAudioSource
{
public:
	WaveAudioSource(void);
	~WaveAudioSource(void);

	void fillChunk(double* buffer, unsigned int chunkSize);

	void setFile(std::string path);

private:
	int readNextChunk(double** buffer, unsigned int chunkLength);

	FILE *pFile;

	int mSampleRate;
	short mNumChannels;
	short mBitsPerSample;
	int mFileSize;

	// conversion constants
	int mSignPreservationMask;
	int mSignPreservationVerifier;
	double mNormalizationFactor;
};

