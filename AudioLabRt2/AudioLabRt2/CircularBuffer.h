#pragma once

#include <condition_variable>

class CircularBuffer
{
public:
	CircularBuffer(unsigned int nChannels, unsigned int bufferSize);
	~CircularBuffer(void);

	void fillChunk(double** chunk, unsigned int chunkSize);
	void bufferChunk(double** chunk, unsigned int chunkSize);

	unsigned int getNChannels() const;
	unsigned int getBufferSize() const;

	unsigned int countAvailableSamples() const;
	unsigned int countFreeSamples() const;

private:
	unsigned int mNChannels;
	unsigned int mBufferSize;
	unsigned int mAvailable;

	double** mBuffer;

	unsigned int mReadPtr;
	unsigned int mWritePtr;

	std::condition_variable not_full;
    std::condition_variable not_empty;
	std::mutex lock;
};

