#pragma once

#include "IAudioGenerator.h"
#include "BaseAudioSource.h"

class BaseAudioGenerator
	: public BaseAudioSource, public IAudioGenerator
{
public:
	~BaseAudioGenerator() {}

	unsigned int getChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	void consumeChunk(unsigned int channel, unsigned int chunkSize);
};