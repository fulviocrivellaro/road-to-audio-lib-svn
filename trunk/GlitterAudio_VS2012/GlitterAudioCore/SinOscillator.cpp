#include "SinOscillator.h"
#include "CircularMultiBuffer.h"
#include "Utils.h"
#include <math.h>

SinOscillator::SinOscillator(void)
{
	SinOscillator(0, 0);
}

SinOscillator::SinOscillator(double f, unsigned int fs)
{
	mFrequency = f;
	mSamplingFrequency = fs;
	updateTapsFromConfig();

	mBuffer = new CircularMultiBuffer(1, 8192);
}

SinOscillator::~SinOscillator(void)
{
	delete mBuffer;
}

void SinOscillator::setFrequencyInHz(double f)
{
	mFrequency = f;
	updateTapsFromConfig();
}

double SinOscillator::getFrequencyInHz() const
{
	return mFrequency;
}

void SinOscillator::setSamplingFrequency(unsigned int fs)
{
	mSamplingFrequency = fs;
	updateTapsFromConfig();
}

unsigned int SinOscillator::getSamplingFrequency() const
{
	return mSamplingFrequency;
}

void SinOscillator::updateTapsFromConfig()
{
	if (mFrequency != 0 && mSamplingFrequency != 0)
	{
		double dphi = 2 * PI * mFrequency / mSamplingFrequency;

		// 2nd order oscillator
		const double a = sin(-2*dphi);
		const double b = sin(-dphi);
		const double c = 0;
		const double d = sin(dphi);
		const double det = a*c - b*b;

		mC1 = -d/b;      // (c*c - b*d) / det;
		mC1 = (c*c - b*d) / det;
		mC2 = -a*mC1/b;  // (a*d - b*c) / det;
		mC2 = (a*d - b*c) / det;

		mLastValues[0] = a;
		mLastValues[1] = b;
	} else {
		// causes 'mute'
		mC1 = 0;
		mC2 = 0;
		mLastValues[0] = 0;
		mLastValues[1] = 0;
	}
	
}

void SinOscillator::fillChunk(double* buffer, unsigned int channel, unsigned int chunkSize)
{
	mBuffer->fillChunk(buffer, channel, chunkSize);
}

void SinOscillator::createChunk(unsigned int chunkSize)
{
	double* chunk = new double[chunkSize];
	for (int i=0; i<chunkSize; i++)
	{
		double sample = mC1*mLastValues[0] + mC2*mLastValues[1];
		mLastValues[0] = mLastValues[1];
		mLastValues[1] = sample;
		
		chunk[i] = sample;
	}
	mBuffer->bufferChunk(chunk, 0, chunkSize);

	delete[] chunk;
}