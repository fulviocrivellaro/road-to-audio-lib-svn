#include "CircularMultiBuffer.h"
#include <iostream>

CircularMultiBuffer::CircularMultiBuffer(unsigned int nChannels, unsigned int bufferSize)
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


CircularMultiBuffer::~CircularMultiBuffer(void)
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
void CircularMultiBuffer::fillChunk(double* chunk, unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	not_empty.wait(l, [this, &chunkSize, channel]()
	{
		return mAvailable[channel] >= chunkSize;
	});


	for (unsigned int i=0; i<chunkSize; i++)
	{
		chunk[i] = mBuffer[channel][(i+mReadPtr[channel])%mBufferSize];
	}

	// update read pointer
	mReadPtr[channel] += chunkSize;
	mReadPtr[channel] %= mBufferSize;
	// update sample count
	mAvailable[channel] -= chunkSize;

	// notify other lock
	not_full.notify_one();
}

// write to buffer
void CircularMultiBuffer::bufferChunk(double* chunk, unsigned int channel, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	not_full.wait(l, [this, &chunkSize, channel]()
	{
		return this->countFreeSamples(channel) >= chunkSize;
	});

	for (unsigned int i=0; i<chunkSize; i++)
	{
		double val = chunk[i];
		mBuffer[channel][(i+mWritePtr[channel])%mBufferSize] = val;
	}
	
	// update write pointer
	mWritePtr[channel] += chunkSize;
	mWritePtr[channel] %= mBufferSize;
	// update sample count
	mAvailable[channel] += chunkSize;

	// notify other lock
	not_empty.notify_one();
}

unsigned int CircularMultiBuffer::getNChannels() const
{
	return mNChannels;
}

unsigned int CircularMultiBuffer::getBufferSize() const
{
	return mBufferSize;
}

unsigned int CircularMultiBuffer::countAvailableSamples(unsigned int channel) const
{
	return mAvailable[channel];
}

unsigned int CircularMultiBuffer::countFreeSamples(unsigned int channel) const
{
	return mBufferSize - mAvailable[channel];
}