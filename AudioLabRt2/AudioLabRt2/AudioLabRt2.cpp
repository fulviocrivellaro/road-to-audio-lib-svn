#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "GlitterAudioDefines.h"
#include <iostream>
#include <cstdlib>
#include <math.h>

#include "GlitterAudio.h"
#include "IAudioSink.h"
#include "SinOscillator.h"
#include "SawOscillator.h"
#include "CircularBuffer.h"

#include "Thread.h"
#include "IRunnable.h"

int audioTest() {

	GlitterAudio* audio = new GlitterAudio();
	IAudioSink* sink = audio->getAudioSinkForDevice();

	int f = 440;
	int fs = 48000;
	int chunkSize = 256;

	bool ok = sink->open(*audio->listDevicesForDriver(AudioDriver::WIN_ASIO)[0], 2, (unsigned int)fs, chunkSize);

	if (ok)
	{
		sink->start();
	}
	IAudioSource* osc1 = new SinOscillator(f, (int)fs);
	IAudioSource* osc2 = new SawOscillator(f, (int)fs);
	sink->setAudioSource(*osc1, 0);
	sink->setAudioSource(*osc2, 1);
	
	char input;

	std::cout << "\nPlaying ... press <enter> to quit.\n\n\n";
	std::cin.get( input );

	sink->stop();
	sink->close();

	std::cout << "Delete OSC" << std::endl;
	delete osc1;
	delete osc2;
	delete sink;

	delete audio;

	return 0;
}

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
	- buffer il half the size of the samples to be written
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
int threadTest()
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

void main() {
	threadTest();

	char input;
	std::cout << "Press to exit...";
	std::cin.get(input);

	_CrtDumpMemoryLeaks();
}

