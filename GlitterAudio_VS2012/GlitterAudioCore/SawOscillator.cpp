#include "SawOscillator.h"


SawOscillator::SawOscillator(double f, unsigned int fs)
	: BaseAudioGenerator()
{
	mFrequency = f;
	mSamplingFrequency = fs;
	updateDiffFromConfig();
	mLastValue = 0;
}

SawOscillator::~SawOscillator(void) {}

void SawOscillator::setFrequencyInHz(double f)
{
	mFrequency = f;
	updateDiffFromConfig();
}

double SawOscillator::getFrequencyInHz() const
{
	return mFrequency;
}

void SawOscillator::setSamplingFrequency(unsigned int fs)
{
	mSamplingFrequency = fs;
	updateDiffFromConfig();
}

unsigned int SawOscillator::getSamplingFrequency() const
{
	return mSamplingFrequency;
}

void SawOscillator::updateDiffFromConfig()
{
	if (mFrequency != 0 && mSamplingFrequency != 0)
	{
		mDiff = 2 * mFrequency / mSamplingFrequency;
	} else {
		// causes 'mute'
		mDiff = 0;
		mLastValue = 0;
	}
	
}

//void SawOscillator::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
//{
//	for (int i=0; i<chunkSize; i++)
//	{
//		mLastValue += mDiff;
//		if (mLastValue > 1)
//		{
//			mLastValue -= 2;
//		}
//		*buffer++ = mLastValue;
//	}
//}