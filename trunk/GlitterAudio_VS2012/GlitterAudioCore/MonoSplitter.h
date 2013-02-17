#pragma once

#include "IAudioNode.h"

class CircularMultiBuffer;

class MonoSplitter :
	public IAudioNode
{
public:
	MonoSplitter(void);
	~MonoSplitter(void);

	void takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize);
	void fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize);

	void processChunk(unsigned int chunkSize);

private:
	CircularMultiBuffer* mInputBuffer;
	CircularMultiBuffer* mOutputBuffer;
};

