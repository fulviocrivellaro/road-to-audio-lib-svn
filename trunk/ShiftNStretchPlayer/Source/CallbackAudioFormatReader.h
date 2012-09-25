#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class PSTSEntryPoint;

class CallbackAudioFormatReader :
	public AudioFormatReaderSource
{
public:

	PSTSEntryPoint *seekListener;

	CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteReaderWhenThisIsDeleted , PSTSEntryPoint *newListener);
	~CallbackAudioFormatReader(void);

	void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
};

