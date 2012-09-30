#include "AudioDevice.h"


AudioDevice::AudioDevice(int driverIndex, int deviceIndex, string driver, string name)
{
	AudioDevice::mDriverIndex = driverIndex;
	AudioDevice::mDeviceIndex = deviceIndex;
	AudioDevice::mDriver = driver;
	AudioDevice::mName = name;
}

AudioDevice::~AudioDevice(void) {}

// hardware indexes
inline int AudioDevice::getDriverIndex() const
{
	return mDriverIndex;
}

inline int AudioDevice::getDeviceIndex() const
{
	return mDeviceIndex;
}

// utils
inline string AudioDevice::getDriver() const
{
	return mDriver;
}

inline string AudioDevice::getName() const
{
	return mName;
}