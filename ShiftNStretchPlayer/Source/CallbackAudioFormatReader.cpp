#include "CallbackAudioFormatReader.h"
#include "IAudioReaderSeekListener.h"

CallbackAudioFormatReader::CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , IAudioReaderSeekListener *newListener)
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

	const MessageManagerLock mmLock;
	seekListener->onSeek(bufferToFill.numSamples, currentReadPosition);
}

void CallbackAudioFormatReader::setNextReadPosition(int64 newPosition)
{
	AudioFormatReaderSource::setNextReadPosition(newPosition);
	currentReadPosition = newPosition;
}