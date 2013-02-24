#include "BaseAudioSink.h"
#include "AudioMultiBuffer.h"

BaseAudioSink::BaseAudioSink(void)
{
	mInputBuffer = new AudioMultiBuffer(1, 8192);
}

BaseAudioSink::~BaseAudioSink(void)
{
	delete mInputBuffer;
}

unsigned int BaseAudioSink::takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return mInputBuffer->takeChunk(buffer, channel, chunkSize);
}

void BaseAudioSink::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	mInputBuffer->convalidateChunk(channel, chunkSize);
}
