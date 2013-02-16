#pragma once

#include <condition_variable>

class CircularMultiBuffer
{
public:
	CircularMultiBuffer(unsigned int nChannels, unsigned int bufferSize);
	~CircularMultiBuffer(void);

	void fillChunk(double* chunk, unsigned int channel, unsigned int chunkSize);
	void bufferChunk(double* chunk, unsigned int channel, unsigned int chunkSize);

	unsigned int getNChannels() const;
	unsigned int getBufferSize() const;

	unsigned int countAvailableSamples(unsigned int channel) const;
	unsigned int countFreeSamples(unsigned int channel) const;

private:
	unsigned int mNChannels;
	unsigned int mBufferSize;

	double** mBuffer;

	unsigned int* mReadPtr;
	unsigned int* mWritePtr;
	unsigned int* mAvailable;

	std::condition_variable not_full;
    std::condition_variable not_empty;
	std::mutex lock;
};

