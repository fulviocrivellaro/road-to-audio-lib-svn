#pragma once

#include "BaseAudioSource.h"
#include "BaseAudioSink.h"

class BaseAudioNode :
	public BaseAudioSource, public BaseAudioSink
{
public:
	BaseAudioNode::BaseAudioNode(unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int bufferSize);
	virtual ~BaseAudioNode(void) {}

	// node method(s)
	unsigned int processChunk(unsigned int chunkSize);

	virtual void doProcessChunk(double** input, double** output, unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int chunkSize) = 0;

};

