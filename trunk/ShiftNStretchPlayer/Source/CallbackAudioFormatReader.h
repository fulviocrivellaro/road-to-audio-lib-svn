#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class IAudioReaderSeekListener;

class CallbackAudioFormatReader :
	public AudioFormatReaderSource
{
public:

	IAudioReaderSeekListener *seekListener;

	CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , IAudioReaderSeekListener *newListener);
	~CallbackAudioFormatReader(void);

	void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
	void setNextReadPosition(int64 newPosition);

private:
	unsigned long currentReadPosition;
};

