#pragma once

#include "GlitterAudioDefines.h"
#include "IAudioPlayer.h"
#include "RtAudio.h" // necessary for RtAudioStreamStatus
#include <vector>

class CircularMultiBuffer;

struct BufferedStreamData
{
	unsigned int    nChannels;
	IAudioSource*   sources[__GLITTERAUDIO__MAX__OUTPUT__CHANNELS__];
	CircularMultiBuffer* outputBuffer;
};

// RTAudio static callback declaration
int rtAudioBufferedCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

class RTAudioPlayer :
	public IAudioPlayer
{
public:
	RTAudioPlayer(RtAudio &rtAudio);
	~RTAudioPlayer(void);

	void takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize);

	void setAudioSource(IAudioSource &audioSource, unsigned int channelNumber);
	void triggerProcess();

	// stream commands
	bool open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize);
	bool close();
	bool start();
	bool stop();

private:
	void cleanBuffer();

	RtAudio &mRtAudio;
	BufferedStreamData mBufferedStreamData;

	//CircularBuffer *mOutputBuffer;
	unsigned int mChunkSize;
	double** mTmpBuffer;

	double mSamplingFrequency;
};

