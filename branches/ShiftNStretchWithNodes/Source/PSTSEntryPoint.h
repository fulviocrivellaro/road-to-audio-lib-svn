#pragma once

#include "GUIHandler.h"
#include "GUIReceiver.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "CallbackAudioFormatReader.h"
#include "IAudioReaderSeekListener.h"

#include <string>

class IAudioFacade;

class PSTSEntryPoint : public GUIReceiver, IAudioReaderSeekListener
{
public:
	PSTSEntryPoint(GUIHandler *newGUIHandler);
	~PSTSEntryPoint(void);
	void run(void);

	// receive the panpot value
	virtual void onPitchShiftValueChanged(int value);
	virtual void onTimeStretchValueChanged(int value);

	// receive the buttons' callbacks
	virtual void onStartPressed();
	virtual void onPausePressed();
	virtual void onStopPressed();
	
	// receive new filename
	virtual void onFileSelected(std::string fileName);

	// receive the progress bar
	virtual void onProgressValueChanged(int value);

	// listen to progress seek
	void onSeek(int samplesRead, long currentPosition);

private:
	// utils
	int duration;
	long positionInSamples, previousPosition;
	GUIHandler *guiHandler;
	IAudioFacade *mAudioFacade;

	void prepareForFilename(std::string filename);
	void resetGui();
};

