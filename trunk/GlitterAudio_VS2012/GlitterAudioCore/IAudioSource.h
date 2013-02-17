#pragma once

class IAudioSource
{
public:
	virtual void fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize) = 0;
};