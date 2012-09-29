#include "AudioDevice.h"


AudioDevice::AudioDevice(int driverIndex, int deviceIndex, string driver, string name)
{
	AudioDevice::driverIndex = driverIndex;
	AudioDevice::deviceIndex = deviceIndex;
	AudioDevice::driver = driver;
	AudioDevice::name = name;
}

AudioDevice::~AudioDevice(void) {}

// hardware indexes
int AudioDevice::getDriverIndex()
{
	return driverIndex;
}

int AudioDevice::getDeviceIndex()
{
	return deviceIndex;
}

// utils
string AudioDevice::getDriver()
{
	return driver;
}

string AudioDevice::getName()
{
	return name;
}