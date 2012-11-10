#pragma once

class IAudioSource;
class AudioDevice;

class IAudioSink
{
public:
	//virtual double* getNextChunk(unsigned int &chunkSize) = 0;
	virtual void setAudioSource(IAudioSource &audioSource) = 0;

	// stream commands
	virtual bool open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize) = 0;
	virtual bool close() = 0;
	virtual bool start() = 0;
	virtual bool stop() = 0;

};