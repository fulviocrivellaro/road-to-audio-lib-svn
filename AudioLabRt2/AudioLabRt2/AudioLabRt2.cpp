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

void reader()
{

}


int threadTest()
{
	// circular buffer test
	CircularBuffer b(1, 1024);
	int size = 1024;
	double* w = (double *)malloc(size*sizeof(double));
	double* r = (double *)malloc(size*sizeof(double));

	double* wp = w;
	double* rp = r;

	std::cout << "Starting write..." << std::endl;
	for (int i=0; i<size; i++)
	{
		w[i] = rand() % 100;
	}
	b.bufferChunk(&w, size);
	
	std::cout << "Starting read..." << std::endl;
	b.fillChunk(&rp, size/2);
	rp += (size/2);
	b.fillChunk(&rp, size/2);
	for (int i=0; i<size; i++)
	{
		if (w[i] != r[i])
		{
			std::cout << "x";
		} else {
			std::cout << ".";
		}
	}
	std::cout << std::endl;

	free(w);
	free(r);

	char input;
	std::cout << "Press enter to exit...";
	std::cin.get(input);

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
	simpleThreadTest();

	char input;
	std::cout << "Press to exit...";
	std::cin.get(input);

	_CrtDumpMemoryLeaks();
}

