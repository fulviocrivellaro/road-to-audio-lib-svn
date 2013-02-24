#pragma once

#include "IAudioSource.h"
#include "IAudioSink.h"

class IAudioNode
	: public IAudioSource, public IAudioSink
{
public:
	virtual unsigned int processChunk(unsigned int chunkSize) = 0;
};