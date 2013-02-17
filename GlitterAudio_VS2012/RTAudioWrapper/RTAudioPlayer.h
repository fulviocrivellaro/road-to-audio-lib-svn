#pragma once

#include "GlitterAudioDefines.h"
#include "IAudioPlayer.h"
#include "RtAudio.h" // necessary for RtAudioStreamStatus
#include <vector>

struct StreamData
{
	unsigned int   nChannels;
	IAudioSource*  sources[__GLITTERAUDIO__MAX__OUTPUT__CHANNELS__];
};

// RTAudio static callback declaration
int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

class RTAudioPlayer :
	public IAudioPlayer
{
public:
	RTAudioPlayer(RtAudio &rtAudio);
	~RTAudioPlayer(void);

	void setAudioSource(IAudioSource &audioSource, unsigned int channelNumber);
	void triggerProcess();

	// stream commands
	bool open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize);
	bool close();
	bool start();
	bool stop();

private:

	RtAudio &mRtAudio;
	StreamData mStreamData;

	double mSamplingFrequency;
};

