#include "StaticChain.h"
#include "AudioLink.h"
#include "IAudioGenerator.h"
#include "IAudioNode.h"

StaticChain::StaticChain(unsigned int chunkSize, IAudioGenerator* oscillator1, IAudioGenerator* oscillator2, IAudioNode* noiseAdder, IAudioPlayer* player)
	: BaseAudioChain()
{
	mChunkSize = chunkSize;

	mOscillator2 = oscillator1;
	mOscillator1 = oscillator2;
	mNoiseAdder = noiseAdder;
	mPlayer = player;

	link(mOscillator1, 0, mNoiseAdder, 0);
	link(mNoiseAdder, 0, mPlayer, 0);
	link(mOscillator2, 0, mPlayer, 1);
}


StaticChain::~StaticChain(void)
{
}

void StaticChain::processChunk()
{
	// generate sound
	mOscillator1->createChunk(mChunkSize);
	mOscillator2->createChunk(mChunkSize);

	// pass to splitter
	mLinks[0]->moveData(mChunkSize);

	// add noise
	mNoiseAdder->processChunk(mChunkSize);

	// pass to noise generator
	mLinks[1]->moveData(mChunkSize);
	mLinks[2]->moveData(mChunkSize);
}