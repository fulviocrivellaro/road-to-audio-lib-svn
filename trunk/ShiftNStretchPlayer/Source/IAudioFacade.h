#pragma once

#include <vector>
#include <string>

#include "AudioDevice.h"

using namespace std;

class IAudioFacade
{
public:
	virtual ~IAudioFacade(void) {};

	// hardware methods
	virtual vector<string> listDrivers() = 0;
	virtual vector<string> listDevices(int driver) = 0;
	virtual vector<AudioDevice> listAllDevices() = 0;

	// audio methods
	/*
	virtual bool play() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool seek() = 0;
	*/
};

