#include "CallbackAudioFormatReader.h"
#include "IAudioReaderSeekListener.h"

namespace GlitterAudio {
	namespace JuceAudio {
		CallbackAudioFormatReader::CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , GlitterAudio::Core::Audio::IAudioReaderSeekListener *newListener)
			: AudioFormatReaderSource(readerSource, deleteReaderWhenThisIsDeleted ), seekListener(newListener)
		{
			// default, base constructor
			currentReadPosition = 0;
		}


		CallbackAudioFormatReader::~CallbackAudioFormatReader(void)
		{
		}

		void CallbackAudioFormatReader::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
		{
			AudioFormatReaderSource::getNextAudioBlock(bufferToFill);

			currentReadPosition += bufferToFill.numSamples;

			seekListener->onSeek(bufferToFill.numSamples, currentReadPosition);
		}

		void CallbackAudioFormatReader::setNextReadPosition(int64 newPosition)
		{
			AudioFormatReaderSource::setNextReadPosition(newPosition);
			currentReadPosition = newPosition;
		}
	}
}