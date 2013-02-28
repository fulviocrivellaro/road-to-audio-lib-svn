#include "BaseAudioSink.h"
#include "AudioMultiBuffer.h"

BaseAudioSink::BaseAudioSink(void)
{
	mSinkBuffer = new AudioMultiBuffer(1, 8192);
}

BaseAudioSink::~BaseAudioSink(void)
{
	delete mSinkBuffer;
}

unsigned int BaseAudioSink::takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return mSinkBuffer->takeChunk(buffer, channel, chunkSize);
}

void BaseAudioSink::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	mSinkBuffer->convalidateChunk(channel, chunkSize);
}
