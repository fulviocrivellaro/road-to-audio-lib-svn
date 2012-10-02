#pragma once

#include <vector>
#include <string>

#include "IAudioDevice.h"

using namespace std;

class IAudioReaderSeekListener;

class IAudioFacade
{
public:
	virtual ~IAudioFacade(void) {};

	// hardware methods
	virtual vector<string> listDrivers() const = 0;
	virtual vector<string> listDevices(int driver) const = 0;
	virtual vector<const IAudioDevice* const> listAllDevices() const = 0;

	//
	virtual bool setFileSource(std::string filename) = 0;
	virtual int getSamplingFrequency() const = 0;
	virtual long getSourceLength() const = 0;

	// transport methods
	virtual bool play() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool seek(long newPosition) = 0;

	// callbacks
	virtual void setAudioSeekListener(IAudioReaderSeekListener *listener) = 0;
	
};

