#include "BaseAudioNode.h"

unsigned int BaseAudioNode::getChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return this->BaseAudioSource::getChunk(buffer, channel, chunkSize);
}

void BaseAudioNode::consumeChunk(unsigned int channel, unsigned int chunkSize)
{
	this->BaseAudioSource::consumeChunk(channel, chunkSize);
}

unsigned int BaseAudioNode::takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return this->BaseAudioSink::takeChunk(buffer, channel, chunkSize);
}

void BaseAudioNode::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	return this->BaseAudioSink::convalidateChunk(channel, chunkSize);
}