#pragma once
#include "JuceHeader.h"

class PSTSEntryPoint;

class CallbackAudioFormatReader :
	public AudioFormatReaderSource
{
public:

	PSTSEntryPoint *seekListener;

	CallbackAudioFormatReader(AudioFormatReader *readerSource, bool deleteThisWhenBoh, PSTSEntryPoint *newListener);
	~CallbackAudioFormatReader(void);

	void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill);
};

