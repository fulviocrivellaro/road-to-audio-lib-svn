#include "BaseAudioSource.h"
#include "AudioMultiBuffer.h"

BaseAudioSource::BaseAudioSource(void)
{
	mOutputBuffer = new AudioMultiBuffer(1, 8192);
}

BaseAudioSource::~BaseAudioSource(void)
{
	delete mOutputBuffer;
}

unsigned int BaseAudioSource::getChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return mOutputBuffer->getChunk(buffer, channel, chunkSize);
}

void BaseAudioSource::consumeChunk(unsigned int channel, unsigned int chunkSize)
{
	mOutputBuffer->consumeChunk(channel, chunkSize);
}
