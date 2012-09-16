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
	delete wavAudioFile;
}

void PSTSEntryPoint::init()
{
	DBG("Initializing");
	String outcome = audioDeviceManager.initialise(0, 3, nullptr, true, "DirectSound");
	if (outcome.isEmpty())
	{
		
		DBG("OK - play");
		DBG(audioDeviceManager.getCurrentAudioDeviceType());

		int bufferSize = 2048;

		// initialize audio session
		wavAudioFile = new File("C:\\2012_cisternino\\Nutshell-Buccia.wav");
		WavAudioFormat wavAudioFormat;
		audioFormatReader = wavAudioFormat.createReaderFor(wavAudioFile->createInputStream(), false);
		audioFormatReaderSource = new CallbackAudioFormatReader(audioFormatReader, false, this);
		audioSourcePlayer = new AudioSourcePlayer();
		audioSourcePlayer->setSource(audioFormatReaderSource);

		//DBG("Gain is: " + String(audioSourcePlayer->getGain()));
		//DBG("Audio is: " + String(audioDevice->isOpen()?String("Open"):String("Closed")));

		int fs = audioFormatReader->sampleRate;
		duration = audioFormatReader->lengthInSamples / fs;
		previousPosition = 0;
		positionInSamples = 0;

		audioDevice = audioDeviceManager.getCurrentAudioDevice();
		audioDevice->open(0, 3, fs, bufferSize);

		audioFormatReaderSource->prepareToPlay(bufferSize, 44100);
		
	} else {
		DBG(outcome);
	}
	
}

void PSTSEntryPoint::run()
{
	guiHandler->setTimeStretchValue(100);
	guiHandler->setProgress(0, duration);
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
	audioDevice->start(audioSourcePlayer);
}

void PSTSEntryPoint::onPausePressed()
{
	guiHandler->doPause();
	audioDevice->stop();
}

void PSTSEntryPoint::onStopPressed()
{
	guiHandler->doStop();
	guiHandler->setProgress(0, duration);
	audioDevice->stop();
	audioFormatReaderSource->setNextReadPosition(0);
	positionInSamples = 0;
	previousPosition = 0;
}

void PSTSEntryPoint::onRewindPressed()
{
	guiHandler->doRewind();
	guiHandler->setProgress(0, duration);
	audioDeviceManager.playTestSound();
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