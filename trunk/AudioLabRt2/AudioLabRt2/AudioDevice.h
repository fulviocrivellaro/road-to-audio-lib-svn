#pragma once

#include "Utils.h"

class AudioDevice
{
public:
	AudioDevice(AudioDriver driver, unsigned int index, unsigned int maxChannelInput, unsigned int maxChannelOutput);
	~AudioDevice(void);

	AudioDriver getDriver() const;
	unsigned int getIndex() const;
	unsigned int getMaxChannelInput() const;
	unsigned int getMaxChannelOutput() const;

private:
	AudioDriver mDriver;
	unsigned int mIndex;
	unsigned int mMaxChannelInput;
	unsigned int mMaxChannelOutput;
};