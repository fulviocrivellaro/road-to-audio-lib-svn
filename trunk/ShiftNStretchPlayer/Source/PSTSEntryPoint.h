#pragma once

#include "GUIHandler.h"
#include "GUIReceiver.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "CallbackAudioFormatReader.h"
#include "IAudioReaderSeekListener.h"

#include <string>

namespace GlitterAudio {
	namespace Core {
		namespace Audio {
			class IAudioFacade;
		}

		class PSTSEntryPoint : public GlitterAudio::EventHandling::GUIReceiver, Audio::IAudioReaderSeekListener
		{
		public:
			PSTSEntryPoint(GlitterAudio::EventHandling::GUIHandler *newGUIHandler);
			~PSTSEntryPoint(void);
			void run(void);

			// receive the panpot value
			virtual void onPitchShiftValueChanged(int value);
			virtual void onTimeStretchValueChanged(int value);

			// receive the buttons' callbacks
			virtual void onStartPressed();
			virtual void onPausePressed();
			virtual void onStopPressed();

			// receive new filename
			virtual void onFileSelected(std::string fileName);

			// receive the progress bar
			virtual void onProgressValueChanged(int value);

			// listen to progress seek
			void onSeek(int samplesRead, long currentPosition);

		private:
			// utils
			int duration;
			long positionInSamples, previousPosition;
			GlitterAudio::EventHandling::GUIHandler *guiHandler;
			GlitterAudio::Core::Audio::IAudioFacade *mAudioFacade;

			void prepareForFilename(std::string filename);
			void resetGui();
		};
	}
}

