#include "AudioDevice.h"

AudioDevice::AudioDevice(AudioDriver driver, unsigned int index, unsigned int maxChannelInput, unsigned int maxChannelOutput)
{
	mDriver = driver;
	mIndex = index;
	mMaxChannelInput = maxChannelInput;
	mMaxChannelOutput = maxChannelOutput;
}


AudioDevice::~AudioDevice(void)
{
}

AudioDriver AudioDevice::getDriver() const
{
	return mDriver;
}

unsigned int AudioDevice::getIndex() const
{
	return mIndex;
}

unsigned int AudioDevice::getMaxChannelInput() const
{
	return mMaxChannelInput;
}

unsigned int AudioDevice::getMaxChannelOutput() const
{
	return mMaxChannelOutput;
}
