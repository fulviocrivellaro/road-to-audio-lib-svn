#include "RTAudioSink.h"
#include "AudioDevice.h"
#include "IAudioSource.h"

RTAudioSink::RTAudioSink(RtAudio &rtAudio) :
	mRtAudio(rtAudio)
{
	for (unsigned int i=0; i<__GLITTERAUDIO__MAX__OUTPUT__CHANNELS__; i++)
	{
		mStreamData.sources[i] = 0;
	}
}

RTAudioSink::~RTAudioSink(void)
{
}

void RTAudioSink::setAudioSource(IAudioSource &audioSource, unsigned int channelNumber)
{
	mStreamData.sources[channelNumber] = &audioSource;
}

// stream commands

bool RTAudioSink::open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize)
{
	try
	{
		RtAudio::StreamParameters parameters;
		parameters.deviceId = device.getIndex();
		parameters.nChannels = nChannels;
		parameters.firstChannel = 0;
		RtAudio::StreamOptions opts;
		opts.flags |= RTAUDIO_NONINTERLEAVED;
		//StreamData* streamData = new StreamData();
		mStreamData.nChannels = nChannels;
		mRtAudio.openStream(&parameters, NULL, RTAUDIO_FLOAT64, (int)fs, &chunkSize, &rtAudioCallback, (void *)&mStreamData, &opts);
		std::cout << "Returned buffer size is: " << chunkSize << std::endl;
		return true;
	} catch (RtError& e) {
		e.printMessage();
		return false;
	}
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
	StreamData* streamData = (StreamData*)userData;
	
	for (unsigned int i=0; i<streamData->nChannels; i++)
	{
		// call the source only if meaningful
		if (streamData->sources[i] != 0)
		{
			streamData->sources[i]->fillChunk(&buffer[i*nBufferFrames], nBufferFrames);
		}
	}
	return 0;
}