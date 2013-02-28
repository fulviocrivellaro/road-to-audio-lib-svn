#pragma once

#include "BaseAudioNode.h"

class AudioMultiBuffer;

class NoiseAdder :
	public BaseAudioNode
{
public:
	NoiseAdder(double noiseGain, unsigned int bufferSize);
	~NoiseAdder(void);
	
	void doProcessChunk(double** input, double** output, unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int chunkSize);

private:
	double mNoiseGain;
};

