#pragma once

#include "IAudioSink.h"

class AudioMultiBuffer;

class BaseAudioSink :
	public IAudioSink
{
public:
	BaseAudioSink(void);
	~BaseAudioSink(void);

	virtual unsigned int takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	virtual void convalidateChunk(unsigned int channel, unsigned int chunkSize);

protected:
	AudioMultiBuffer* mSinkBuffer;
};

