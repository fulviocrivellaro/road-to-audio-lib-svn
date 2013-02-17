#pragma once

#include <vector>
#include <string>

#include "AudioDevice.h"
#include "Utils.h"

class IAudioPlayer;

class IAudioHardwareFacade
{
public:
	// hardware methods
	//virtual std::vector<AudioDriver> listDrivers() const = 0;
	virtual std::vector<const AudioDevice* const> listDevicesForDriver(AudioDriver driver) const = 0;
	virtual std::vector<const AudioDevice* const> listAllDevices() const = 0;

	//virtual std::set<std::string> getSupportedAudioFormats() const = 0;

	// Query methods
	/*virtual bool setFileSource(std::string filename) = 0;
	virtual int getSamplingFrequency() const = 0;
	virtual long getSourceLength() const = 0;
	virtual bool isPlaying() const = 0;

	// transport methods
	virtual bool play() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool seek(long newPosition) = 0;

	// FX methods
	virtual void setPitchShiftingSemitones(int value)  = 0;

	// callbacks
	virtual void setAudioSeekListener(IAudioReaderSeekListener *listener) = 0;*/

	virtual IAudioPlayer* getBufferedAudioPlayer() = 0;
};