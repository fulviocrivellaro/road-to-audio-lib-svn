#pragma once

#include "BaseAudioSource.h"

class SawOscillator :
	public BaseAudioSource
{
public:
	SawOscillator(double f, unsigned int fs);
	~SawOscillator(void);

	void setFrequencyInHz(double f);
	double getFrequencyInHz() const;

	void setSamplingFrequency(unsigned int fs);
	unsigned int getSamplingFrequency() const;

	unsigned int processChunk(unsigned int chunkSize);

private:
	void updateDiffFromConfig();

	double mFrequency;
	unsigned int mSamplingFrequency;

	double mDiff;
	double mLastValue;
};

