#pragma once

#include "IAudioFacade.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <vector>
#include <string>

using namespace std;

class JuceAudioFacade :
	public IAudioFacade
{
public:
	JuceAudioFacade(void);
	~JuceAudioFacade(void);

	// hardware queries
	vector<string> listDrivers();
	vector<string> listDevices(int driverIndex);
	vector<const IAudioDevice* const> listAllDevices();

	// audio methods
	/*
	virtual bool play() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool seek() = 0;
	*/

private:
	AudioDeviceManager mAudioDeviceManager;
	vector<const IAudioDevice* const> mAudioDevices;
	vector<string> mDrivers;
};

