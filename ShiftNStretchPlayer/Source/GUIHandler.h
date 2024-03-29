#pragma once

#include <set>
#include <string>

namespace GlitterAudio {
	namespace EventHandling {
		class GUIHandler
		{
		public:

			virtual ~GUIHandler(void) {}

			// set the panpot value
			virtual void setPitchShiftValue(int value) = 0;
			virtual void setTimeStretchValue(int value) = 0;

			// set the mode
			virtual void doStart() = 0;
			virtual void doPause() = 0;
			virtual void doStop() = 0;

			// set the progress bar
			virtual void setProgress(int current, int duration) = 0;

			// register the knon audio formats
			virtual void registerAudioFormats(std::set<std::string> formats) = 0;

		};
	}
}
