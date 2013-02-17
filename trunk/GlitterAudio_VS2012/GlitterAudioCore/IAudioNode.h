#pragma once

#include "IAudioSource.h"
#include "IAudioSink.h"

class IAudioNode
	: public IAudioSource, public IAudioSink
{
public:
	virtual void processChunk(unsigned int chunkSize) = 0;
};