#include "RTAudioSink.h"
#include "AudioDevice.h"
#include "IAudioSource.h"

RTAudioSink::RTAudioSink(RtAudio &rtAudio) :
	mRtAudio(rtAudio)
{
	mAudioSource = 0;
}

RTAudioSink::RTAudioSink(RtAudio &rtAudio, IAudioSource &audioSource) :
	mRtAudio(rtAudio)
{
	setAudioSource(audioSource);
}

RTAudioSink::~RTAudioSink(void)
{
}

void RTAudioSink::setAudioSource(IAudioSource &audioSource)
{
	mAudioSource = &audioSource;
}

// stream commands

void test() {
	void* ptr = (void *)&rtAudioCallback;
}

bool RTAudioSink::open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize)
{
	if (mAudioSource != 0)
	{
		RtAudio::StreamParameters parameters;
		parameters.deviceId = device.getIndex();
		parameters.nChannels = nChannels;
		parameters.firstChannel = 0;
		RtAudio::StreamOptions opts;
		opts.flags |= RTAUDIO_NONINTERLEAVED;
		mRtAudio.openStream(&parameters, NULL, RTAUDIO_FLOAT64, (int)fs, &chunkSize, &rtAudioCallback, (void *)mAudioSource, &opts);
		return true;
	}
	return false;
}

bool RTAudioSink::close()
{
	mRtAudio.closeStream();
	return true;
}

bool RTAudioSink::start()
{
	mRtAudio.startStream();
	return true;
}

bool RTAudioSink::stop()
{
	mRtAudio.stopStream();
	return true;
}

// RTAudio static callback implementation
int rtAudioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData)
{
	double *buffer = (double *) outputBuffer;
	IAudioSource *osc = (IAudioSource*)userData;

	osc->fillChunk(buffer, nBufferFrames);
	//buffer += nBufferFrames;
	for (unsigned int i=0; i<nBufferFrames; i++)
	{
		buffer[i+nBufferFrames] = buffer[i];
	}

	return 0;
}