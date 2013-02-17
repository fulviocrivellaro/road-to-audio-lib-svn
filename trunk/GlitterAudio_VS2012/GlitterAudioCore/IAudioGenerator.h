#pragma once

#include "IAudioSource.h"

class IAudioGenerator
	: public IAudioSource
{
public:
	virtual void createChunk(unsigned int chunkSize) = 0;
};