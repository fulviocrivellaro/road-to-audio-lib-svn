#include "RTAudioPlayer.h"
#include "AudioDevice.h"
#include "IAudioSource.h"
#include "CircularMultiBuffer.h"

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

void RTAudioPlayer::takeChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	if (mBufferedStreamData.outputBuffer != 0)
	{
		mBufferedStreamData.outputBuffer->bufferChunk(buffer, channel, chunkSize);
		//for (unsigned int i=0; i<mBufferedStreamData.nChannels; i++)
		//{
		//	// call the source only if meaningful
		//	if (mBufferedStreamData.sources[i] != 0)
		//	{
		//		mBufferedStreamData.sources[i]->fillChunk(mTmpBuffer[i], mChunkSize);
		//	}
		//}
		//mBufferedStreamData.outputBuffer->bufferChunk(mTmpBuffer, mChunkSize);
	}
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
	mBufferedStreamData.outputBuffer = new CircularMultiBuffer(nChannels, 8*chunkSize);
	try
	{
		RtAudio::StreamParameters parameters;
		parameters.deviceId = device.getIndex();
		parameters.nChannels = nChannels;
		parameters.firstChannel = 0;
		RtAudio::StreamOptions opts;
		opts.flags |= RTAUDIO_NONINTERLEAVED;
		//StreamData* streamData = new StreamData();
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

	double** internalBuffer = new double*[nBufferFrames];
	for (unsigned int c=0; c<bufferedStreamData->nChannels; c++)
	{
		internalBuffer[c] = new double[nBufferFrames];
		bufferedStreamData->outputBuffer->fillChunk(internalBuffer[c], c, nBufferFrames);
	}
	
	for (unsigned int c=0; c<bufferedStreamData->nChannels; c++)
	{
		for (unsigned int i=0; i<nBufferFrames; i++)
		{
			*buffer++ = internalBuffer[c][i];
		}
	}

	for (unsigned int i=0; i<bufferedStreamData->nChannels; i++)
	{
		delete[] internalBuffer[i];
	}
	delete[] internalBuffer;

	return 0;
}