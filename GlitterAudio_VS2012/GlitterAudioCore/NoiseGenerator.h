#pragma once

#include "IAudioNode.h"

class CircularMultiBuffer;

class NoiseGenerator :
	public IAudioNode
{
public:
	NoiseGenerator(double noiseGain);
	~NoiseGenerator(void);

	void takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize);
	void fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize);

	void processChunk(unsigned int chunkSize);

private:
	double mNoiseGain;

	CircularMultiBuffer* mInputBuffer;
	CircularMultiBuffer* mOutputBuffer;
};

