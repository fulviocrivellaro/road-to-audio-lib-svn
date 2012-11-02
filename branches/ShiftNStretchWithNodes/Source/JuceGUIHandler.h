#pragma once

#include "GUIHandler.h"
#include "MainGUI.h"

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

	// set the progress bar
	virtual void setProgress(int current, int duration);

	// register the knon audio formats
	void registerAudioFormats(std::set<std::string> formats);

private:
	MainGUI* gui;
	MainGUI* getGUI();
};