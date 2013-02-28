#pragma once

#include "BaseAudioSource.h"

class SinOscillator :
	public BaseAudioSource
{
public:
	SinOscillator(double f, unsigned int fs, unsigned int bufferSize);
	~SinOscillator(void);

	void setFrequencyInHz(double f);
	double getFrequencyInHz() const;

	void setSamplingFrequency(unsigned int fs);
	unsigned int getSamplingFrequency() const;

	unsigned int processChunk(unsigned int chunkSize);

private:
	void updateTapsFromConfig();

	double mFrequency;
	unsigned int mSamplingFrequency;

	// filter taps and output buffer
	double mC1, mC2;
	double mLastValues[2];
};

