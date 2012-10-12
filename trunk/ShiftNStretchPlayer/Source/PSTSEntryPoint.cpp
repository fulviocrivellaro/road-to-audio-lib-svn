#include "PSTSEntryPoint.h"
#include "JuceAudioFacade.h"
#include "AudioDevice.h"
#include <vector>
#include <string>

PSTSEntryPoint::PSTSEntryPoint(GUIHandler *newGUIHandler)
	: guiHandler(newGUIHandler)
{
}


PSTSEntryPoint::~PSTSEntryPoint(void)
{
	delete mAudioFacade;
}

void PSTSEntryPoint::prepareForFilename(std::string filename)
{
	mAudioFacade->setFileSource(filename);
	duration = mAudioFacade->getSourceLength() / mAudioFacade->getSamplingFrequency();
	resetGui();
}

void PSTSEntryPoint::run()
{
	guiHandler->setTimeStretchValue(100);
	duration = 0;
	resetGui();

	// initialize Juce Facade
	mAudioFacade = new JuceAudioFacade();
	mAudioFacade->setAudioSeekListener(this);

	guiHandler->registerAudioFormats(mAudioFacade->getSupportedAudioFormats());
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
	if (mAudioFacade->play())
	{
		guiHandler->doStart();
	}
}

void PSTSEntryPoint::onPausePressed()
{
	if (mAudioFacade->pause())
	{
		guiHandler->doPause();
	}
}

void PSTSEntryPoint::onStopPressed()
{
	if (mAudioFacade->stop())
	{
		resetGui();
	}
}

void PSTSEntryPoint::resetGui()
{
	guiHandler->doStop();
	guiHandler->setProgress(0, duration);
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
	positionInSamples = value * mAudioFacade->getSamplingFrequency();
	mAudioFacade->seek(positionInSamples);
	
	guiHandler->setProgress(value, duration);
}

// listen to seek advance
void PSTSEntryPoint::onSeek(int samplesRead, long currentPosition)
{
	int fs = mAudioFacade->getSamplingFrequency();
	int currentPositionInSeconds = currentPosition / fs;
	if (currentPositionInSeconds != previousPosition)
	{
		previousPosition = currentPositionInSeconds;
		duration = mAudioFacade->getSourceLength() / fs;
		guiHandler->setProgress(currentPositionInSeconds, duration);
	}
}