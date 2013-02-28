#pragma once
#include "IAudioSource.h"

class AudioMultiBuffer;

class BaseAudioSource :
	public IAudioSource
{
public:
	BaseAudioSource(unsigned int nChannels, unsigned int bufferSize);
	virtual ~BaseAudioSource(void);

	unsigned int getChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	void consumeChunk(unsigned int channel, unsigned int chunkSize);

	virtual unsigned int processChunk(unsigned int chunkSize) = 0;

protected:
	AudioMultiBuffer* mSourceBuffer;
};

