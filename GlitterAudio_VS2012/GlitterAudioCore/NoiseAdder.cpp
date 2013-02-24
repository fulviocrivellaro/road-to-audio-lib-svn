#include "NoiseAdder.h"

#include "AudioMultiBuffer.h"

#include <iostream>

NoiseAdder::NoiseAdder(double noiseGain)
	: BaseAudioNode()
{
	mNoiseGain = noiseGain;
}

NoiseAdder::~NoiseAdder(void) {}

unsigned int NoiseAdder::processChunk(unsigned int chunkSize)
{
	double* input;
	unsigned int inputCount = mInputBuffer->getChunk(&input, 0, chunkSize);
	
	double* output;
	unsigned int outputCount = mOutputBuffer->takeChunk(&output, 0, chunkSize);

	unsigned int count = std::min(inputCount, outputCount);
	
	// add noise
	for (int i=0; i<count; i++)
	{
		output[i] = .8*input[i] + mNoiseGain * ((double)rand() / 2 + 1);
	}

	mInputBuffer->consumeChunk(0, count);
	mOutputBuffer->convalidateChunk(0, count);

	return count;
}
