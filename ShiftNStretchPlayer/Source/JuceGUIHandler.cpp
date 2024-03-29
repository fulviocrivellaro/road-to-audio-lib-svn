#include "JuceGUIHandler.h"

namespace GlitterAudio {
	namespace JuceGUI {
		JuceGUIHandler::JuceGUIHandler(MainGUI *newGui)
		{
			gui = newGui;
		}


		JuceGUIHandler::~JuceGUIHandler(void)
		{
		}

		MainGUI* JuceGUIHandler::getGUI()
		{
			return gui;
		}

		void JuceGUIHandler::setPitchShiftValue(int value)
		{
			gui->setPitchShiftValue(value);
		}

		void JuceGUIHandler::setTimeStretchValue(int value)
		{
			gui->setTimeStretchValue(value);
		}

		// set the mode
		void JuceGUIHandler::doStart()
		{
			gui->doStart();
		}

		void JuceGUIHandler::doPause()
		{
			gui->doPause();
		}

		void JuceGUIHandler::doStop()
		{
			gui->doStop();
		}

		// set the progress bar
		void JuceGUIHandler::setProgress(int current, int duration)
		{
			gui->setProgress(current, duration);
		}

		void JuceGUIHandler::registerAudioFormats(std::set<std::string> formats)
		{
			gui->registerAudioFormats(formats);
		}
	}
}