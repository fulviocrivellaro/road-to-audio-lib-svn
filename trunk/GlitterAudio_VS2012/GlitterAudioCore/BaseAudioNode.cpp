#include "BaseAudioNode.h"
#include "AudioMultiBuffer.h"

#include <iostream>

BaseAudioNode::BaseAudioNode(unsigned int nInputChannels, unsigned int nOutputChannels, unsigned int bufferSize)
	: BaseAudioSource(nOutputChannels, bufferSize), BaseAudioSink(nInputChannels, bufferSize)
{
}

unsigned int BaseAudioNode::processChunk(unsigned int chunkSize)
{
	unsigned int count = chunkSize;
	unsigned int nSinkChannels = mSinkBuffer->getNChannels();
	unsigned int nSourceChannels = mSourceBuffer->getNChannels();

	double** input = new double*[nSinkChannels];
	double** output = new double*[nSourceChannels];

	for (unsigned int c=0; c<nSourceChannels; c++)
	{
		count = mSinkBuffer->getChunk(&input[c], c, count);
	}
	for (unsigned int c=0; c<nSinkChannels; c++)
	{
		count = mSourceBuffer->takeChunk(&output[c], c, count);
	}

	// ask for data processing
	this->doProcessChunk(input, output, nSourceChannels, nSinkChannels, count);

	for (unsigned int c=0; c<nSinkChannels; c++)
	{
		mSinkBuffer->consumeChunk(c, count);
	}
	for (unsigned int c=0; c<nSourceChannels; c++)
	{
		mSourceBuffer->convalidateChunk(c, count);
	}

	delete [] input;
	delete [] output;

	return count;
}
