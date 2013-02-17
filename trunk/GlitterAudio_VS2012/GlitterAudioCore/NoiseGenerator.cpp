#include "NoiseGenerator.h"

#include "CircularMultiBuffer.h"

NoiseGenerator::NoiseGenerator(double noiseGain)
{
	mNoiseGain = noiseGain;

	mInputBuffer = new CircularMultiBuffer(1, 8192);
	mOutputBuffer = new CircularMultiBuffer(1, 8192);
}

NoiseGenerator::~NoiseGenerator(void)
{
	delete mInputBuffer;
	delete mOutputBuffer;
}

void NoiseGenerator::takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mInputBuffer->bufferChunk(buffer, channel, chunkSize);
}

void NoiseGenerator::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mOutputBuffer->fillChunk(buffer, channel, chunkSize);
}

void NoiseGenerator::processChunk(unsigned int chunkSize)
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
