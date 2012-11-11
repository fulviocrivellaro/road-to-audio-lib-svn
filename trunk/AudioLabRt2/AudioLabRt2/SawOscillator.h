#pragma once

#include "IAudioSource.h"

class SawOscillator :
	public IAudioSource
{
public:
	SawOscillator(void);
	SawOscillator(double f, unsigned int fs);
	~SawOscillator(void);

	void setFrequencyInHz(double f);
	double getFrequencyInHz() const;

	void setSamplingFrequency(unsigned int fs);
	unsigned int getSamplingFrequency() const;

	void fillChunk(double* buffer, unsigned int chunkSize);

private:
	void updateDiffFromConfig();

	double mFrequency;
	unsigned int mSamplingFrequency;

	double mDiff;
	double mLastValue;
};

