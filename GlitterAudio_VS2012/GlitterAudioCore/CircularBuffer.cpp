#include "CircularBuffer.h"
#include <iostream>

CircularBuffer::CircularBuffer(unsigned int nChannels, unsigned int bufferSize)
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
	mReadPtr = 0;
	mWritePtr = 0;
	mAvailable = 0;
}


CircularBuffer::~CircularBuffer(void)
{
	// free memory for each channel
	for (int c=0; c<mNChannels; c++)
	{
		delete[] mBuffer[c];
	}
	// free root
	delete[] mBuffer;
}

// read from buffer
void CircularBuffer::fillChunk(double** chunk, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	not_empty.wait(l, [this, &chunkSize]()
	{
		return mAvailable >= chunkSize;
	});


	for (unsigned int c=0; c<mNChannels; c++)
	{
		for (unsigned int i=0; i<chunkSize; i++)
		{
			chunk[c][i] = mBuffer[c][(i+mReadPtr)%mBufferSize];
		}
	}

	// update read pointer
	mReadPtr += chunkSize;
	mReadPtr %= mBufferSize;
	// update sample count
	mAvailable -= chunkSize;

	// notify other lock
	not_full.notify_one();
}

// write to buffer
void CircularBuffer::bufferChunk(double** chunk, unsigned int chunkSize)
{
	std::unique_lock<std::mutex> l(lock);

	not_full.wait(l, [this, &chunkSize]()
	{
		return this->countFreeSamples() >= chunkSize;
	});

	for (unsigned int c=0; c<mNChannels; c++)
	{
		for (unsigned int i=0; i<chunkSize; i++)
		{
			mBuffer[c][(i+mWritePtr)%mBufferSize] = chunk[c][i];
		}
	}
	
	// update write pointer
	mWritePtr += chunkSize;
	mWritePtr %= mBufferSize;
	// update sample count
	mAvailable += chunkSize;

	// notify other lock
	not_empty.notify_one();
}

unsigned int CircularBuffer::getNChannels() const
{
	return mNChannels;
}

unsigned int CircularBuffer::getBufferSize() const
{
	return mBufferSize;
}

unsigned int CircularBuffer::countAvailableSamples() const
{
	return mAvailable;
}

unsigned int CircularBuffer::countFreeSamples() const
{
	return mBufferSize - mAvailable;
}