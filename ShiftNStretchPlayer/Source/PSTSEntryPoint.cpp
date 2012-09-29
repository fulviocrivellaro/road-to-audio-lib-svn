#include "PSTSEntryPoint.h"
#include "JuceAudioFacade.h"
#include "AudioDevice.h"
#include <vector>
#include <string>

PSTSEntryPoint::PSTSEntryPoint(GUIHandler *newGUIHandler)
	: guiHandler(newGUIHandler)
{
	init();
}


PSTSEntryPoint::~PSTSEntryPoint(void)
{
	if (audioSourcePlayer != nullptr)
	{
		audioFormatReaderSource->releaseResources();
		audioDeviceManager.closeAudioDevice();
		delete audioSourcePlayer;
		delete audioFormatReaderSource;
	}
}

void PSTSEntryPoint::init()
{
	DBG("Initializing");
	String outcome = audioDeviceManager.initialise(0, 3, nullptr, false);
	if (outcome.isEmpty())
	{
		DBG("OK - playing on " + audioDeviceManager.getCurrentAudioDeviceType());
	} else {
		DBG("Initialization error: " + outcome);
	}
	// sets the player to null
	audioSourcePlayer = nullptr;

	// dumps info about current output hardware available
	JuceAudioFacade facade;
	vector<AudioDevice> devices = facade.listAllDevices();
	for (int i=0; i<devices.size(); i++)
	{
		AudioDevice dev = devices[i];
		DBG("DRV (" + String(dev.getDriverIndex()) + "): " + dev.getDriver().c_str() + " - NAME (" + String(dev.getDeviceIndex()) + "): " + dev.getName().c_str());
	}

}

void PSTSEntryPoint::prepareForFilename(std::string filename)
{
	int bufferSize = audioDeviceManager.getCurrentAudioDevice()->getDefaultBufferSize();

	bool initialized = (audioSourcePlayer != nullptr);
	if (!initialized)
	{
		audioSourcePlayer = new AudioSourcePlayer();
	}

	WavAudioFormat wavAudioFormat;
	
	// need to create a new, temporary AudioFormatReaderSource, for the player
	AudioFormatReaderSource* newAudioFormatReaderSource = new CallbackAudioFormatReader(wavAudioFormat.createReaderFor(File((const char*) filename.c_str()).createInputStream(), false), true, this);
	// AFTER setting the new AudioFormatReaderSource, the releaseResources() method is called on the source instance
	audioSourcePlayer->setSource(newAudioFormatReaderSource);

	// check if this is not the first run
	if (initialized)
	{
		// now the old AudioFormatReaderSource is no longer needed - can delete it (AudioSourcePlayer will NOT do it)
		delete audioFormatReaderSource;
	}
	// we can update our pointer to the current AudioFormatReaderSource at last
	audioFormatReaderSource = newAudioFormatReaderSource;
	
	int fs = audioFormatReaderSource->getAudioFormatReader()->sampleRate;
	duration = audioFormatReaderSource->getAudioFormatReader()->lengthInSamples / fs;
	previousPosition = 0;
	positionInSamples = 0;

	audioDeviceManager.getCurrentAudioDevice()->open(0, 3, fs, bufferSize);
	audioFormatReaderSource->prepareToPlay(bufferSize, 44100);

	initialized = true;
}

void PSTSEntryPoint::run()
{
	guiHandler->setTimeStretchValue(100);
	guiHandler->setProgress(0, 0);
}

// receive the panpot value
void PSTSEntryPoint::onPitchShiftValueChanged(int value)
{
	
}

void PSTSEntryPoint::onTimeStretchValueChanged(int value)
{

}

// receive the buttons' callbacks
void PSTSEntryPoint::onStartPressed(void)
{
	guiHandler->doStart();
	audioDeviceManager.getCurrentAudioDevice()->start(audioSourcePlayer);
}

void PSTSEntryPoint::onPausePressed()
{
	guiHandler->doPause();
	audioDeviceManager.getCurrentAudioDevice()->stop();
}

void PSTSEntryPoint::onStopPressed()
{
	if (audioSourcePlayer != nullptr)
	{
		guiHandler->doStop();
		guiHandler->setProgress(0, duration);
		audioDeviceManager.getCurrentAudioDevice()->stop();
		audioFormatReaderSource->setNextReadPosition(0);
		positionInSamples = 0;
		previousPosition = 0;
	}
}

void PSTSEntryPoint::onFileSelected(std::string fileName)
{
	prepareForFilename(fileName);
}

// receive the progress bar
void PSTSEntryPoint::onProgressValueChanged(int value)
{
	positionInSamples = value * audioFormatReaderSource->getAudioFormatReader()->sampleRate;
	audioFormatReaderSource->setNextReadPosition(positionInSamples);
	
	guiHandler->setProgress(value, duration);
}

// listen to seek advance
void PSTSEntryPoint::onSeek(long sample)
{
	positionInSamples += sample;
	int currentPosition = positionInSamples / audioFormatReaderSource->getAudioFormatReader()->sampleRate;
	if (currentPosition != previousPosition)
	{
		previousPosition = currentPosition;
		guiHandler->setProgress(currentPosition, duration);
	}
}