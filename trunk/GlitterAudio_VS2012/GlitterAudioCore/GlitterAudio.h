#pragma once

#define __GLITTERAUDIO__USE__RTAUDIO__

#include "GlitterAudioDefines.h"
#include "IAudioHardwareFacade.h"

class IAudioPlayer;
class IAudioChain;

class GlitterAudio
{
public:
	GlitterAudio(void);
	~GlitterAudio(void);

	std::vector<const AudioDevice* const> listAllDevices() const;
	std::vector<const AudioDevice* const> listDevicesForDriver(AudioDriver driver) const;

	IAudioPlayer* getBufferedAudioPlayerForDevice();

	void setAudioChain(IAudioChain* audioChain);

	// transport
	void start();
	void stop();

private:
	IAudioHardwareFacade* facade;
	IAudioChain* mAudioChain;
};