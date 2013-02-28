#include "StaticChain.h"
#include "AudioLink.h"
#include "BaseAudioNode.h"
#include "IAudioPlayer.h"

StaticChain::StaticChain(unsigned int chunkSize, IAudioSource* oscillator1, BaseAudioNode* noiseAdder, IAudioPlayer* player)
	: BaseAudioChain()
{
	mChunkSize = chunkSize;

	mOscillator1 = oscillator1;
	mNoiseAdder = noiseAdder;
	mPlayer = player;

	//IAudioSink* sink1[] = {mPlayer, mPlayer};
	IAudioSink* sink1[] = {mNoiseAdder, mPlayer};
	unsigned int channels[] = {0, 1};
	link(mOscillator1, 0, sink1, channels, 2);
	link(mNoiseAdder, 0, mPlayer, 0);
}


StaticChain::~StaticChain(void)
{
}

void StaticChain::processChunk()
{
	// generate sound
	//mOscillator1->createChunk(mChunkSize);

	// pass to player AND to noise generator
	mLinks[0]->moveData(mChunkSize);

	// add noise
	//mNoiseAdder->processChunk(mChunkSize);

	// pass noisy channel to player
	mLinks[1]->moveData(mChunkSize);
}