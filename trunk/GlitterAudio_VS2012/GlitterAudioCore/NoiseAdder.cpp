#include "NoiseAdder.h"

#include "CircularMultiBuffer.h"

NoiseAdder::NoiseAdder(double noiseGain)
{
	mNoiseGain = noiseGain;

	mInputBuffer = new CircularMultiBuffer(1, 8192);
	mOutputBuffer = new CircularMultiBuffer(1, 8192);
}

NoiseAdder::~NoiseAdder(void)
{
	delete mInputBuffer;
	delete mOutputBuffer;
}

void NoiseAdder::takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mInputBuffer->bufferChunk(buffer, channel, chunkSize);
}

void NoiseAdder::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mOutputBuffer->fillChunk(buffer, channel, chunkSize);
}

void NoiseAdder::processChunk(unsigned int chunkSize)
{
	double* chunk = new double[chunkSize];

	mInputBuffer->fillChunk(chunk, 0, chunkSize);
	
	// add noise
	for (int i=0; i<chunkSize; i++)
	{
		chunk[i] += mNoiseGain * ((double)rand() / 2 + 1);
	}

	mOutputBuffer->bufferChunk(chunk, 0, chunkSize);
	
	delete[] chunk;
}
