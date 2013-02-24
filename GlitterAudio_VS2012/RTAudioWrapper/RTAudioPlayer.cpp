#include "RTAudioPlayer.h"
#include "AudioDevice.h"
#include "IAudioSource.h"
#include "AudioMultiBuffer.h"

RTAudioPlayer::RTAudioPlayer(RtAudio &rtAudio) :
	mRtAudio(rtAudio)
{
	for (unsigned int i=0; i<__GLITTERAUDIO__MAX__OUTPUT__CHANNELS__; i++)
	{
		mBufferedStreamData.sources[i] = 0;
	}
	mBufferedStreamData.outputBuffer = 0;
	mTmpBuffer = 0;
}

RTAudioPlayer::~RTAudioPlayer(void)
{
}

void RTAudioPlayer::setAudioSource(IAudioSource &audioSource, unsigned int channelNumber)
{
	mBufferedStreamData.sources[channelNumber] = &audioSource;
}

unsigned int RTAudioPlayer::takeChunk(double** buffer, unsigned int channel, unsigned int chunkSize)
{
	if (mBufferedStreamData.outputBuffer != 0)
	{
		return mBufferedStreamData.outputBuffer->takeChunk(buffer, channel, chunkSize);
	} else {
		return 0;
	}
}

void RTAudioPlayer::convalidateChunk(unsigned int channel, unsigned int chunkSize)
{
	mBufferedStreamData.outputBuffer->convalidateChunk(channel, chunkSize);
}

// stream commands

bool RTAudioPlayer::open(const AudioDevice &device, unsigned int nChannels, unsigned int fs, unsigned int chunkSize)
{
	cleanBuffer();
	mTmpBuffer = new double*[nChannels];
	for (unsigned int c=0; c<nChannels; c++)
	{
		mTmpBuffer[c] = new double[chunkSize];
	}
	mBufferedStreamData.outputBuffer = new AudioMultiBuffer(nChannels, 8*chunkSize);
	try
	{
		RtAudio::StreamParameters parameters;
		parameters.deviceId = device.getIndex();
		parameters.nChannels = nChannels;
		parameters.firstChannel = 0;
		RtAudio::StreamOptions opts;
		opts.flags |= RTAUDIO_NONINTERLEAVED;
		mBufferedStreamData.nChannels = nChannels;
		mRtAudio.openStream(&parameters, NULL, RTAUDIO_FLOAT64, (int)fs, &chunkSize, &rtAudioBufferedCallback, (void *)&mBufferedStreamData, &opts);
		std::cout << "Returned buffer size is: " << chunkSize << std::endl;
		mChunkSize = chunkSize;
		return true;
	} catch (RtError& e) {
		e.printMessage();
		return false;
	}
}

bool RTAudioPlayer::close()
{
	if (mBufferedStreamData.outputBuffer)
	{
		delete mBufferedStreamData.outputBuffer;
	}
	mRtAudio.closeStream();
	return true;
}

bool RTAudioPlayer::start()
{
	mRtAudio.startStream();
	return true;
}

bool RTAudioPlayer::stop()
{
	mRtAudio.stopStream();
	return true;
}

void RTAudioPlayer::cleanBuffer()
{
	if (mTmpBuffer != 0)
	{
		for (unsigned int c=0; c<mBufferedStreamData.nChannels; c++)
		{
			delete[] mTmpBuffer[c];
		}
		delete[] mTmpBuffer;
	}
}

// RTAudio static callback implementation
int rtAudioBufferedCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData)
{
	double *buffer = (double *) outputBuffer;
	BufferedStreamData* bufferedStreamData = (BufferedStreamData*)userData;
	
	for (unsigned int c=0; c<bufferedStreamData->nChannels; c++)
	{
		double* samplePointer;

		// wait for enough samples (TODO: switch to synchronous method)
		while (bufferedStreamData->outputBuffer->getChunk(&samplePointer, c, nBufferFrames) < nBufferFrames);
		
		for (unsigned int i=0; i<nBufferFrames; i++)
		{
			*buffer++ = samplePointer[i];
		}
		// TODO: create synchronous buffer call
		bufferedStreamData->outputBuffer->consumeChunk(c, nBufferFrames);
	}

	return 0;
}