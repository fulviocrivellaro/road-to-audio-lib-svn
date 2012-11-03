#pragma once

#include "IAudioFacade.h"
#include "IAudioReaderSeekListener.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <set>
#include <vector>
#include <string>

namespace GlitterAudio {

	namespace JuceAudio {
		class DiracAudioSource;
	}

	namespace Core {
		namespace Audio {
			class IAudioFacade;
			class IAudioReaderSeekListener;
		}
	}

	namespace Abstraction {
		class JuceAudioFacade : public GlitterAudio::Core::Audio::IAudioFacade, GlitterAudio::Core::Audio::IAudioReaderSeekListener
		{
		public:
			JuceAudioFacade(void);
			virtual ~JuceAudioFacade(void);

			// hardware queries
			std::vector<std::string> listDrivers() const;
			std::vector<std::string> listDevices(int driverIndex) const;
			std::vector<const GlitterAudio::Core::Audio::IAudioDevice* const> listAllDevices() const;
			std::set<std::string> getSupportedAudioFormats() const;

			bool setFileSource(std::string filename);
			int getSamplingFrequency() const;
			long getSourceLength() const;
			bool isPlaying() const;

			// transport methods
			bool play();
			bool stop();
			bool pause();
			bool seek(long newPosition);

			// FX methods
			void setPitchShiftingSemitones(int value);

			void onSeek(int samplesRead, long currentPosition);

			void setAudioSeekListener(IAudioReaderSeekListener *newSeekListener);

		private:
			AudioDeviceManager mAudioDeviceManager;
			AudioFormatManager mAudioFormatManager;
			std::vector<const GlitterAudio::Core::Audio::IAudioDevice* const> mAudioDevices;
			AudioSourcePlayer *mAudioSourcePlayer;
			AudioFormatReaderSource *mAudioFormatReaderSource;
			GlitterAudio::JuceAudio::DiracAudioSource *mDiracAudioSource;
			std::vector<std::string> mDrivers;
			IAudioReaderSeekListener *seekListener;

			int fs;
			long length;

			int mPitchShiftingSemitones;
		};
	}
}
