#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace GlitterAudio
{
	namespace JuceAudio
	{
		class DiracAudioSource : public AudioSource
		{
		public:

			DiracAudioSource(AudioSource* inputSource, bool deleteInputWhenDeleted, float pitchShiftingSemitones);
			~DiracAudioSource();

			void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
			void releaseResources();
			void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

			void setPitchShiftValue(int value);

		private:
			AudioSource* inputSource;
			bool deleteOnExit;

			void *diracL;
			void *diracR;

			float time;
			float pitch;

			int sampleRate;

			CriticalSection lock;

			bool mDoProcess;
		};
	}
}

