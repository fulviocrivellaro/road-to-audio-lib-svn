#include "DiracAudioSource.h"
#include "../libs/Dirac.h"
#include <math.h>

DiracAudioSource::DiracAudioSource(AudioSource* inputSource, bool deleteInputWhenDeleted, float pitchShiftingSemitones)
	: deleteOnExit(deleteInputWhenDeleted)
{
	DiracAudioSource::inputSource = inputSource;
	time = 1;
	pitch = pow(2., pitchShiftingSemitones/12.);
}

DiracAudioSource::~DiracAudioSource()
{
	if (deleteOnExit)
	{
		delete inputSource;
	}
}

void DiracAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	const ScopedLock sl (lock);

	inputSource->prepareToPlay (samplesPerBlockExpected, sampleRate);

	// create dirac instance
	diracL = DiracFxCreate(kDiracQualityBetter, sampleRate, 1);
	diracR = DiracFxCreate(kDiracQualityBetter, sampleRate, 1);

	DiracAudioSource::sampleRate = sampleRate;

	mDoProcess = true;
}

void DiracAudioSource::releaseResources()
{
	mDoProcess = false;

	const ScopedLock sl (lock);
	inputSource->releaseResources();
	//DiracDestroy(diracL);
	//DiracDestroy(diracR);
}

void DiracAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	const ScopedLock sl (lock);
	inputSource->getNextAudioBlock(bufferToFill);

	if (mDoProcess)
	{
		float* channelL = bufferToFill.buffer->getSampleData(0, bufferToFill.startSample);
		float** audioInL = &channelL;

		float* channelR = bufferToFill.buffer->getSampleData(1, bufferToFill.startSample);
		float** audioInR = &channelR;

		long retL = DiracFxProcessFloat(time, pitch, audioInL, audioInL, bufferToFill.numSamples, diracL);
		long retR = DiracFxProcessFloat(time, pitch, audioInR, audioInR, bufferToFill.numSamples, diracR);
	}
}

void DiracAudioSource::setPitchShiftValue(int value)
{
	const ScopedLock sl (lock);

	pitch = pow(2., value/12.);
}