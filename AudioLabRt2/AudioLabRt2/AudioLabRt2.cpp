#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "GlitterAudioDefines.h"
//#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <math.h>

//#include "RtAudioHardwareFacade.h"
//#include "RTAudioSink.h"

#include "GlitterAudio.h"
#include "IAudioSink.h"
#include "SinOscillator.h"
#include "SawOscillator.h"

// direct calculation
const double pi = std::atan(1.0)*4;
const double f = 440.0;
const double fs = 48000.0;
unsigned int chunkSize = 256;
const double dphi = 2 * pi * f / fs;

double slopephi = dphi / 2;
double dslopephi = 1e-5;

// 2nd order oscillator
const double a = sin(0*dphi);
const double b = sin(1*dphi);
const double c = sin(2*dphi);
const double d = sin(3*dphi);
const double det = a*c - b*b;
const double c1 = (c*c - b*d) / det;
const double c2 = (a*d - b*c) / det;

/*
// Two-channel sawtooth wave generator.
int saw( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData )
{
	unsigned int i, j;
	double *buffer = (double *) outputBuffer;
	double *lastValues = (double *) userData;

	if ( status )
		std::cout << "Stream underflow detected!" << std::endl;

	// Write interleaved audio data.
	for ( i=0; i<nBufferFrames; i++ ) {
		for ( j=0; j<2; j++ ) {
			*buffer++ = lastValues[j];

			lastValues[j] += 0.005 * (j+1+(j*0.1));
			if ( lastValues[j] >= 1.0 ) lastValues[j] -= 2.0;
		}
	}

	return 0;
}

// Two-channel sin wave generator.
int sin_interleaved( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData)
{
	unsigned int i, j;
	double *buffer = (double *) outputBuffer;
	double *lastValues = (double *) userData;

	if ( status )
		std::cout << "Stream underflow detected!" << std::endl;

	// Write interleaved audio data.
	for ( i=0; i<nBufferFrames; i++ ) {
		for ( j=0; j<2; j++ ) {
			*buffer++ = std::sin(lastValues[j]);

			lastValues[j] += dphi;
			if (lastValues[j] >= 2*pi) {
				lastValues[j] -= 2 * pi;
			}
		}
	}

	return 0;
}

int sin_noninterleaved( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData)
{
	unsigned int i;
	double *buffer = (double *) outputBuffer;
	double *lastValues = (double *) userData;

	if ( status )
		std::cout << "Stream underflow detected!" << std::endl;

	// Write NON interleaved audio data.

	// L channel: calculation
	for (i=0; i<nBufferFrames; i++) {
		*buffer++ = std::sin(lastValues[0]);

		lastValues[0] += (slopephi += dslopephi);

		if (slopephi > 2*dphi || slopephi < .5*dphi) {
			dslopephi = -dslopephi;
		}

		if (lastValues[0] >= 2*pi) {
			lastValues[0] -= 2 * pi;
		}
	}

	// R channel: 2nd order oscillation
	for (i=0; i<nBufferFrames; i++) {
		double sample = c1*lastValues[1] + c2*lastValues[2];
		lastValues[1] = lastValues[2];
		lastValues[2] = sample;
		
		*buffer++ = sample;
	}


	return 0;
}

int sin_oscillator( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
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

int square( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData)
{
	int ret_val = sin_noninterleaved(outputBuffer, inputBuffer, nBufferFrames, streamTime, status, userData);

	double *buffer = (double *) outputBuffer;
	for (unsigned int i=0; i<2*nBufferFrames; i++) {
		*buffer++ = *buffer>0?1.0:-1.0;
	}

	return ret_val;
}

void playWithCallback(RtAudio* audio, IAudioSource* osc) {
	RtAudio::StreamParameters parameters;
	parameters.deviceId = 0;
	parameters.nChannels = 2;
	parameters.firstChannel = 0;
	double data[3] = {0, a, b};

	bool interleaved = false;

	try {

		//osc = new SinOscillator(f, (int)fs);

		if (interleaved) {
			audio->openStream(&parameters, NULL, RTAUDIO_FLOAT64, (unsigned int)fs, &chunkSize, &sin_interleaved, (void *)&data);
		} else {
			RtAudio::StreamOptions opts;
			opts.flags |= RTAUDIO_NONINTERLEAVED;
			audio->openStream(&parameters, NULL, RTAUDIO_FLOAT64, (unsigned int)fs, &chunkSize, &sin_oscillator, (void *)osc, &opts);
			//audio.openStream(&parameters, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, &sin_noninterleaved, (void *)&data, &opts);
		}
		std::cout << "Buffer size is: " << chunkSize << std::endl;
		std::cout << "Latency is: " << audio->getStreamLatency() << std::endl;
		audio->startStream();
	} catch (RtError& e) {
		e.printMessage();
		char input2;
		std::cout << "\nPress <enter> to quit.\n";
		std::cin.get( input2 );
		exit( 0 );
	}

	char input;
	std::cout << "\nPlaying ... press <enter> to quit.\n";
	std::cin.get( input );
}
*/

