#pragma once
#include "IAudioSource.h"

class AudioMultiBuffer;

class BaseAudioSource :
	public IAudioSource
{
public:
	BaseAudioSource(void);
	virtual ~BaseAudioSource(void);

	unsigned int getChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	void consumeChunk(unsigned int channel, unsigned int chunkSize);

protected:
	AudioMultiBuffer* mOutputBuffer;
};

