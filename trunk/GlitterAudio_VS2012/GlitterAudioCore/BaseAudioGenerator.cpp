#include "BaseAudioGenerator.h"

unsigned int BaseAudioGenerator::getChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	return this->BaseAudioSource::getChunk(buffer, channel, chunkSize);
}

void BaseAudioGenerator::consumeChunk(unsigned int channel, unsigned int chunkSize)
{
	this->BaseAudioSource::consumeChunk(channel, chunkSize);
}
