/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Sep 2012 6:31:57pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINGUI_MAINGUI_C121884B__
#define __JUCER_HEADER_MAINGUI_MAINGUI_C121884B__

//[Headers]     -- You can add your own extra header files here --
#include <../JuceLibraryCode/JuceHeader.h>
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
    //[/UserVariables]

    //==============================================================================
    Slider* sliderPitchShift;
    Label* label;
    Label* label2;
    Slider* sliderTimeStretch;
    Label* label3;
    TextButton* btnStop;
    TextButton* btnRewind;
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


#endif   // __JUCER_HEADER_MAINGUI_MAINGUI_C121884B__
