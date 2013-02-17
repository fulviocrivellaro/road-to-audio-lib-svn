#include "MonoSplitter.h"
#include "CircularMultiBuffer.h"

MonoSplitter::MonoSplitter(void)
{
	mInputBuffer = new CircularMultiBuffer(1, 8192);
	mOutputBuffer = new CircularMultiBuffer(2, 8192);
}

MonoSplitter::~MonoSplitter(void)
{
	delete mInputBuffer;
	delete mOutputBuffer;
}

void MonoSplitter::takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mInputBuffer->bufferChunk(buffer, channel, chunkSize);
}

void MonoSplitter::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mOutputBuffer->fillChunk(buffer, channel, chunkSize);
}

void MonoSplitter::processChunk(unsigned int chunkSize)
{
	double* chunk = new double[chunkSize];

	mInputBuffer->fillChunk(chunk, 0, chunkSize);
	mOutputBuffer->bufferChunk(chunk, 0, chunkSize);
	mOutputBuffer->bufferChunk(chunk, 1, chunkSize);

	delete[] chunk;
}
