#pragma once

class IAudioSink
{
public:
	virtual unsigned int takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize) = 0;
	virtual void convalidateChunk(unsigned int channel, unsigned int chunkSize) = 0;
};