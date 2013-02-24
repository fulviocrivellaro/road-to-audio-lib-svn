#pragma once

#include "IAudioHardwareFacade.h"

class RtAudio;
class IAudioPlayer;

class RtAudioHardwareFacade :
	public IAudioHardwareFacade
{
public:
	RtAudioHardwareFacade(void);
	~RtAudioHardwareFacade(void);

	std::vector<const AudioDevice* const> listAllDevices() const;
	std::vector<const AudioDevice* const> listDevicesForDriver(AudioDriver driver) const;

	IAudioPlayer* getAudioPlayer();
	
private:
	RtAudio* mRtAudio;

	std::vector<const AudioDevice* const> mDevices;
};

