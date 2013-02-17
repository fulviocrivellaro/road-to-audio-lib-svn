#pragma once

#include "BaseAudioChain.h"

class IAudioGenerator;
class IAudioNode;

class StaticChain :
	public BaseAudioChain
{
public:
	StaticChain(unsigned int chunkSize, IAudioGenerator* oscillator, IAudioNode* splitter, IAudioNode* NoiseAdder, IAudioPlayer* player);
	~StaticChain(void);

	void processChunk();

private:
	unsigned int mChunkSize;

	IAudioGenerator* mOscillator;
	IAudioNode* mSplitter;
	IAudioNode* mNoiseAdder;
	IAudioPlayer* mPlayer;
};