int main() {

	/*
	RtAudio* audio = new RtAudio();
	if (audio->getDeviceCount() < 1) {
		std::cout << "\nNo audio devices found!\n";
		exit(0);
	}

	// printAnalysis(dac);
	// ------------------------------------------------------------------------------
	// Determine the number of devices available
	int devices = audio->getDeviceCount();

	std::cout << "Found " << devices << " devices!" << std::endl << std::endl;

	// Scan through devices for various capabilities
	RtAudio::DeviceInfo info;
	for (int i=0; i<devices; i++) {

		try {
			info = audio->getDeviceInfo(i);
		} catch (RtError &error) {
			error.printMessage();
			break;
		}

		// Print, for example, the maximum number of output channels for each device
		std::cout << "DEVICE = " << i << std::endl;
		std::cout << "name: " << info.name << std::endl;
		std::cout << "- duplex channels: " << info.duplexChannels << std::endl;
		std::cout << "-  input channels: " << info.inputChannels << std::endl;
		std::cout << "- output channels: " << info.outputChannels << std::endl;
		std::cout << "-   default input: " << info.isDefaultInput << std::endl;
		std::cout << "-  default output: " << info.isDefaultOutput << std::endl;
		std::cout << "-  native formats: " << info.nativeFormats << std::endl;
		std::cout << "-          probed: " << info.probed << std::endl;
		//std::cout << "-    sample rates: " << info.sampleRates << std::endl;
		
		std::cout << std::endl;
	}

	std::cout << std::endl;
	// ------------------------------------------------------------------------------
	
	
	playWithCallback(audio, osc1);
	
	((SinOscillator*)osc1)->setFrequencyInHz(2*f);

	char input;
	std::cout << "\nPlaying ... press <enter> to quit.\n";
	std::cin.get( input );
	
	//playWithCallback(audio, osc2);

	try {
		// Stop the stream
		audio->stopStream();
	} catch (RtError& e) {
		e.printMessage();
	}

	if (audio->isStreamOpen()) {
		audio->closeStream();
	}

	delete audio;

	std::cout << std::endl << std::endl << "------------------------------------------" << std::endl;

	*/

	/*RtAudioHardwareFacade facade;

	std::vector<const AudioDevice* const> asioAudioDevices = facade.listDevicesForDriver(AudioDriver::WIN_ASIO);
	std::vector<const AudioDevice* const> dsAudioDevices = facade.listDevicesForDriver(AudioDriver::WIN_DIRECT_SOUND);
	std::cout << "Found for ASIO: " << asioAudioDevices.size() << std::endl;
	std::cout << "Found for DS  : " << dsAudioDevices.size() << std::endl;*/

	GlitterAudio* audio = new GlitterAudio();
	IAudioSink* sink = audio->getAudioSinkForDevice();


	//RtAudio ad2;
	//RTAudioSink sink(ad2, *osc1);
	IAudioSource* osc1 = new SinOscillator(f, (int)fs);
	IAudioSource* osc2 = new SawOscillator(f, (int)fs);
	sink->setAudioSource(*osc1, 0);
	sink->setAudioSource(*osc2, 1);
	
	char input;
	bool ok = sink->open(*audio->listDevicesForDriver(AudioDriver::WIN_ASIO)[0], 2, (unsigned int)fs, chunkSize);

	if (ok)
	{
		sink->start();

		std::cout << "\nPlaying ... press <enter> to quit.\n";
		std::cin.get( input );

		((SawOscillator*)osc2)->setFrequencyInHz(660);
	}

	std::cout << "\nPlaying ... press <enter> to quit.\n";
	std::cin.get( input );

	sink->stop();
	sink->close();

	std::cout << "Delete OSC" << std::endl;
	delete osc1;
	delete osc2;
	//delete sink;

	delete audio;

	_CrtDumpMemoryLeaks();

	return 0;

}
