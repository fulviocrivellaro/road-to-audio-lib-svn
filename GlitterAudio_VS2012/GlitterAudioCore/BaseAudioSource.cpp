#include "BaseAudioSource.h"
#include "AudioMultiBuffer.h"

BaseAudioSource::BaseAudioSource(unsigned int nChannels, unsigned int bufferSize)
{
	mSourceBuffer = new AudioMultiBuffer(nChannels, bufferSize);
}

BaseAudioSource::~BaseAudioSource(void)
{
	delete mSourceBuffer;
}

unsigned int BaseAudioSource::getChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	/* HP: manage 3..n modes
	 *     1 - lazy:           only asks for specific data on specific channels
	 *     2 - block oriented: keeps channels size aligned
	 *     3 - hard working:   preloads buffer with more samples than asked
	 */

	unsigned int count = mSourceBuffer->getChunk(buffer, channel, chunkSize);
	if (count < chunkSize)
	{
		// if lazy > createChunk(chunkSize - count, channel);
		// if hard working > createChunk(n * (chunkSize - count));
		count += this->processChunk(chunkSize - count);
	}
	return count;
}

void BaseAudioSource::consumeChunk(unsigned int channel, unsigned int chunkSize)
{
	mSourceBuffer->consumeChunk(channel, chunkSize);
}
