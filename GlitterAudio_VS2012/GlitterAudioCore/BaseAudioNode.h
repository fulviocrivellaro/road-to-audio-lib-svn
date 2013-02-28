#pragma once

#include "BaseAudioSource.h"
#include "BaseAudioSink.h"

class BaseAudioNode :
	public BaseAudioSource, public BaseAudioSink
{
public:
	BaseAudioNode::BaseAudioNode();
	virtual ~BaseAudioNode(void) {}

	// node method(s)
	unsigned int processChunk(unsigned int chunkSize);

	virtual void doProcessChunk(double** input, double** output, unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int chunkSize) = 0;

};

