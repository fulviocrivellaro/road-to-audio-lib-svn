#pragma once

#include "guihandler.h"
#include "GUIReceiver.h"
#include "JuceHeader.h"
#include "CallbackAudioFormatReader.h"
#include <string>

class PSTSEntryPoint : public GUIReceiver
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
	void onSeek(long sample);

private:
	// utils
	int duration;
	long positionInSamples, previousPosition;
	GUIHandler *guiHandler;

	// Juce Audio Objects
	AudioDeviceManager audioDeviceManager;
	AudioIODevice *audioDevice;
    //File *wavAudioFile;
	//FileInputStream *wavInputStream;
	//WavAudioFormat *wavAudioFormat;
	AudioFormatReader *audioFormatReader;
	AudioFormatReaderSource *audioFormatReaderSource;
	AudioSourcePlayer *audioSourcePlayer;
	
	void init();
	void prepareForFilename(std::string filename);
	
};

