#pragma once

#include <string>

class GUIReceiver
{
public:

	virtual ~GUIReceiver(void) {}

	// receive the panpot value
	virtual void onPitchShiftValueChanged(int value) = 0;
	virtual void onTimeStretchValueChanged(int value) = 0;

	// receive the buttons' callbacks
	virtual void onStartPressed() = 0;
	virtual void onPausePressed() = 0;
	virtual void onStopPressed() = 0;
	
	// receive the requested file
	virtual void onFileSelected(std::string fileName) = 0;

	// receive the progress bar
	virtual void onProgressValueChanged(int value) = 0;

};

