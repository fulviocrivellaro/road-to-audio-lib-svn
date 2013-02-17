#pragma once

class IAudioSource;
class AudioDevice;

class IAudioSink
{
public:
	virtual void takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize) = 0;
};