#pragma once

#include "IAudioSink.h"

class IAudioPlayer : public IAudioSink
{
public:
	// stream commands
	virtual bool open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize) = 0;
	virtual bool close() = 0;
	virtual bool start() = 0;
	virtual bool stop() = 0;
};