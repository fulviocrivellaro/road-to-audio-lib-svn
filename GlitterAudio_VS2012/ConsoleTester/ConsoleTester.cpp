#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "GlitterAudioDefines.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include "GlitterAudio.h"
#include "IAudioPlayer.h"
#include "SinOscillator.h"
#include "SawOscillator.h"
#include "CircularBuffer.h"

#include "Thread.h"
#include "IRunnable.h"

#include "AudioBufferTest.h"
#include "StaticChainTest.h"


class Writer : public IRunnable
{
public:
	Writer::Writer(CircularBuffer *buffer, double* readFrom, int size) { mBuffer = buffer; mReadFrom = readFrom; mSize = size; }
	void Writer::run()
	{
		int ptr = 0;
		while (ptr < mSize)
		{
			int chunk = rand() % 200;
			if (ptr + chunk >= mSize)
			{
				chunk = mSize - ptr;
			}
			std::cout << "WR  > write " << chunk << " samples" << std::endl;
			mBuffer->bufferChunk(&mReadFrom, chunk);
			ptr += chunk;
			mReadFrom += chunk;
			std::chrono::milliseconds waitfor(rand() % 100);
			std::cout << "WR  > wait " << waitfor.count() << " ms" << std::endl;
			std::this_thread::sleep_for(waitfor);
		}
	}
private:
	CircularBuffer *mBuffer;
	double* mReadFrom;
	int mSize;
};

class Reader : public IRunnable
{
public:
	Reader::Reader(CircularBuffer *buffer, double* writeTo, int size, int chunkSize) { mBuffer = buffer; mWriteTo = writeTo; mSize = size; mChunk = chunkSize; }
	void Reader::run()
	{
		std::chrono::milliseconds waitfor(5000);
		std::cout << "WR  > wait 5 seconds to start..." << std::endl;
		std::this_thread::sleep_for(waitfor);
		int ptr = 0;
		while (ptr < mSize)
		{
			int chunk = mChunk;
			if (ptr + chunk >= mSize)
			{
				chunk = mSize - ptr;
			}
			std::cout << "RD <<< read " << chunk << " samples" << std::endl;
			mBuffer->fillChunk(&mWriteTo, chunk);
			ptr += chunk;
			mWriteTo += chunk;
		}
	}
private:
	int mChunk;
	CircularBuffer *mBuffer;
	double* mWriteTo;
	int mSize;
};

