#include "BaseAudioSink.h"
#include "AudioMultiBuffer.h"

BaseAudioSink::BaseAudioSink(unsigned int nChannels, unsigned int bufferSize)
{
	mSinkBuffer = new AudioMultiBuffer(nChannels, bufferSize);
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
