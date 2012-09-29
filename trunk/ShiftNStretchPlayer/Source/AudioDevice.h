#pragma once

#include "IAudioDevice.h"
#include <string>

using namespace std;

class AudioDevice :
	public IAudioDevice
{
public:
	
	AudioDevice(int driverIndex, int deviceIndex, string driver = "", string name = "");
	~AudioDevice(void);

	// hardware indexes
	int getDriverIndex();
	int getDeviceIndex();

	// utils
	string getDriver();
	string getName();

private:

	int driverIndex;
	int deviceIndex;

	string driver;
	string name;
};

