#pragma once

class IAudioSource
{
public:
	virtual unsigned int getChunk(double** buffer, unsigned int channel, unsigned int chunkSize) = 0;
	virtual void consumeChunk(unsigned int channel, unsigned int chunkSize) = 0;
};