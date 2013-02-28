#include "NoiseAdder.h"

#include "AudioMultiBuffer.h"

#include <iostream>

NoiseAdder::NoiseAdder(double noiseGain, unsigned int bufferSize)
	: BaseAudioNode(1, 1, bufferSize)
{
	mNoiseGain = noiseGain;
}

NoiseAdder::~NoiseAdder(void) {}

/*unsigned int NoiseAdder::processChunk(unsigned int chunkSize)
{
	double* input;
	unsigned int inputCount = mSinkBuffer->getChunk(&input, 0, chunkSize);
	
	double* output;
	unsigned int outputCount = mSourceBuffer->takeChunk(&output, 0, chunkSize);

	unsigned int count = std::min(inputCount, outputCount);
	
	// add noise
	for (int i=0; i<count; i++)
	{
		output[i] = .8*input[i] + mNoiseGain * ((double)rand() / 2 + 1);
	}

	mSinkBuffer->consumeChunk(0, count);
	mSourceBuffer->convalidateChunk(0, count);

	return count;
}*/

void NoiseAdder::doProcessChunk(double** input, double** output, unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int chunkSize)
{
	// take for granted that nInputChannels == nOutputChannels
	for (unsigned int c=0; c<nInputChannels; c++)
	{
		for (int i=0; i<chunkSize; i++)
		{
			output[c][i] = .8*input[c][i] + mNoiseGain * ((double)rand() / 2 + 1);
		}
	}
}