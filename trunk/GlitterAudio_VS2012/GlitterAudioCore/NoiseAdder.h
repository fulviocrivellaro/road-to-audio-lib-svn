#pragma once

#include "BaseAudioNode.h"

class AudioMultiBuffer;

class NoiseAdder :
	public BaseAudioNode
{
public:
	NoiseAdder(double noiseGain);
	~NoiseAdder(void);
	
	unsigned int processChunk(unsigned int chunkSize);

private:
	double mNoiseGain;
};

