#include <stdlib.h>
#include <iostream>

#include "CircularMultiBuffer.h"
#include "Thread.h"
#include "IRunnable.h"

// ================================= MULTI-CHANNEL TEST =====================================

class CircularMultiWriter : public IRunnable
{
public:
	CircularMultiWriter::CircularMultiWriter(CircularMultiBuffer *buffer, double** readFrom, int size) { mBuffer = buffer; mReadFrom = readFrom; mSize = size; }
	void CircularMultiWriter::run()
	{
		srand(time(NULL));
		unsigned int nChannels = mBuffer->getNChannels();
		int ptr = 0;
		while (ptr < mSize)
		{
			// choose random length to buffer (checking for overflow)
			int chunk = rand() % 200;
			if (ptr + chunk >= mSize)
			{
				chunk = mSize - ptr;
			}
			std::cout << "WR  > write " << chunk << " samples" << std::endl;

			// references double[][] as double** (CircularBuffer format)
			//double* samples = new double[nChannels];
			for (int c=0; c<nChannels; c++)
			{
				mBuffer->bufferChunk(&mReadFrom[c][ptr], c, chunk);
				//samples[c] = &mReadFrom[c][ptr];
			}

			// actually buffers the samples
			//mBuffer->bufferChunk(samples, chunk);
			//delete[] samples;

			// updates current position tracker
			ptr += chunk;
			std::chrono::milliseconds waitfor(rand() % 100);
			std::cout << "WR  > wait " << waitfor.count() << " ms" << std::endl;
			std::this_thread::sleep_for(waitfor);
		}
	}
private:
	CircularMultiBuffer *mBuffer;
	double** mReadFrom;
	int mSize;
};

class CircularMultiReader : public IRunnable
{
public:
	CircularMultiReader::CircularMultiReader(CircularMultiBuffer *buffer, double** writeTo, int size, int chunkSize) { mBuffer = buffer; mWriteTo = writeTo; mSize = size; mChunk = chunkSize; }
	void CircularMultiReader::run()
	{
		srand(time(NULL));
		std::chrono::milliseconds waitfor(5000);
		std::cout << "WR  > wait 5 seconds to start..." << std::endl;
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

			// references double[][] as double** (CircularBuffer format)
			//double** samples = new double*[nChannels];
			for (int c=0; c<nChannels; c++)
			{
				mBuffer->fillChunk(&mWriteTo[c][ptr], c, chunk);
				//samples[c] = &mWriteTo[c][ptr];
			}
			
			// actually fill the local buffer, reading from the Circular
			//mBuffer->fillChunk(samples, chunk);
			//delete[] samples;

			// updates current position tracker
			ptr += chunk;
		}
	}
private:
	int mChunk;
	CircularMultiBuffer *mBuffer;
	double** mWriteTo;
	int mSize;
};

#define MULT_SIZE 1024
#define MULT_CHANS 5

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
int circularMultiBufferTest()
{
	srand(time(NULL));
	std::cout << "Starting test with " << MULT_CHANS << " channels and " << MULT_SIZE << " samples" << std::endl << std::endl;

	// circular buffer test
	CircularMultiBuffer b(MULT_CHANS, MULT_SIZE/2);
	
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
	CircularMultiWriter *writer = new CircularMultiWriter(&b, w, MULT_SIZE);
	Thread tWrite(writer);
	tWrite.startAndDetach();
	
	// creates a reader thread, and waits for execution to end
	CircularMultiReader *reader = new CircularMultiReader(&b, r, MULT_SIZE, MULT_SIZE/8);
	Thread tReader(reader);
	tReader.startAndJoin();

	// checks that the read data perfectly match the written ones
	std::cout << "Starting read..." << std::endl;
	bool succeed = true;
	for (int c=0; c<MULT_CHANS; c++)
	{
		for (int j=0; j<MULT_SIZE; j++) {
			if (w[c][j] != r[c][j])
			{
				succeed = false;
				std::cout << "x";
			} else {
				std::cout << ".";
			}
		}
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