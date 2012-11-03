#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace GlitterAudio {
	namespace Core {
		namespace Audio {
			class IAudioReaderSeekListener;
		}
	}

	namespace JuceAudio {
		class CallbackAudioFormatReader : public AudioFormatReaderSource
		{
		public:

			GlitterAudio::Core::Audio::IAudioReaderSeekListener *seekListener;

			CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , GlitterAudio::Core::Audio::IAudioReaderSeekListener *newListener);
			~CallbackAudioFormatReader(void);

			void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
			void setNextReadPosition(int64 newPosition);

		private:
			unsigned long currentReadPosition;
		};
	}
}