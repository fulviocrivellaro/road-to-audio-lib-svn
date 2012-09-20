#include "PSTSEntryPoint.h"

PSTSEntryPoint::PSTSEntryPoint(GUIHandler *newGUIHandler)
	: guiHandler(newGUIHandler)
{
	init();
}


PSTSEntryPoint::~PSTSEntryPoint(void)
{
	audioFormatReaderSource->releaseResources();
	audioDeviceManager.closeAudioDevice();
	delete audioSourcePlayer;
	delete audioFormatReaderSource;
	delete audioFormatReader;
	//delete wavAudioFile;
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
}

void PSTSEntryPoint::prepareForFilename(std::string filename)
{
	int bufferSize = 2048;

	// initialize audio session
	WavAudioFormat wavAudioFormat;
	audioFormatReader = wavAudioFormat.createReaderFor(File((const char*) filename.c_str()).createInputStream(), false);
	audioFormatReaderSource = new CallbackAudioFormatReader(audioFormatReader, false, this);
	audioSourcePlayer = new AudioSourcePlayer();
	audioSourcePlayer->setSource(audioFormatReaderSource);

	int fs = audioFormatReader->sampleRate;
	duration = audioFormatReader->lengthInSamples / fs;
	previousPosition = 0;
	positionInSamples = 0;

	audioDeviceManager.getCurrentAudioDevice()->open(0, 3, fs, bufferSize);
	audioFormatReaderSource->prepareToPlay(bufferSize, 44100);
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
	guiHandler->doStop();
	guiHandler->setProgress(0, duration);
	audioDeviceManager.getCurrentAudioDevice()->stop();
	audioFormatReaderSource->setNextReadPosition(0);
	positionInSamples = 0;
	previousPosition = 0;
}

void PSTSEntryPoint::onFileSelected(std::string fileName)
{
	prepareForFilename(fileName);
}

// receive the progress bar
void PSTSEntryPoint::onProgressValueChanged(int value)
{
	positionInSamples = value * audioFormatReader->sampleRate;
	audioFormatReaderSource->setNextReadPosition(positionInSamples);
	
	guiHandler->setProgress(value, duration);
}

// listen to seek advance
void PSTSEntryPoint::onSeek(long sample)
{
	positionInSamples += sample;
	int currentPosition = positionInSamples / audioFormatReader->sampleRate;
	if (currentPosition != previousPosition)
	{
		previousPosition = currentPosition;
		guiHandler->setProgress(currentPosition, duration);
	}
}