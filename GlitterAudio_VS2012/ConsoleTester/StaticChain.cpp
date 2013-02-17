#include "StaticChain.h"
#include "AudioLink.h"
#include "IAudioGenerator.h"
#include "IAudioNode.h"

StaticChain::StaticChain(unsigned int chunkSize, IAudioGenerator* oscillator, IAudioNode* splitter, IAudioNode* noiseGenerator, IAudioPlayer* player)
	: BaseAudioChain()
{
	mChunkSize = chunkSize;

	mOscillator = oscillator;
	mSplitter = splitter;
	mNoiseGenerator = noiseGenerator;
	mPlayer = player;

	link(mOscillator, 0, mSplitter, 0);
	link(mSplitter, 0, mNoiseGenerator, 0);
	link(mNoiseGenerator, 0, mPlayer, 1);
	link(mSplitter, 1, mPlayer, 0);
}


StaticChain::~StaticChain(void)
{
}

void StaticChain::processChunk()
{
	// generate sound
	mOscillator->createChunk(mChunkSize);

	// pass to splitter
	mLinks[0]->moveData(mChunkSize);

	// let splitter processes data
	mSplitter->processChunk(mChunkSize);

	// pass to noise generator
	mLinks[1]->moveData(mChunkSize);

	// add noise
	mNoiseGenerator->processChunk(mChunkSize);

	// pass to player
	mLinks[2]->moveData(mChunkSize);
	mLinks[3]->moveData(mChunkSize);
}