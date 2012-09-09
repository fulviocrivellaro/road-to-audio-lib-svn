#include "PSTSEntryPoint.h"

PSTSEntryPoint::PSTSEntryPoint(GUIHandler *newGUIHandler)
{
	guiHandler = newGUIHandler;
	duration = 92;
}


PSTSEntryPoint::~PSTSEntryPoint(void)
{
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
}

void PSTSEntryPoint::onPausePressed()
{
	guiHandler->doPause();
}

void PSTSEntryPoint::onStopPressed()
{
	guiHandler->doStop();
}

void PSTSEntryPoint::onRewindPressed()
{
	guiHandler->doRewind();
	guiHandler->setProgress(0, duration);
}

// receive the progress bar
void PSTSEntryPoint::onProgressValueChanged(int value)
{
	guiHandler->setProgress(value, duration);
}
