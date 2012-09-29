#pragma once

#include <string>

using namespace std;

class IAudioDevice
{
public:
	virtual ~IAudioDevice(void) {};

	// hardware indexes
	virtual int getDriverIndex() = 0;
	virtual int getDeviceIndex() = 0;

	// utils
	virtual string getDriver() = 0;
	virtual string getName() = 0;
};

