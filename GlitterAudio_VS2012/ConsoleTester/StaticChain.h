#pragma once

#include "BaseAudioChain.h"

class IAudioSource;
class BaseAudioNode;

class StaticChain :
	public BaseAudioChain
{
public:
	StaticChain(unsigned int chunkSize, IAudioSource* oscillator1, BaseAudioNode* noiseAdder, IAudioPlayer* player);
	~StaticChain(void);

	void processChunk();

private:
	unsigned int mChunkSize;

	IAudioSource* mOscillator1;
	BaseAudioNode* mNoiseAdder;
	IAudioPlayer* mPlayer;
};

