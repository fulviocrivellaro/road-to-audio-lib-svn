#pragma once

#define __GLITTERAUDIO__USE__RTAUDIO__

#include "GlitterAudioDefines.h"
#include "IAudioHardwareFacade.h"

class IAudioSink;

class GlitterAudio
{
public:
	GlitterAudio(void);
	~GlitterAudio(void);

	std::vector<const AudioDevice* const> listAllDevices() const;
	std::vector<const AudioDevice* const> listDevicesForDriver(AudioDriver driver) const;

	IAudioSink* getAudioSinkForDevice();
	IAudioSink* getBufferedAudioSinkForDevice();

private:
	IAudioHardwareFacade* facade;
};