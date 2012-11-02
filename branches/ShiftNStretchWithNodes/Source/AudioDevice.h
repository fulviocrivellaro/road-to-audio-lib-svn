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
	int getDriverIndex() const;
	int getDeviceIndex() const;

	// utils
	string getDriver() const;
	string getName() const;

private:

	int mDriverIndex;
	int mDeviceIndex;

	string mDriver;
	string mName;
};

