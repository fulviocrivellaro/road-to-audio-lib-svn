#include "AudioMultiBuffer.h"
#include <iostream>

AudioMultiBuffer::AudioMultiBuffer(unsigned int nChannels, unsigned int bufferSize)
{
	mNChannels = nChannels;
	mBufferSize = bufferSize;
	
	// allocate buffer
	mBuffer = new double*[mNChannels];
	for (int c=0; c<mNChannels; c++)
	{
		mBuffer[c] = new double[mBufferSize];
	}

	// initialize pointers
	mReadPtr = new unsigned int[mNChannels];
	mWritePtr = new unsigned int[mNChannels];
	mAvailable = new unsigned int[mNChannels];
	for (int c=0; c<mNChannels; c++)
	{
		mReadPtr[c] = 0;
		mWritePtr[c] = 0;
		mAvailable[c] = 0;
	}
}


AudioMultiBuffer::~AudioMultiBuffer(void)
{
	// free memory for each channel
	for (int c=0; c<mNChannels; c++)
	{
		delete[] mBuffer[c];
	}
	// free root
	delete[] mBuffer;

	// free pointers
	delete[] mReadPtr;
	delete[] mWritePtr;
	delete[] mAvailable;
}

// read from buffer
unsigned int AudioMultiBuffer::getChunk(double** chunk, unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	unsigned int count;
	if (mReadPtr[channel] <= mWritePtr[channel])
	{
		count = mAvailable[channel];
	} else {
		count = mBufferSize + mWritePtr[channel] - mReadPtr[channel];
	}
	count = std::min(count, chunkSize);

	*chunk = &mBuffer[channel][(mReadPtr[channel])];
	return count;
}

void AudioMultiBuffer::consumeChunk(unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	// update read pointer
	mReadPtr[channel] += chunkSize;
	mReadPtr[channel] %= mBufferSize;
	// update sample count
	mAvailable[channel] -= chunkSize;

	// notify other lock
	//not_full.notify_one();
}

// read from buffer (TODO: restore synchronous read)
//void AudioMultiBuffer::fillChunk(double* chunk, unsigned int channel, unsigned int chunkSize)
//{
//	std::unique_lock<std::mutex> l(lock);
//
//	not_empty.wait(l, [this, &chunkSize, channel]()
//	{
//		return mAvailable[channel] >= chunkSize;
//	});
//
//
//	for (unsigned int i=0; i<chunkSize; i++)
//	{
//		chunk[i] = mBuffer[channel][(i+mReadPtr[channel])%mBufferSize];
//	}
//
//	// update read pointer
//	mReadPtr[channel] += chunkSize;
//	mReadPtr[channel] %= mBufferSize;
//	// update sample count
//	mAvailable[channel] -= chunkSize;
//
//	// notify other lock
//	not_full.notify_one();
//}

// write to buffer
unsigned int AudioMultiBuffer::takeChunk(double** chunk, unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	unsigned int count;
	if (countFreeSamples(channel) == 0)
	{
		count = 0;
	} else {
		count = std::min(mBufferSize-mWritePtr[channel], chunkSize);
	}

	*chunk = &mBuffer[channel][(mWritePtr[channel])];
	return count;
}


void AudioMultiBuffer::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	// update write pointer
	mWritePtr[channel] += chunkSize;
	mWritePtr[channel] %= mBufferSize;
	// update sample count
	mAvailable[channel] += chunkSize;

	// notify other lock
	//not_empty.notify_one();
}

// write to buffer (TODO: restore synchronous write)
//void AudioMultiBuffer::bufferChunk(double* chunk, unsigned int channel, unsigned int chunkSize)
//{
//	std::unique_lock<std::mutex> l(lock);
//
//	not_full.wait(l, [this, &chunkSize, channel]()
//	{
//		return this->countFreeSamples(channel) >= chunkSize;
//	});
//
//	for (unsigned int i=0; i<chunkSize; i++)
//	{
//		double val = chunk[i];
//		mBuffer[channel][(i+mWritePtr[channel])%mBufferSize] = val;
//	}
//	
//	// update write pointer
//	mWritePtr[channel] += chunkSize;
//	mWritePtr[channel] %= mBufferSize;
//	// update sample count
//	mAvailable[channel] += chunkSize;
//
//	// notify other lock
//	not_empty.notify_one();
//}

unsigned int AudioMultiBuffer::getNChannels() const
{
	return mNChannels;
}

unsigned int AudioMultiBuffer::getBufferSize() const
{
	return mBufferSize;
}

//unsigned int AudioMultiBuffer::countAvailableSamples() const
//{
//	unsigned int count = mAvailable[0];
//	for (unsigned int i=1; i<mNChannels; i++)
//	{
//		count = std::min(count, mAvailable[i]);
//	}
//	return count;
//}

unsigned int AudioMultiBuffer::countAvailableSamples(unsigned int channel) const
{
	return mAvailable[channel];
}

//unsigned int AudioMultiBuffer::countFreeSamples() const
//{
//	unsigned int count = mBufferSize - mAvailable[0];
//	for (unsigned int i=1; i<mNChannels; i++)
//	{
//		count = std::min(count, mBufferSize - mAvailable[i]);
//	}
//	return count;
//}

unsigned int AudioMultiBuffer::countFreeSamples(unsigned int channel) const
{
	return mBufferSize - mAvailable[channel];
}