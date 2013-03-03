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

	link(mOscillator1, 0, mPlayer, 0);
	link(mOscillator1, 1, mPlayer, 1);

	//IAudioSink* sink1[] = {mPlayer, mPlayer};
	//IAudioSink* sink1[] = {mNoiseAdder, mPlayer};
	//unsigned int channels[] = {0, 1};
	//link(mOscillator1, 0, sink1, channels, 2);
	//link(mNoiseAdder, 0, mPlayer, 0);
}


StaticChain::~StaticChain(void)
{
}

void StaticChain::processChunk()
{
	for (unsigned int i=0; i<mLinks.size(); i++)
	{
		mLinks[i]->moveData(mChunkSize);
	}
}