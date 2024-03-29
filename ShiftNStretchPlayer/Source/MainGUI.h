/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  16 Sep 2012 5:20:06pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINGUI_MAINGUI_CB4C2F14__
#define __JUCER_HEADER_MAINGUI_MAINGUI_CB4C2F14__

//[Headers]     -- You can add your own extra header files here --
#include <../JuceLibraryCode/JuceHeader.h>
#include <set>
#include <string>
#include "GUIReceiver.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainGUI  : public Component,
                 public SliderListener,
                 public ButtonListener
{
public:
    //==============================================================================
    MainGUI ();
    ~MainGUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	// set the panpot value
	void setPitchShiftValue(int value);
	void setTimeStretchValue(int value);

	// set the mode
	void doStart();
	void doPause();
	void doStop();
	void doRewind();

	// set the progress bar
	void setProgress(int current, int duration);

	// add/remove receivers
	void addReceiver(GlitterAudio::EventHandling::GUIReceiver *newReceiver);
	void removeReceiver(GlitterAudio::EventHandling::GUIReceiver *toBeRemovedReceiver);
	void registerAudioFormats(std::set<std::string> formats);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* sound_wave_jpg;
    static const int sound_wave_jpgSize;


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	//GUIReceiver *receiver;
	std::set<GlitterAudio::EventHandling::GUIReceiver*> receivers;
	String mAvailableFormatsString;
    //[/UserVariables]

    //==============================================================================
    Slider* sliderPitchShift;
    Label* label;
    Label* label2;
    Slider* sliderTimeStretch;
    Label* label3;
    TextButton* btnStop;
    TextButton* btnOpen;
    TextButton* btnPlay;
    Slider* sliderPosition;
    Label* labelProgress;
    Label* labelTotalTime;
    Image cachedImage_sound_wave_jpg;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainGUI (const MainGUI&);
    const MainGUI& operator= (const MainGUI&);
};


#endif   // __JUCER_HEADER_MAINGUI_MAINGUI_CB4C2F14__
