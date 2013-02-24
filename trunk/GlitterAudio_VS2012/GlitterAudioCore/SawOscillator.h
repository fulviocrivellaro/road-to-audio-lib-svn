#pragma once

#include "BaseAudioGenerator.h"

class SawOscillator :
	public BaseAudioGenerator
{
public:
	SawOscillator(double f, unsigned int fs);
	~SawOscillator(void);

	void setFrequencyInHz(double f);
	double getFrequencyInHz() const;

	void setSamplingFrequency(unsigned int fs);
	unsigned int getSamplingFrequency() const;

private:
	void updateDiffFromConfig();

	double mFrequency;
	unsigned int mSamplingFrequency;

	double mDiff;
	double mLastValue;
};

