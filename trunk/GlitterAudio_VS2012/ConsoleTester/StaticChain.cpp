#include "StaticChain.h"
#include "AudioLink.h"
#include "IAudioGenerator.h"
#include "IAudioNode.h"

StaticChain::StaticChain(unsigned int chunkSize, IAudioGenerator* oscillator1, IAudioNode* noiseAdder, IAudioPlayer* player)
	: BaseAudioChain()
{
	mChunkSize = chunkSize;

	mOscillator1 = oscillator1;
	mNoiseAdder = noiseAdder;
	mPlayer = player;

	IAudioSink* sink1[] = {mNoiseAdder, (IAudioSink*)mPlayer};
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
	mOscillator1->createChunk(mChunkSize);

	// pass to player AND to noise generator
	mLinks[0]->moveData(mChunkSize);

	// add noise
	mNoiseAdder->processChunk(mChunkSize);

	// pass noisy channel to player
	mLinks[1]->moveData(mChunkSize);
}