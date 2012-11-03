#pragma once

#include <set>
#include <vector>
#include <string>

#include "IAudioDevice.h"

namespace GlitterAudio {
	namespace Core {
		namespace Audio {
			using namespace std;

			class IAudioReaderSeekListener;

			class IAudioFacade
			{
			public:
				virtual ~IAudioFacade(void) {};

				// hardware methods
				virtual std::vector<std::string> listDrivers() const = 0;
				virtual std::vector<std::string> listDevices(int driver) const = 0;
				virtual std::vector<const IAudioDevice* const> listAllDevices() const = 0;
				virtual std::set<std::string> getSupportedAudioFormats() const = 0;

				// Query methods
				virtual bool setFileSource(std::string filename) = 0;
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
				virtual void setAudioSeekListener(IAudioReaderSeekListener *listener) = 0;
			};
		}
	}
}

