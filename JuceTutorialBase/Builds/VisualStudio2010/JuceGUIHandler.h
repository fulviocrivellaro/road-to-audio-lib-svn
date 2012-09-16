#pragma once

#include "guihandler.h"
#include "../../Source/MainGUI.h"

class JuceGUIHandler :
	public GUIHandler
{
public:
	JuceGUIHandler(MainGUI *newGui);
	virtual ~JuceGUIHandler(void);

	// set the panpot value
	virtual void setPitchShiftValue(int value);
	virtual void setTimeStretchValue(int value);

	// set the mode
	virtual void doStart();
	virtual void doPause();
	virtual void doStop();
	virtual void doRewind();

	// set the progress bar
	virtual void setProgress(int current, int duration);

private:
	MainGUI* gui;
	MainGUI* getGUI();
};