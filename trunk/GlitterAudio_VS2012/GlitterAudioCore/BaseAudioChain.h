#pragma once

#include <vector>
#include "IAudioChain.h"

class AudioLink;
class IAudioPlayer;

class BaseAudioChain :
	public IAudioChain
{
public:
	BaseAudioChain();
	virtual ~BaseAudioChain(void);

	void link(IAudioSource* source, unsigned int sourceChannel, IAudioSink* sink, unsigned int destChannel);
	void link(IAudioSource* source, unsigned int sourceChannel, IAudioPlayer* sink, unsigned int destChannel);
	virtual void processChunk() = 0;
	void processChunks(unsigned int count);

	// simple transport methods
	void start();
	void stop();

protected:
	std::vector<AudioLink*> mLinks;
	IAudioPlayer* mAudioPlayer;
};

