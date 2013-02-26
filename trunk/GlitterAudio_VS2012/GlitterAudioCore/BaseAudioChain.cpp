#include "BaseAudioChain.h"
#include "AudioLink.h"
#include "IAudioPlayer.h"

BaseAudioChain::BaseAudioChain(void)
{
	mAudioPlayer = NULL;
}

BaseAudioChain::~BaseAudioChain(void)
{
	mAudioPlayer = NULL;
	for (int i=0; i<mLinks.size(); i++)
	{
		delete mLinks[i];
	}
}

void BaseAudioChain::link(IAudioSource* source, unsigned int sourceChannel, IAudioSink* sink, unsigned int destChannel)
{
	mLinks.push_back(new AudioLink(source, sourceChannel, sink, destChannel));
}

void BaseAudioChain::link(IAudioSource* source, unsigned int sourceChannel, IAudioPlayer* player, unsigned int destChannel)
{
	mAudioPlayer = player;
	this->link(source, sourceChannel, (IAudioSink*)player, destChannel);
}

void BaseAudioChain::link(IAudioSource* source, unsigned int sourceChannel, IAudioSink* outputNodes[], unsigned int outputChannels[], unsigned int outputNodesCount)
{
	mLinks.push_back(new AudioLink(source, sourceChannel, outputNodes, outputChannels, outputNodesCount));
}

void BaseAudioChain::processChunks(unsigned int count)
{
	for (int i=0; i<count; i++)
	{
		processChunk();
	}
}

void BaseAudioChain::start()
{
	if (mAudioPlayer != NULL)
	{
		mAudioPlayer->start();
	}
}

void BaseAudioChain::stop()
{
	if (mAudioPlayer != NULL)
	{
		mAudioPlayer->stop();
	}
}