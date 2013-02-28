#include <stdlib.h>
#include <iostream>

#include "AudioMultiBuffer.h"
#include "Thread.h"
#include "IRunnable.h"

// ================================= MULTI-CHANNEL TEST =====================================

class AudioMultiWriter : public IRunnable
{
public:
	AudioMultiWriter::AudioMultiWriter(AudioMultiBuffer *buffer, double** readFrom, int size) { mBuffer = buffer; mReadFrom = readFrom; mSize = size; }
	void AudioMultiWriter::run()
	{
		srand(time(NULL));
		unsigned int nChannels = mBuffer->getNChannels();
		int ptr = 0;
		while (ptr < mSize)
		{
			// choose random length to buffer (checking for overflow)
			int chunk = rand() % 20;
			if (ptr + chunk >= mSize)
			{
				chunk = mSize - ptr;
			}
			std::cout << "WR  > write " << chunk << " samples" << std::endl;

			int count;
			for (unsigned int c=0; c<nChannels; c++)
			{
				double* samples;
				count = mBuffer->takeChunk(&samples, c, chunk);

				for (int i=0; i<count; i++)
				{
					samples[i] = mReadFrom[c][ptr+i];
				}
				mBuffer->convalidateChunk(c, count);
			}

			if (count < chunk)
			{
				std::cout << "WR  > WRITE Buffer underflow" << std::endl;
				std::cout << "WR  > Asked " << chunk << " samples, available " << mBuffer->countFreeSamples(0) << ", returned " << count << std::endl;
				if (count == 0)
				{
					std::cout << "WR  > Underflow detected: sleep 2s" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
			}

			// updates current position tracker
			ptr += count;
			std::chrono::milliseconds waitfor(rand() % 100);
			std::cout << "WR  > wait " << waitfor.count() << " ms" << std::endl;
			std::this_thread::sleep_for(waitfor);
		}
	}
private:
	AudioMultiBuffer *mBuffer;
	double** mReadFrom;
	int mSize;
};

class AudioMultiReader : public IRunnable
{
public:
	AudioMultiReader::AudioMultiReader(AudioMultiBuffer *buffer, double** writeTo, int size, int chunkSize) { mBuffer = buffer; mWriteTo = writeTo; mSize = size; mChunk = chunkSize; }
	void AudioMultiReader::run()
	{
		srand(time(NULL));
		std::chrono::milliseconds waitfor(2000);
		std::cout << "WR  > wait 2 seconds to start..." << std::endl;
		std::this_thread::sleep_for(waitfor);
		unsigned int nChannels = mBuffer->getNChannels();
		int ptr = 0;
		while (ptr < mSize)
		{
			// checks for buffer overflow
			int chunk = mChunk;
			if (ptr + chunk >= mSize)
			{
				chunk = mSize - ptr;
			}
			std::cout << "RD <<< read " << chunk << " samples" << std::endl;

			int count;
			for (unsigned int c=0; c<nChannels; c++)
			{
				double* samples;
				count = mBuffer->getChunk(&samples, c, chunk);

				for (int i=0; i<count; i++)
				{
					mWriteTo[c][ptr+i] = samples[i];
				}
				mBuffer->consumeChunk(c, count);
			}
			
			if (count < chunk)
			{
				std::cout << "RD <<< READ Buffer underflow" << std::endl;
				std::cout << "RD <<< Asked " << chunk << " samples, available " << mBuffer->countAvailableSamples(0) << ", returned " << count << std::endl;
				if (count == 0)
				{
					std::cout << "RD <<< Underflow detected: sleep 2s" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
			}

			// updates current position tracker
			ptr += count;
		}
	}
private:
	int mChunk;
	AudioMultiBuffer *mBuffer;
	double** mWriteTo;
	int mSize;
};

#define MULT_SIZE 32
#define MULT_CHANS 16

/********
	MULTICHANNEL buffer test:
	- buffer is half the size of the samples to be written
	- writer thread starts writing with random chunk size
	- reader thread sleeps for 5000ms befor start reading
	- writer reaches buffer maximum, and waits
	- reader thread awakes, and starts freeing the buffer
	- writer can resume filling
	- reader reads all samples
	- test is processed on all samples:
	  - '.' (dot) means correct sample
	  - 'x' (cross) means wrong sample
	  - final outcome is displayed
*/
int AudioMultiBufferTest()
{
	srand(time(NULL));
	std::cout << "Starting test with " << MULT_CHANS << " channels and " << MULT_SIZE << " samples" << std::endl << std::endl;

	// circular buffer test
	AudioMultiBuffer b(MULT_CHANS, MULT_SIZE/2);
	
	// write data and read data structures
	double **w = new double*[MULT_CHANS];
	double **r = new double*[MULT_CHANS];
	for (int c=0; c<MULT_CHANS; c++)
	{
		w[c] = new double[MULT_SIZE];
		r[c] = new double[MULT_SIZE];
	}

	// fills write data with random values
	std::cout << "Starting generating samples..." << std::endl;
	for (int c=0; c<MULT_CHANS; c++)
	{
		for (int j=0; j<MULT_SIZE; j++) {
			w[c][j] = rand() % 100;
		}
	}

	// creates a writer thread, which runs by its own
	AudioMultiWriter *writer = new AudioMultiWriter(&b, w, MULT_SIZE);
	Thread tWrite(writer);
	tWrite.startAndDetach();
	
	// creates a reader thread, and waits for execution to end
	AudioMultiReader *reader = new AudioMultiReader(&b, r, MULT_SIZE, MULT_SIZE/8);
	Thread tReader(reader);
	tReader.startAndJoin();

	// checks that the read data perfectly match the written ones
	std::cout << "Starting read..." << std::endl;
	bool succeed = true;
	for (int j=0; j<MULT_SIZE; j++)
	{
		for (int c=0; c<MULT_CHANS; c++)
		{
			if (w[c][j] != r[c][j])
			{
				succeed = false;
				std::cout << "x";
			} else {
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}

	// outcome
	std::cout << std::endl;
	std::cout << "Buffer test: " << (succeed?"SUCCESS!!!":"Error...") << std::endl;
	std::cout << std::endl;
	
	// free allocated memory (notice that reader and writer are deleted by Thread object
	for (int c=0; c<MULT_CHANS; c++) {
		free(w[c]);
		free(r[c]);
	}
	free(w);
	free(r);

	return succeed?0:-1;
}

#define SIMPLE_CHANS 2
#define SIMPLE_SIZE  8
void AudioBufferSimpleTest()
{

	std::cout << "Starting SIMPLE test with " << SIMPLE_CHANS << " channel(s) and " << SIMPLE_SIZE << " samples" << std::endl << std::endl;

	// circular buffer test
	AudioMultiBuffer b(SIMPLE_CHANS, SIMPLE_SIZE);

	unsigned int testCount = 8;

	std::cout << "Available free samples for WRITE: " << b.countFreeSamples(0) << std::endl;
	std::cout << "Available free samples for READ:  " << b.countAvailableSamples(0) << std::endl << std::endl;

	for (int c=0; c<SIMPLE_CHANS; c++)
	{
		double* wSample;
		unsigned int wCount = b.takeChunk(&wSample, c, testCount/2);

		std::cout << "Available samples for WRITE: " << wCount << std::endl;
		std::cout << "Writing " << wCount << " samples...";
		for (unsigned int i=0; i<wCount; i++)
		{
			wSample[i] = 10*(c+1) + (double)i;
		}
		std::cout << " Done!" << std::endl << std::endl;

		b.convalidateChunk(c, wCount);
	}

	for (int c=0; c<SIMPLE_CHANS; c++)
	{
		double* rSample;
		unsigned int rCount = b.getChunk(&rSample, c, testCount/2);

		std::cout << "Available samples for READ:  " << rCount << std::endl;
		std::cout << "Reading " << rCount << " samples..." << std::endl;
		for (unsigned int i=0; i<rCount; i++)
		{
			if (10*(c+1)+i != rSample[i]) std::cout << "ERROR >>> ";
			std::cout << "Sample at " << i << ": " << rSample[i] << std::endl;
		}
		std::cout << "Done!" << std::endl << std::endl;

		b.consumeChunk(c, rCount);
	}

	for (int c=0; c<SIMPLE_CHANS; c++)
	{
		double* wSample;
		unsigned int wCount = b.takeChunk(&wSample, c, testCount/2);

		std::cout << "Available samples for WRITE: " << wCount << std::endl;
		std::cout << "Writing " << wCount << " samples...";
		for (unsigned int i=0; i<wCount; i++)
		{
			wSample[i] = 10*(c+1) + 4 +(double)i;
		}
		std::cout << " Done!" << std::endl << std::endl;

		b.convalidateChunk(c, wCount);
	}

	for (int c=0; c<SIMPLE_CHANS; c++)
	{
		double* rSample;
		unsigned int rCount = b.getChunk(&rSample, c, testCount/2);

		std::cout << "Available samples for READ:  " << rCount << std::endl;
		std::cout << "Reading " << rCount << " samples..." << std::endl;
		for (unsigned int i=0; i<rCount; i++)
		{
			if (10*(c+1)+i != rSample[i]) std::cout << "ERROR >>> ";
			std::cout << "Sample at " << i << ": " << rSample[i] << std::endl;
		}
		std::cout << "Done!" << std::endl << std::endl;

		b.consumeChunk(c, rCount);
	}
}