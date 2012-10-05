#pragma once

#include "IAudioFacade.h"
#include "IAudioReaderSeekListener.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <set>
#include <vector>
#include <string>

using namespace std;

class JuceAudioFacade :
	public IAudioFacade, IAudioReaderSeekListener
{
public:
	JuceAudioFacade(void);
	virtual ~JuceAudioFacade(void);

	// hardware queries
	vector<string> listDrivers() const;
	vector<string> listDevices(int driverIndex) const;
	vector<const IAudioDevice* const> listAllDevices() const;
	set<string> getSupportedAudioFormats() const;

	bool setFileSource(std::string filename);
	int getSamplingFrequency() const;
	long getSourceLength() const;

	// transport methods
	bool play();
	bool stop();
	bool pause();
	bool seek(long newPosition);

	void onSeek(int samplesRead, long currentPosition);

	void setAudioSeekListener(IAudioReaderSeekListener *newSeekListener);

private:
	AudioDeviceManager mAudioDeviceManager;
	AudioFormatManager mAudioFormatManager;
	vector<const IAudioDevice* const> mAudioDevices;
	AudioSourcePlayer *mAudioSourcePlayer;
	AudioFormatReaderSource *mAudioFormatReaderSource;
	vector<string> mDrivers;
	IAudioReaderSeekListener *seekListener;
};

