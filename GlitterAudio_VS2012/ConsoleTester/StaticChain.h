#pragma once

#include "BaseAudioChain.h"

class IAudioGenerator;
class IAudioNode;

class StaticChain :
	public BaseAudioChain
{
public:
	StaticChain(unsigned int chunkSize, IAudioGenerator* oscillator1, IAudioGenerator* oscillator2, IAudioNode* noiseAdder, IAudioPlayer* player);
	~StaticChain(void);

	void processChunk();

private:
	unsigned int mChunkSize;

	IAudioGenerator* mOscillator1;
	IAudioGenerator* mOscillator2;
	IAudioNode* mNoiseAdder;
	IAudioPlayer* mPlayer;
};

