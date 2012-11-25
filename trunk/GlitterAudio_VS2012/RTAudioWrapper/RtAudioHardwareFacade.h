#pragma once

#include "IAudioHardwareFacade.h"

class RtAudio;
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
	IAudioSink* getBufferedAudioSink();
	
private:
	RtAudio* mRtAudio;

	std::vector<const AudioDevice* const> mDevices;
};

