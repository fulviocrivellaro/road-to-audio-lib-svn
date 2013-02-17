#include <stdlib.h>
#include <iostream>

#include "CircularMultiBuffer.h"
#include "Thread.h"
#include "IRunnable.h"

#include "IAudioSource.h"
#include "IAudioNode.h"
#include "IAudioSink.h"
#include "GlitterAudio.h"
#include "StaticChain.h"
#include "MonoSplitter.h"
#include "NoiseGenerator.h"

#include "SinOscillator.h"

// ================================= STAIC CHAIN TEST =====================================

#define CHUNK_SIZE 1024

class AudioSynch : public IRunnable
{
public:
	AudioSynch::AudioSynch(IAudioGenerator* generator, IAudioChain* chain) { mGenerator = generator; mChain = chain; mProceed = true; }
	void AudioSynch::stop() {
		mProceed = false;
	}
	void AudioSynch::run()
	{
		// prepare 8 chunks
		mChain->start();
		mGenerator->createChunk(6*CHUNK_SIZE);
		while (mProceed)
		{
			//mGenerator->createChunk(CHUNK_SIZE);
			mChain->processChunk();
		}
		std::cout<< "Synch stopped" << std::endl;
		mChain->stop();
	}
private:
	IAudioChain* mChain;
	IAudioGenerator* mGenerator;
	bool mProceed;
};

int staticChainAudioTest() {

	GlitterAudio* audio = new GlitterAudio();
	
	int f = 220;
	int fs = 48000;

	// nodes
	IAudioGenerator* osc1 = new SinOscillator(f, (int)fs);
	IAudioNode* splitter = new MonoSplitter();
	IAudioNode* noiseGenerator = new NoiseGenerator(0.001);
	IAudioPlayer* player = audio->getBufferedAudioPlayerForDevice();

	// chain
	StaticChain chain(1024, osc1, splitter, noiseGenerator, player);

	bool ok = player->open(*audio->listDevicesForDriver(AudioDriver::WIN_ASIO)[0], 2, (unsigned int)fs, CHUNK_SIZE);

	AudioSynch *synch = new AudioSynch(osc1, &chain);
	Thread t(synch, false);
	t.start();

	char input;

	std::cout << "\nPlaying ... press <enter> to quit.\n\n\n";
	std::cin.get( input );

	synch->stop();
	t.join();

	delete synch;

	std::cout << "Delete OSC" << std::endl;
	delete osc1;
	delete splitter;
	delete noiseGenerator;
	delete player;

	delete audio;

	return 0;
}

