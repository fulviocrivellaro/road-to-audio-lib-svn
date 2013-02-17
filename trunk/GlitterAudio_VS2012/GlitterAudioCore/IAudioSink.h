#pragma once

class IAudioSource;
class AudioDevice;

class IAudioSink
{
public:
	virtual void takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize) = 0;
	
	// TODO: remove
	//virtual void setAudioSource(IAudioSource &audioSource, unsigned int channelNumber) = 0;
	//virtual void triggerProcess() = 0;

};