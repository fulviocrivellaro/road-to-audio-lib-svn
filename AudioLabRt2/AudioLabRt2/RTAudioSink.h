#pragma once

#include "IAudioSink.h"
#include "RtAudio.h" // necessary for RtAudioStreamStatus

// RTAudio static callback declaration
int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

class RTAudioSink :
	public IAudioSink
{
public:
	RTAudioSink(RtAudio &rtAudio);
	RTAudioSink(RtAudio &rtAudio, IAudioSource &audioSource);
	~RTAudioSink(void);

	void setAudioSource(IAudioSource &audioSource);

	// stream commands
	bool open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize);
	bool close();
	bool start();
	bool stop();

private:
	//int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData);

	RtAudio &mRtAudio;
	IAudioSource *mAudioSource;

	double mSamplingFrequency;
};

