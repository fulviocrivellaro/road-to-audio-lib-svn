#pragma once

#include <string>

using namespace std;

class IAudioDevice
{
public:
	virtual ~IAudioDevice(void) {};

	// hardware indexes
	virtual int getDriverIndex() const = 0;
	virtual int getDeviceIndex() const = 0;

	// utils
	virtual string getDriver() const = 0;
	virtual string getName() const = 0;
};

