#include "AudioLink.h"

#include "IAudioSource.h"
#include "IAudioSink.h"

#include <iostream>

AudioLink::AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNode, unsigned int outputChannel)
{
	this->AudioLink::AudioLink(inputNode, inputChannel, &outputNode, &outputChannel, 1);
}

AudioLink::AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNodes[], unsigned int outputChannels[], unsigned int outputNodesCount)
{
	mInputNode = inputNode;
	mInputChannel = inputChannel;
	for (unsigned int i=0; i<outputNodesCount; i++)
	{
		OutputSink sink;
		sink.sink = outputNodes[i];
		sink.channel = outputChannels[i];
		mSinks.push_back(sink);
	}
}

AudioLink::~AudioLink(void)
{
}

unsigned int AudioLink::moveData(unsigned int chunkSize)
{
	double *input;
	unsigned int count = mInputNode->getChunk(&input, mInputChannel, chunkSize);

	double** output = new double*[mSinks.size()];
	for (unsigned int c=0; c<mSinks.size() && count>0; c++)
	{
		count = std::min(count, mSinks[c].sink->takeChunk(&output[c], mSinks[c].channel, count));
	}

	if (count > 0)
	{
		for (unsigned int c=0; c<mSinks.size(); c++)
		{
			for (int i=0; i<count; i++)
			{
				output[c][i] = input[i];
			}
			mSinks[c].sink->convalidateChunk(mSinks[c].channel, count);
		}

	}
	mInputNode->consumeChunk(mInputChannel, count);

	delete[] output;
	return count;
}