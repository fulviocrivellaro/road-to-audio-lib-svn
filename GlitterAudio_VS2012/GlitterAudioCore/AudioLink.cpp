#include "AudioLink.h"

#include "IAudioSource.h"
#include "IAudioSink.h"

#include <iostream>

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

unsigned int AudioLink::moveData(unsigned int chunkSize)
{
	double *input;
	unsigned int inputCount = mInputNode->getChunk(&input, mInputChannel, chunkSize);

	double *output;
	unsigned int outputCount = mOutputNode->takeChunk(&output, mOutputChannel, chunkSize);

	unsigned int count = std::min(inputCount, outputCount);
	for (int i=0; i<count; i++)
	{
		output[i] = input[i];
	}

	mInputNode->consumeChunk(mInputChannel, count);
	mOutputNode->convalidateChunk(mOutputChannel, count);

	return count;
}