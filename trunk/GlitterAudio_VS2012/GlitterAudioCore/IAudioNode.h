#pragma once

#include "IAudioSource.h"
#include "IAudioSink.h"

class IAudioNode
	: public IAudioSource, public IAudioSink
{
public:
	//virtual ~IAudioNode() {};

	//virtual unsigned int getNumAudioInputs() = 0;
	//virtual unsigned int getNumAudioOutputs() = 0;

	//virtual void takeInput(double** data, unsigned int numChannels) = 0;
	//virtual void getOutput(double** data, unsigned int numChannels) = 0;

	virtual void processChunk(unsigned int chunkSize) = 0;
};