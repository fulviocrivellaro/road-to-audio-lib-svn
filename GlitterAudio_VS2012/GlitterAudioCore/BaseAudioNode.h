#pragma once

#include "IAudioNode.h"
#include "BaseAudioSource.h"
#include "BaseAudioSink.h"

class BaseAudioNode :
	public BaseAudioSource, public BaseAudioSink, public IAudioNode
{
public:
	virtual ~BaseAudioNode(void) {}

	// source methods
	unsigned int getChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	void consumeChunk(unsigned int channel, unsigned int chunkSize);

	// sink methods
	virtual unsigned int takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize);
	virtual void convalidateChunk(unsigned int channel, unsigned int chunkSize);

	// node method(s)
	virtual unsigned int processChunk(unsigned int chunkSize) = 0;
	//virtual unsigned int doProcessData(double* input, double* output, unsigned int chunkSize) = 0;
};

