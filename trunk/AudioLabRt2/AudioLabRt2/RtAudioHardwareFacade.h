#pragma once

#include "IAudioHardwareFacade.h"
#include "RtAudio.h"

class IAudioSink;

class RtAudioHardwareFacade :
	public IAudioHardwareFacade
{
public:
	RtAudioHardwareFacade(void);
	~RtAudioHardwareFacade(void);

	std::vector<const AudioDevice* const> listAllDevices() const;
	std::vector<const AudioDevice* const> listDevicesForDriver(AudioDriver driver) const;

	IAudioSink* getAudioSink();
	
private:
	RtAudio* mRtAudio;

	std::vector<const AudioDevice* const> mDevices;
};

