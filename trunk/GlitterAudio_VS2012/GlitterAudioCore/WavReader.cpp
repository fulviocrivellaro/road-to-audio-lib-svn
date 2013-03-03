#include "WavReader.h"
#include "AudioMultiBuffer.h"

WavReader::WavReader(const std::string filename) :
	BaseAudioSource(2, 8192)
{
	mSndFile = sf_open(filename.c_str(), SFM_READ, &mInfo);
}

WavReader::~WavReader(void)
{
	if (mSndFile != NULL)
	{
		sf_close(mSndFile);
	}
}

unsigned int WavReader::processChunk(unsigned int chunkSize)
{
	if (mSndFile != NULL) {

		double* lBuffer; // = new double[chunkSize];
		double* rBuffer; // = new double[chunkSize];

		unsigned int lCount = mSourceBuffer->takeChunk(&lBuffer, 0, chunkSize);
		unsigned int rCount = mSourceBuffer->takeChunk(&rBuffer, 1, chunkSize);

		unsigned int count = std::min(lCount, rCount);
		double* readBuffer = new double[2 * count];
		count = sf_read_double(mSndFile, readBuffer, 2*count) / 2;

		unsigned int ptr = 0;
		for (unsigned int i=0; i<count; i++)
		{
			lBuffer[i] = readBuffer[ptr++];
			rBuffer[i] = readBuffer[ptr++];
		}

		mSourceBuffer->convalidateChunk(0, count);
		mSourceBuffer->convalidateChunk(1, count);

		delete[] readBuffer;
		return count;

	} else {
		return 0;
	}
}