/********
	MONO buffer test:
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
int monoBufferTest()
{
	// circular buffer test
	int size = 512;
	CircularBuffer b(1, size/2);
	double* w = (double *)malloc(size*sizeof(double));
	double* r = (double *)malloc(size*sizeof(double));

	double* wp = w;
	double* rp = r;

	std::cout << "Starting generating samples..." << std::endl;
	for (int i=0; i<size; i++)
	{
		w[i] = rand() % 100;
	}

	Writer *writer = new Writer(&b, wp, size);
	Thread tWrite(writer);
	tWrite.startAndDetach();
	//b.bufferChunk(&wp, size);

	Reader *reader = new Reader(&b, rp, size, size/4);
	Thread tReader(reader);
	tReader.startAndJoin();

	std::cout << "Starting read..." << std::endl;
	//b.fillChunk(&rp, size);
	bool succeed = true;
	for (int i=0; i<size; i++)
	{
		if (w[i] != r[i])
		{
			succeed = false;
			std::cout << "x";
		} else {
			std::cout << ".";
		}
	}
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Buffer test: " << (succeed?"SUCCESS!!!":"Error...") << std::endl;
	std::cout << std::endl;
	free(w);
	free(r);

	return 0;

}

// ================================= MULTI-CHANNEL TEST =====================================

class CircularWriter : public IRunnable
{
public:
	CircularWriter::CircularWriter(CircularBuffer *buffer, double** readFrom, int size) { mBuffer = buffer; mReadFrom = readFrom; mSize = size; }
	void CircularWriter::run()
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
			double** samples = new double*[nChannels];
			for (unsigned int c=0; c<nChannels; c++)
			{
				samples[c] = &mReadFrom[c][ptr];
			}

			// actually buffers the samples
			mBuffer->bufferChunk(samples, chunk);
			delete[] samples;

			// updates current position tracker
			ptr += chunk;
			std::chrono::milliseconds waitfor(rand() % 100);
			std::cout << "WR  > wait " << waitfor.count() << " ms" << std::endl;
			std::this_thread::sleep_for(waitfor);
		}
	}
private:
	CircularBuffer *mBuffer;
	double** mReadFrom;
	int mSize;
};

class CircularReader : public IRunnable
{
public:
	CircularReader::CircularReader(CircularBuffer *buffer, double** writeTo, int size, int chunkSize) { mBuffer = buffer; mWriteTo = writeTo; mSize = size; mChunk = chunkSize; }
	void CircularReader::run()
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
			double** samples = new double*[nChannels];
			for (unsigned int c=0; c<nChannels; c++)
			{
				samples[c] = &mWriteTo[c][ptr];
			}
			
			// actually fill the local buffer, reading from the Circular
			mBuffer->fillChunk(samples, chunk);
			delete[] samples;

			// updates current position tracker
			ptr += chunk;
		}
	}
private:
	int mChunk;
	CircularBuffer *mBuffer;
	double** mWriteTo;
	int mSize;
};

#define SIZE 1024
#define CHANS 5

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
int multiBufferTest()
{
	srand(time(NULL));
	std::cout << "Starting test with " << CHANS << " channels and " << SIZE << " samples" << std::endl << std::endl;

	// circular buffer test
	CircularBuffer b(CHANS, SIZE/2);
	
	// write data and read data structures
	double **w = new double*[CHANS];
	double **r = new double*[CHANS];
	for (int c=0; c<CHANS; c++)
	{
		w[c] = new double[SIZE];
		r[c] = new double[SIZE];
	}

	// fills write data with random values
	std::cout << "Starting generating samples..." << std::endl;
	for (int i=0; i<CHANS; i++)
	{
		for (int j=0; j<SIZE; j++) {
			w[i][j] = rand() % 100;
		}
	}

	// creates a writer thread, which runs by its own
	CircularWriter *writer = new CircularWriter(&b, w, SIZE);
	Thread tWrite(writer);
	tWrite.startAndDetach();
	
	// creates a reader thread, and waits for execution to end
	CircularReader *reader = new CircularReader(&b, r, SIZE, SIZE/8);
	Thread tReader(reader);
	tReader.startAndJoin();

	// checks that the read data perfectly match the written ones
	std::cout << "Starting read..." << std::endl;
	bool succeed = true;
	for (int i=0; i<CHANS; i++)
	{
		for (int j=0; j<SIZE; j++) {
			if (w[i][j] != r[i][j])
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
	for (int c=0; c<CHANS; c++) {
		free(w[c]);
		free(r[c]);
	}
	free(w);
	free(r);

	return succeed?0:-1;
}

class Tester : public IRunnable
{
public:
	Tester::Tester(int n) {nn = n;}
	void run();
private:
	int nn;
};

void Tester::run()
{
	std::cout << "I am " << nn << "! - running on thread: " << std::this_thread::get_id() << std::endl;
}

void simpleThreadTest()
{
	std::cout << "I am main thread: " << std::this_thread::get_id() << std::endl << std::endl;

	IRunnable* runnable1 = new Tester(1);
	IRunnable* runnable2 = new Tester(2);
	
	// this runs on main thread
	runnable1->run();

	Thread t(runnable1, false);
	// this runs on Thread t
	t.startAndJoin();

	// this still works, and still on main thread
	runnable1->run();

	// re-use same runnable
	Thread t2(runnable1);
	// this runs on Thread t
	t2.startAndJoin();

	// runnable has been deleted: next statement would crash
	//runnable->run();

	// new runnable, different parameter
	Thread t3(runnable2);
	// this runs on Thread t
	t3.startAndJoin();

}

#define C 3
#define S 5
void dummyArray() {

	int a[C][S];

	for (int i=0; i<C; i++)
	{
		for (int j=0; j<S; j++)
		{
			int v = 10*(i+1) + (j+1);
			a[i][j] = v;
			//b[j][i] = v;
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	int chans = S;
	int samps = C;
	int **c;
	c = new int*[chans];
	for (int i=0; i<chans; i++)
	{
		c[i] = new int[samps];
	}

	for (int i=0; i<C; i++)
	{
		for (int j=0; j<S; j++)
		{
			int v = a[i][j];
			c[i][j] = v;
			std::cout << c[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	int *b = &a[0][0];
	for (int i=0; i<S*C; i++) {
		std::cout << *b++ << " - ";
	}
	std::cout << std::endl << std::endl;

	int *d = &c[0][0];
	for (int i=0; i<C*S; i++) {
		std::cout << *d++ << " - ";
	}
	std::cout << std::endl << std::endl;

}

//void AudioMultiBufferTest();

void main() {
	
	//multiBufferTest();
	//audioTest();
	//bufferedAudioTest();
	//AudioMultiBufferTest();
	//AudioBufferSimpleTest();

	//wavFileTest();

	staticChainAudioTest();

	char input;
	std::cout << "Press to exit...";
	std::cin.get(input);

	_CrtDumpMemoryLeaks();
}

