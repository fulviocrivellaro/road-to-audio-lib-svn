#include "BaseAudioPlayer.h"

BaseAudioPlayer::~BaseAudioPlayer(void)
{
}

unsigned int BaseAudioPlayer::takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return this->BaseAudioSink::takeChunk(buffer, channel, chunkSize);
}

void BaseAudioPlayer::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	this->BaseAudioSink::convalidateChunk(channel, chunkSize);
}
