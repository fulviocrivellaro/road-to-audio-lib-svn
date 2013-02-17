#include "AudioLink.h"

#include "IAudioSource.h"
#include "IAudioSink.h"

AudioLink::AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNode, unsigned int outputChannel)
{
	mInputNode = inputNode;
	mInputChannel = inputChannel;
	mOutputNode = outputNode;
	mOutputChannel = outputChannel;
}

AudioLink::~AudioLink(void)
{
}

void AudioLink::moveData(unsigned int chunkSize)
{
	double *chunk = new double[chunkSize];

	// move data
	mInputNode->fillChunk(chunk, mInputChannel, chunkSize);
	mOutputNode->takeChunk(chunk, mOutputChannel, chunkSize);

	delete[] chunk;
}