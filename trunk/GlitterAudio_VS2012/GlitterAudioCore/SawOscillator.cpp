#include "SawOscillator.h"

#include "AudioMultiBuffer.h"

SawOscillator::SawOscillator(double f, unsigned int fs)
	: BaseAudioSource()
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

unsigned int SawOscillator::processChunk(unsigned int chunkSize)
{
	double* chunk;
	unsigned int count = mSourceBuffer->takeChunk(&chunk, 0, chunkSize);
	for (int i=0; i<count; i++)
	{
		mLastValue += mDiff;
		if (mLastValue > 1)
		{
			mLastValue -= 2;
		}
		chunk[i] = .25*mLastValue;
	}
	
	mSourceBuffer->convalidateChunk(0, count);

	return chunkSize;
}