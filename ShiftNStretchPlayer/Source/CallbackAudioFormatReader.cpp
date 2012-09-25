#include "CallbackAudioFormatReader.h"
#include "PSTSEntryPoint.h"

CallbackAudioFormatReader::CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , PSTSEntryPoint *newListener)
	: AudioFormatReaderSource(readerSource, deleteReaderWhenThisIsDeleted ), seekListener(newListener)
{
	// default, base constructor
}


CallbackAudioFormatReader::~CallbackAudioFormatReader(void)
{
}

void CallbackAudioFormatReader::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
	AudioFormatReaderSource::getNextAudioBlock(bufferToFill);

	const MessageManagerLock mmLock;
	seekListener->onSeek(bufferToFill.numSamples);
}