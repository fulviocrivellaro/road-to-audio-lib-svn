#include <stdlib.h>
#include <iostream>

#include "AudioMultiBuffer.h"
#include "Thread.h"
#include "IRunnable.h"

#include "IAudioSource.h"
#include "IAudioSink.h"
#include "GlitterAudio.h"
#include "StaticChain.h"
//#include "MonoSplitter.h"
#include "NoiseAdder.h"

#include "SinOscillator.h"

// ================================= STAIC CHAIN TEST =====================================

#define CHUNK_SIZE 1024

class AudioSynch : public IRunnable
{
public:
	AudioSynch::AudioSynch(IAudioSource* generator, IAudioChain* chain) { mGenerator = generator; mChain = chain; mProceed = true; }
	void AudioSynch::stop() {
		mProceed = false;
	}
	void AudioSynch::run()
	{
		// prepare 8 chunks
		//((BaseAudioSource*)mGenerator)->processChunk(8*CHUNK_SIZE);
		mChain->start();
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
	IAudioSource* mGenerator;
	bool mProceed;
};

int staticChainAudioTest() {

	GlitterAudio* audio = new GlitterAudio();
	
	int f = 220;
	int fs = 48000;

	// nodes
	IAudioSource* osc1 = new SinOscillator(f, (int)fs);
	BaseAudioNode* noiseAdder = new NoiseAdder(0.00001);
	IAudioPlayer* player = audio->getAudioPlayerForDevice();

	// chain
	StaticChain chain(1024, osc1, noiseAdder, player);

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
	delete noiseAdder;
	delete player;

	delete audio;

	return 0;
}

