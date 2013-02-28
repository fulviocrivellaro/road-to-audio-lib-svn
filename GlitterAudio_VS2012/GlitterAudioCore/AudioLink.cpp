#include "AudioLink.h"

#include "IAudioSource.h"
#include "IAudioSink.h"

#include <iostream>

AudioLink::AudioLink(IAudioSource* source, unsigned int sourceChannel, IAudioSink* sink, unsigned int sinkChannel)
{
	this->AudioLink::AudioLink(source, sourceChannel, &sink, &sinkChannel, 1);
}

AudioLink::AudioLink(IAudioSource* source, unsigned int sourceChannel, IAudioSink* sinks[], unsigned int sinkChannels[], unsigned int sinkCount)
{
	mSource = source;
	mSourceChannel = sourceChannel;
	for (unsigned int i=0; i<sinkCount; i++)
	{
		OutputSink sink;
		sink.sink = sinks[i];
		sink.channel = sinkChannels[i];
		mSinks.push_back(sink);
	}
}

AudioLink::~AudioLink(void)
{
}

unsigned int AudioLink::moveData(unsigned int chunkSize)
{
	double *input;
	unsigned int count = mSource->getChunk(&input, mSourceChannel, chunkSize);

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
	mSource->consumeChunk(mSourceChannel, count);

	delete[] output;
	return count;
}