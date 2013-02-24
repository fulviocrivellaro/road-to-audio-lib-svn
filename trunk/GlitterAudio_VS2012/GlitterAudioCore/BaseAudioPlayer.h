#pragma once

#include "BaseAudioSink.h"
#include "IAudioPlayer.h"

class BaseAudioPlayer :
	public BaseAudioSink, public IAudioPlayer
{
public:
	virtual ~BaseAudioPlayer(void);

	virtual unsigned int takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	virtual void convalidateChunk(unsigned int channel, unsigned int chunkSize);
};
