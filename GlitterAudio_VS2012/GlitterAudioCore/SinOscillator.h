#pragma once

#include "BaseAudioGenerator.h"

class AudioMultiBuffer;

class SinOscillator :
	public BaseAudioGenerator
{
public:
	SinOscillator(double f, unsigned int fs);
	~SinOscillator(void);

	void setFrequencyInHz(double f);
	double getFrequencyInHz() const;

	void setSamplingFrequency(unsigned int fs);
	unsigned int getSamplingFrequency() const;

	void createChunk(unsigned int chunkSize);

private:
	void updateTapsFromConfig();

	double mFrequency;
	unsigned int mSamplingFrequency;

	// filter taps and output buffer
	double mC1, mC2;
	double mLastValues[2];
};

