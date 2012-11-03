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

//[Headers] You can add your own extra header files here...
#include <string>
//[/Headers]

#include "MainGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainGUI::MainGUI ()
    : Component (L"Pitch & Stretch"),
      sliderPitchShift (0),
      label (0),
      label2 (0),
      sliderTimeStretch (0),
      label3 (0),
      btnStop (0),
      btnOpen (0),
      btnPlay (0),
      sliderPosition (0),
      labelProgress (0),
      labelTotalTime (0),
      cachedImage_sound_wave_jpg (0)
{
    addAndMakeVisible (sliderPitchShift = new Slider (L"Pitch Shift"));
    sliderPitchShift->setRange (-4, 4, 1);
    sliderPitchShift->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderPitchShift->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    sliderPitchShift->setColour (Slider::textBoxBackgroundColourId, Colour (0xffffff));
    sliderPitchShift->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    sliderPitchShift->addListener (this);

    addAndMakeVisible (label = new Label (L"new label",
                                          L"Pitch Shift\n(Semitones)"));
    label->setFont (Font (15.0000f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label2 = new Label (L"new label",
                                           L"Time Stretch\n(Percentage)"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (sliderTimeStretch = new Slider (L"Time Stretch"));
    sliderTimeStretch->setRange (50, 200, 5);
    sliderTimeStretch->setSliderStyle (Slider::RotaryVerticalDrag);
    sliderTimeStretch->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    sliderTimeStretch->setColour (Slider::textBoxBackgroundColourId, Colour (0xffffff));
    sliderTimeStretch->setColour (Slider::textBoxOutlineColourId, Colour (0x808080));
    sliderTimeStretch->addListener (this);
    sliderTimeStretch->setSkewFactor (0.62);

    addAndMakeVisible (label3 = new Label (L"new label",
                                           L"TRANSPORT"));
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (btnStop = new TextButton (L"Stop button"));
    btnStop->setButtonText (L"Stop");
    btnStop->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    btnStop->addListener (this);

    addAndMakeVisible (btnOpen = new TextButton (L"Open button"));
    btnOpen->setButtonText (L"Open...");
    btnOpen->setConnectedEdges (Button::ConnectedOnLeft);
    btnOpen->addListener (this);

    addAndMakeVisible (btnPlay = new TextButton (L"Play button"));
    btnPlay->setButtonText (L"Play");
    btnPlay->setConnectedEdges (Button::ConnectedOnRight);
    btnPlay->addListener (this);
    btnPlay->setColour (TextButton::buttonOnColourId, Colour (0xff137507));

    addAndMakeVisible (sliderPosition = new Slider (L"Position slider"));
    sliderPosition->setRange (0, 100, 0);
    sliderPosition->setSliderStyle (Slider::LinearHorizontal);
    sliderPosition->setTextBoxStyle (Slider::NoTextBox, true, 40, 20);
    sliderPosition->addListener (this);

    addAndMakeVisible (labelProgress = new Label (L"Time label",
                                                  L"0:00"));
    labelProgress->setFont (Font (Font::getDefaultMonospacedFontName(), 12.0000f, Font::plain));
    labelProgress->setJustificationType (Justification::bottomRight);
    labelProgress->setEditable (false, false, false);
    labelProgress->setColour (TextEditor::textColourId, Colours::black);
    labelProgress->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (labelTotalTime = new Label (L"Total time label",
                                                   L"40:00"));
    labelTotalTime->setFont (Font (Font::getDefaultMonospacedFontName(), 12.0000f, Font::plain));
    labelTotalTime->setJustificationType (Justification::bottomRight);
    labelTotalTime->setEditable (false, false, false);
    labelTotalTime->setColour (TextEditor::textColourId, Colours::black);
    labelTotalTime->setColour (TextEditor::backgroundColourId, Colour (0x0));

    cachedImage_sound_wave_jpg = ImageCache::getFromMemory (sound_wave_jpg, sound_wave_jpgSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 400);


    //[Constructor] You can add your own custom stuff here..
    //receivers = vect;
	btnPlay->setClickingTogglesState(true);
	sliderTimeStretch->setValue(100, false);
	sliderTimeStretch->setTextValueSuffix("%");
	setBounds(100, 100, 300, 400);
	mAvailableFormatsString = "";
    //[/Constructor]
}

MainGUI::~MainGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (sliderPitchShift);
    deleteAndZero (label);
    deleteAndZero (label2);
    deleteAndZero (sliderTimeStretch);
    deleteAndZero (label3);
    deleteAndZero (btnStop);
    deleteAndZero (btnOpen);
    deleteAndZero (btnPlay);
    deleteAndZero (sliderPosition);
    deleteAndZero (labelProgress);
    deleteAndZero (labelTotalTime);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainGUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffd4d0c8));

    g.setColour (Colours::black);
    g.drawImage (cachedImage_sound_wave_jpg,
                 10, 10, 280, 150,
                 0, 0, cachedImage_sound_wave_jpg.getWidth(), cachedImage_sound_wave_jpg.getHeight());

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainGUI::resized()
{
    sliderPitchShift->setBounds (50, 220, 80, 66);
    label->setBounds (40, 180, 100, 30);
    label2->setBounds (160, 180, 100, 30);
    sliderTimeStretch->setBounds (170, 220, 80, 66);
    label3->setBounds (70, 300, 160, 24);
    btnStop->setBounds (110, 330, 80, 24);
    btnOpen->setBounds (190, 330, 80, 24);
    btnPlay->setBounds (30, 330, 80, 24);
    sliderPosition->setBounds (60, 370, 190, 24);
    labelProgress->setBounds (10, 376, 50, 14);
    labelTotalTime->setBounds (240, 376, 50, 14);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainGUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderPitchShift)
    {
        //[UserSliderCode_sliderPitchShift] -- add your slider handling code here..
		std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
		for (it=receivers.begin(); it != receivers.end(); it++)
		{
			(*it)->onPitchShiftValueChanged(sliderPitchShift->getValue());
		}
        //[/UserSliderCode_sliderPitchShift]
    }
    else if (sliderThatWasMoved == sliderTimeStretch)
    {
        //[UserSliderCode_sliderTimeStretch] -- add your slider handling code here..
		std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
        for (it=receivers.begin(); it != receivers.end(); it++)
		{
			(*it)->onTimeStretchValueChanged(sliderTimeStretch->getValue());
		}
        //[/UserSliderCode_sliderTimeStretch]
    }
    else if (sliderThatWasMoved == sliderPosition)
    {
        //[UserSliderCode_sliderPosition] -- add your slider handling code here..
		int position = sliderPosition->getValue();
		std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
		for (it=receivers.begin(); it != receivers.end(); it++)
		{
			(*it)->onProgressValueChanged(position);
		}
        //[/UserSliderCode_sliderPosition]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainGUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnStop)
    {
        //[UserButtonCode_btnStop] -- add your button handler code here..
		std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
		for (it=receivers.begin(); it != receivers.end(); it++)
		{
			(*it)->onStopPressed();
		}
        //[/UserButtonCode_btnStop]
    }
    else if (buttonThatWasClicked == btnOpen)
    {
        //[UserButtonCode_btnOpen] -- add your button handler code here..
		FileChooser chooser("Choose file to open", File::nonexistent, mAvailableFormatsString);
		if (chooser.browseForFileToOpen())
		{
			String filename = chooser.getResult().getFullPathName();
			std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
			for (it=receivers.begin(); it != receivers.end(); it++)
			{
				(*it)->onFileSelected((const char *)filename.getCharPointer());
			}
		}
        //[/UserButtonCode_btnOpen]
    }
    else if (buttonThatWasClicked == btnPlay)
    {
        //[UserButtonCode_btnPlay] -- add your button handler code here..
		std::set<GlitterAudio::EventHandling::GUIReceiver*>::iterator it;
        for (it=receivers.begin(); it != receivers.end(); it++)
		{
			if (btnPlay->getToggleState())
			{
				(*it)->onStartPressed();
			} else {
				(*it)->onPausePressed();
			}
		}
        //[/UserButtonCode_btnPlay]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

// set the panpot value
void MainGUI::setPitchShiftValue(int value)
{
	sliderPitchShift->setValue(value, false);
}

void MainGUI::setTimeStretchValue(int value)
{
	sliderTimeStretch->setValue(value, false);
}

// set the mode
void MainGUI::doStart()
{
	btnPlay->setToggleState(true, false);
	btnStop->setEnabled(true);
}

void MainGUI::doPause()
{
	btnPlay->setToggleState(false, false);
	btnStop->setEnabled(true);
}

void MainGUI::doStop()
{
	const MessageManagerLock lock;
	btnPlay->setToggleState(false, false);
	btnStop->setEnabled(true);
}

void MainGUI::doRewind()
{
	btnPlay->setToggleState(false, false);
	btnStop->setEnabled(true);
}

// set the progress bar
void MainGUI::setProgress(int current, int duration)
{
	//float percentage = (float)(100*current) / duration;
	int minutes;
	int seconds;
	String currentPositionString;
	String durationPositionString;
	
	const MessageManagerLock lock;

	if (duration == 0)
	{
		// null duration means no file available
		sliderPosition->setEnabled(false);
		currentPositionString = "0:00";
		durationPositionString = "0:00";
		sliderPosition->setRange(0, 1, 1);
	} else {
		// current
		sliderPosition->setEnabled(true);
		minutes = current / 60;
		seconds = current - 60*minutes;
		if (seconds < 10)
		{
			currentPositionString = String(minutes) += String(":0") += String(seconds);
		} else {
			currentPositionString = String(minutes) += String(":") += String(seconds);
		}

		// duration
		minutes = duration / 60;
		seconds = duration - 60*minutes;
		if (seconds < 10)
		{
			durationPositionString = String(minutes) += String(":0") += String(seconds);
		} else {
			durationPositionString = String(minutes) += String(":") += String(seconds);
		}

		sliderPosition->setRange(0, duration, 1);
	}
	
	sliderPosition->setValue(current, false);
	labelProgress->setText(currentPositionString, false);
	labelTotalTime->setText(durationPositionString, false);
}

void MainGUI::addReceiver(GlitterAudio::EventHandling::GUIReceiver *newReceiver)
{
	receivers.insert(newReceiver);
}

void MainGUI::removeReceiver(GlitterAudio::EventHandling::GUIReceiver *toBeRemovedReceiver)
{
	receivers.erase(toBeRemovedReceiver);
}

void MainGUI::registerAudioFormats(std::set<std::string> formats)
{
	int numFormats = formats.size();
	if (numFormats > 0)
	{
		std::set<std::string>::iterator it;
		for (it = formats.begin(); it != formats.end(); it++)
		{
			std::string currentFormat = "*" + *it + ";";
			mAvailableFormatsString += String(currentFormat.c_str());
		}
	}
	DBG("Registered file format audio wildcard: " + mAvailableFormatsString);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainGUI" componentName="Pitch &amp; Stretch"
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="10" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="300" initialHeight="400">
  <BACKGROUND backgroundColour="ffd4d0c8">
    <IMAGE pos="10 10 280 150" resource="sound_wave_jpg" opacity="1" mode="0"/>
  </BACKGROUND>
  <SLIDER name="Pitch Shift" id="6c464ae576ad6223" memberName="sliderPitchShift"
          virtualName="" explicitFocusOrder="0" pos="50 220 80 66" textboxbkgd="ffffff"
          textboxoutline="808080" min="-4" max="4" int="1" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9fbbb049e5b1bd87" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="40 180 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Shift&#10;(Semitones)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="cbddce196479ad0f" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="160 180 100 30" edTextCol="ff000000"
         edBkgCol="0" labelText="Time Stretch&#10;(Percentage)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Time Stretch" id="adcd38df0693abd3" memberName="sliderTimeStretch"
          virtualName="" explicitFocusOrder="0" pos="170 220 80 66" textboxbkgd="ffffff"
          textboxoutline="808080" min="50" max="200" int="5" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.62"/>
  <LABEL name="new label" id="98ed6b63a777fd42" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="70 300 160 24" edTextCol="ff000000"
         edBkgCol="0" labelText="TRANSPORT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="Stop button" id="20706470cab39e4b" memberName="btnStop"
              virtualName="" explicitFocusOrder="0" pos="110 330 80 24" buttonText="Stop"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Open button" id="1026d20b047dea2d" memberName="btnOpen"
              virtualName="" explicitFocusOrder="0" pos="190 330 80 24" buttonText="Open..."
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Play button" id="b93c34b1715dd879" memberName="btnPlay"
              virtualName="" explicitFocusOrder="0" pos="30 330 80 24" bgColOn="ff137507"
              buttonText="Play" connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Position slider" id="80d97635b641600c" memberName="sliderPosition"
          virtualName="" explicitFocusOrder="0" pos="60 370 190 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Time label" id="c97ed12e6c9ec95b" memberName="labelProgress"
         virtualName="" explicitFocusOrder="0" pos="10 376 50 14" edTextCol="ff000000"
         edBkgCol="0" labelText="0:00" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12"
         bold="0" italic="0" justification="18"/>
  <LABEL name="Total time label" id="ff70752e493ea386" memberName="labelTotalTime"
         virtualName="" explicitFocusOrder="0" pos="240 376 50 14" edTextCol="ff000000"
         edBkgCol="0" labelText="40:00" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="12"
         bold="0" italic="0" justification="18"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: sound_wave_jpg, 23973, "../res/images/sound_wave.jpg"
static const unsigned char resource_MainGUI_sound_wave_jpg[] = { 255,216,255,225,14,201,69,120,105,102,0,0,77,77,0,42,0,0,0,8,0,12,1,0,0,3,0,0,0,1,1,24,0,0,1,1,0,3,0,0,0,1,0,150,0,0,1,2,0,3,0,0,0,3,0,
0,0,158,1,6,0,3,0,0,0,1,0,2,0,0,1,18,0,3,0,0,0,1,0,1,0,0,1,21,0,3,0,0,0,1,0,3,0,0,1,26,0,5,0,0,0,1,0,0,0,164,1,27,0,5,0,0,0,1,0,0,0,172,1,40,0,3,0,0,0,1,0,2,0,0,1,49,0,2,0,0,0,30,0,0,0,180,1,50,0,2,0,
0,0,20,0,0,0,210,135,105,0,4,0,0,0,1,0,0,0,232,0,0,1,32,0,8,0,8,0,8,0,14,166,0,0,0,39,16,0,14,166,0,0,0,39,16,65,100,111,98,101,32,80,104,111,116,111,115,104,111,112,32,67,83,54,32,40,87,105,110,100,111,
119,115,41,0,50,48,49,50,58,48,57,58,48,57,32,50,48,58,52,49,58,49,55,0,0,0,0,4,144,0,0,7,0,0,0,4,48,50,50,49,160,1,0,3,0,0,0,1,255,255,0,0,160,2,0,4,0,0,0,1,0,0,1,24,160,3,0,4,0,0,0,1,0,0,0,150,0,0,0,
0,0,0,0,6,1,3,0,3,0,0,0,1,0,6,0,0,1,26,0,5,0,0,0,1,0,0,1,110,1,27,0,5,0,0,0,1,0,0,1,118,1,40,0,3,0,0,0,1,0,2,0,0,2,1,0,4,0,0,0,1,0,0,1,126,2,2,0,4,0,0,0,1,0,0,13,67,0,0,0,0,0,0,0,72,0,0,0,1,0,0,0,72,0,
0,0,1,255,216,255,237,0,12,65,100,111,98,101,95,67,77,0,2,255,238,0,14,65,100,111,98,101,0,100,128,0,0,0,1,255,219,0,132,0,12,8,8,8,9,8,12,9,9,12,17,11,10,11,17,21,15,12,12,15,21,24,19,19,21,19,19,24,
17,12,12,12,12,12,12,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,1,13,11,11,13,14,13,16,14,14,16,20,14,14,14,20,20,14,14,14,14,20,17,12,12,12,12,12,17,17,12,
12,12,12,12,12,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,255,192,0,17,8,0,86,0,160,3,1,34,0,2,17,1,3,17,1,255,221,0,4,0,10,255,196,1,63,0,0,1,5,1,1,1,1,1,1,
0,0,0,0,0,0,0,3,0,1,2,4,5,6,7,8,9,10,11,1,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,2,3,4,5,6,7,8,9,10,11,16,0,1,4,1,3,2,4,2,5,7,6,8,5,3,12,51,1,0,2,17,3,4,33,18,49,5,65,81,97,19,34,113,129,50,6,20,145,161,
177,66,35,36,21,82,193,98,51,52,114,130,209,67,7,37,146,83,240,225,241,99,115,53,22,162,178,131,38,68,147,84,100,69,194,163,116,54,23,210,85,226,101,242,179,132,195,211,117,227,243,70,39,148,164,133,180,
149,196,212,228,244,165,181,197,213,229,245,86,102,118,134,150,166,182,198,214,230,246,55,71,87,103,119,135,151,167,183,199,215,231,247,17,0,2,2,1,2,4,4,3,4,5,6,7,7,6,5,53,1,0,2,17,3,33,49,18,4,65,81,
97,113,34,19,5,50,129,145,20,161,177,66,35,193,82,209,240,51,36,98,225,114,130,146,67,83,21,99,115,52,241,37,6,22,162,178,131,7,38,53,194,210,68,147,84,163,23,100,69,85,54,116,101,226,242,179,132,195,
211,117,227,243,70,148,164,133,180,149,196,212,228,244,165,181,197,213,229,245,86,102,118,134,150,166,182,198,214,230,246,39,55,71,87,103,119,135,151,167,183,199,255,218,0,12,3,1,0,2,17,3,17,0,63,0,243,
166,178,83,250,104,149,181,79,106,127,10,222,36,30,154,94,154,62,196,182,165,194,174,36,30,154,94,154,179,85,83,99,68,114,147,235,218,247,55,192,148,184,52,181,113,139,166,191,166,151,166,142,234,224,
193,77,181,46,21,113,33,21,73,3,197,25,152,146,81,49,234,221,115,66,211,171,27,94,52,82,226,197,197,171,22,92,220,46,91,176,227,178,174,250,75,76,21,208,191,23,67,162,206,203,199,219,192,78,201,134,133,
133,184,179,241,26,46,111,166,151,166,143,177,56,172,150,147,216,21,7,11,63,16,107,250,105,122,104,251,116,75,106,92,42,226,65,233,167,244,209,182,121,39,21,19,172,37,194,174,36,1,131,193,23,25,129,217,
21,53,194,90,94,217,7,130,37,62,196,76,102,254,179,87,245,218,151,10,184,159,255,208,225,106,110,156,34,108,149,42,155,42,222,54,62,227,37,90,142,59,107,75,32,2,208,85,143,51,226,132,218,119,59,108,112,
187,75,58,126,35,186,62,9,99,3,110,103,168,219,93,26,187,121,245,107,221,253,86,251,21,27,58,5,53,244,218,115,88,73,186,203,108,109,205,236,27,63,171,123,127,235,87,169,14,47,151,78,180,215,143,52,61,
86,226,227,227,77,204,211,178,22,78,52,94,68,114,229,181,78,62,219,90,99,134,161,228,227,77,224,199,37,72,112,250,107,197,100,121,159,95,209,200,200,199,33,195,78,193,1,181,203,128,133,187,149,139,238,
111,201,85,175,23,244,131,79,20,201,225,245,50,195,152,28,40,112,49,191,88,18,60,87,73,233,214,222,144,198,6,141,199,33,207,221,222,11,90,207,251,234,207,196,199,219,97,62,18,181,30,223,212,216,223,131,
135,205,207,31,193,79,143,24,17,30,109,76,249,76,165,187,159,233,170,121,184,210,36,14,203,160,192,232,217,89,230,207,68,181,190,155,75,206,238,241,249,163,250,202,171,250,110,69,175,20,49,133,246,184,
195,90,59,148,233,8,200,17,219,117,144,200,98,65,114,49,126,174,93,157,135,147,117,50,236,170,223,75,113,232,111,248,65,99,141,119,127,219,91,169,67,199,232,121,150,116,220,156,198,176,122,88,197,158,
166,186,254,145,222,155,118,143,228,187,233,173,220,60,220,206,146,27,117,0,11,55,189,190,225,48,11,90,207,243,155,185,108,116,67,139,246,123,169,202,33,184,247,91,101,118,142,37,177,35,252,199,57,86,
56,168,147,86,216,60,204,171,126,175,156,58,146,9,17,218,84,177,241,159,117,161,140,18,79,3,196,174,151,235,30,13,13,234,55,89,67,61,58,237,104,181,172,2,0,15,1,241,167,181,84,250,179,141,187,169,210,
79,209,109,155,157,240,103,189,223,245,9,190,214,163,177,102,251,197,192,203,176,115,186,143,72,200,233,189,78,238,159,144,90,235,113,220,3,156,201,218,101,162,193,183,116,59,243,211,51,23,219,199,101,
177,212,106,125,249,181,94,255,0,115,173,165,133,196,242,75,75,235,255,0,190,163,99,244,140,139,177,45,201,96,30,157,27,67,135,115,188,159,163,254,106,124,112,129,187,28,185,157,3,204,58,130,208,76,120,
169,97,80,251,51,41,174,182,151,61,207,16,209,228,11,191,234,66,212,200,194,125,109,123,30,210,199,182,65,105,16,71,201,87,233,47,118,62,117,119,48,195,152,31,7,194,107,177,159,247,229,30,76,92,63,80,
207,143,55,16,36,63,255,209,196,207,198,99,70,45,108,110,215,87,142,202,236,243,123,101,207,255,0,207,136,216,152,163,96,209,19,22,230,231,6,216,225,46,178,231,136,243,118,199,237,255,0,164,187,15,216,
88,118,216,218,104,138,205,117,236,36,15,164,250,230,183,255,0,159,107,86,150,51,8,209,61,156,124,210,151,202,59,185,134,173,184,254,159,238,10,143,222,194,173,53,181,213,78,78,13,141,215,208,169,205,
242,115,63,79,255,0,163,158,165,149,87,165,125,205,229,164,176,15,128,138,213,123,114,198,71,84,200,143,206,47,103,200,53,205,10,82,56,171,183,204,213,18,34,218,152,221,54,204,171,92,218,96,109,99,159,
175,131,125,209,253,164,55,116,204,135,58,183,22,64,121,33,164,240,97,109,244,145,85,120,246,220,76,57,219,106,96,241,221,171,191,234,85,129,107,108,171,17,144,52,176,143,243,142,228,142,67,100,1,166,
202,26,0,111,90,121,206,163,211,44,197,200,117,22,67,157,89,137,26,3,162,165,78,38,235,64,3,83,253,235,177,234,21,85,110,11,237,115,102,199,150,56,56,243,160,218,239,250,165,141,141,129,152,230,187,38,
170,230,186,200,4,247,212,255,0,177,24,76,74,55,45,8,211,234,146,100,44,15,228,18,179,234,248,175,1,217,22,146,219,156,224,88,211,198,200,247,59,252,226,171,100,84,27,80,96,252,218,217,248,151,127,228,
150,166,127,82,189,254,166,59,192,2,150,6,136,242,45,84,198,199,216,224,238,213,215,255,0,124,255,0,201,37,3,42,185,119,189,22,200,139,211,193,135,76,202,183,24,184,176,192,223,91,79,195,118,168,189,63,
32,213,156,235,76,77,97,228,124,117,111,241,90,93,83,31,22,186,24,234,24,26,208,90,201,3,146,201,146,179,43,162,201,202,180,52,237,104,137,254,179,196,32,12,102,12,170,184,180,81,4,26,189,154,93,66,177,
99,70,159,158,243,255,0,82,137,99,61,38,53,190,54,61,223,126,213,44,136,4,52,233,171,207,222,227,253,202,207,86,169,181,122,26,131,186,177,102,159,202,213,63,75,136,239,106,179,94,78,134,37,56,249,76,
196,203,186,176,255,0,179,86,107,112,34,65,21,251,153,255,0,159,22,70,31,69,253,159,147,151,34,61,22,218,7,246,189,140,255,0,162,245,107,11,173,213,70,35,241,159,89,46,116,57,174,210,0,252,249,254,180,
35,228,101,28,172,3,149,183,249,198,53,132,248,185,174,115,93,255,0,158,218,161,225,148,103,181,68,154,31,244,151,241,250,42,251,91,135,145,142,11,49,223,251,187,217,247,16,255,0,253,24,180,186,87,183,
22,218,199,15,58,143,234,144,84,49,89,86,69,66,167,126,109,160,31,131,219,255,0,152,45,102,99,97,226,101,10,203,182,210,92,242,210,79,104,5,186,185,62,114,0,24,214,186,159,177,96,179,173,255,0,34,229,
229,116,151,117,78,163,104,100,53,215,58,103,176,144,177,186,151,69,199,194,234,54,140,111,230,153,88,241,250,65,190,157,220,254,245,205,123,151,73,83,139,31,118,69,102,5,84,23,79,153,30,155,127,42,192,
187,51,117,101,239,247,57,245,196,159,31,80,181,71,49,96,246,140,127,99,62,9,200,17,87,172,135,230,255,0,255,210,193,232,119,17,101,16,127,155,202,169,255,0,40,115,143,254,122,93,38,7,87,204,111,73,61,
66,73,126,253,161,199,81,234,27,62,209,255,0,80,185,94,132,28,234,243,108,7,250,53,7,32,252,0,126,60,255,0,219,153,85,168,215,213,178,89,132,122,126,225,246,127,87,237,17,26,239,219,232,243,251,187,21,
216,207,107,115,178,225,226,38,186,61,94,31,80,183,43,33,198,211,36,144,227,242,125,106,159,73,200,245,122,187,65,225,246,128,127,180,118,170,157,15,168,99,83,144,231,100,186,25,233,91,180,255,0,47,97,
52,183,251,86,53,171,51,19,168,190,140,151,89,89,135,2,11,79,152,83,156,163,70,188,121,115,235,209,238,221,187,31,31,22,151,8,115,172,117,142,249,22,210,223,250,135,171,24,94,145,109,132,188,7,226,177,
183,144,124,26,28,31,255,0,86,197,207,229,253,101,103,80,234,53,218,198,122,53,6,52,6,120,31,167,111,254,10,231,42,63,88,242,91,87,89,190,170,44,154,216,237,146,211,161,27,91,35,79,205,64,203,210,44,209,
43,35,128,241,85,116,122,123,58,203,44,104,195,3,232,83,100,59,196,183,244,205,255,0,162,197,62,155,213,104,173,152,152,246,88,43,110,111,168,44,158,3,75,133,85,63,251,47,173,235,147,193,201,46,234,120,
204,6,93,107,133,64,120,155,1,168,55,254,154,135,94,204,165,189,79,236,116,145,179,9,141,196,36,112,95,87,244,135,127,236,67,173,77,153,141,240,244,37,124,48,203,235,78,253,249,213,229,100,228,186,191,
206,107,200,249,65,72,60,140,155,218,59,48,143,243,67,127,242,43,15,161,60,221,158,41,26,155,26,246,129,241,105,91,88,204,117,221,84,214,223,240,175,123,71,204,58,20,209,144,225,242,12,57,49,240,202,153,
223,213,111,123,141,39,90,217,107,158,60,100,173,28,238,163,246,124,6,208,25,30,177,117,174,62,83,177,139,154,54,22,216,79,121,69,234,221,92,100,182,184,110,192,202,153,92,127,84,123,143,246,156,140,128,
244,233,167,204,136,196,221,14,186,47,213,114,136,180,14,61,179,247,151,57,9,153,79,178,144,231,188,187,96,218,217,51,0,125,22,170,29,111,42,163,144,207,73,251,155,232,212,73,243,44,107,158,223,236,189,
200,20,100,254,170,117,238,132,114,139,250,50,251,7,128,31,22,251,178,189,196,255,0,37,31,7,175,222,238,158,48,54,141,140,181,214,111,157,125,195,232,194,192,126,79,184,235,249,170,24,87,237,121,19,201,
37,70,114,131,40,223,66,202,57,122,132,190,143,81,210,179,143,218,94,210,127,194,84,127,234,155,255,0,126,87,250,143,88,199,202,174,143,78,67,153,92,89,253,96,127,216,213,203,244,155,247,230,218,63,117,
161,255,0,230,22,165,94,87,179,82,157,25,196,158,35,184,182,41,224,32,145,224,30,137,253,64,215,210,108,51,30,169,101,127,38,250,206,119,253,67,86,72,183,30,222,140,219,125,65,235,179,44,83,233,233,37,
143,111,218,5,159,217,123,30,213,95,55,169,99,191,163,227,81,89,253,59,108,188,220,223,0,75,61,15,253,24,177,241,221,250,197,103,190,225,170,135,44,251,120,182,57,124,21,169,232,67,255,211,225,177,242,
109,169,182,54,183,150,139,153,233,216,7,231,48,150,191,99,191,183,93,110,79,189,86,97,209,75,114,148,73,143,133,181,93,229,163,149,1,97,26,160,110,75,114,60,103,236,71,0,111,227,228,254,153,159,5,11,
238,155,137,29,138,170,199,195,129,240,76,231,203,137,241,50,143,186,120,107,197,3,16,18,191,6,227,242,172,101,213,219,91,139,44,172,181,236,112,228,57,167,115,93,254,114,19,174,123,222,108,121,46,123,
137,115,156,121,36,157,206,119,246,144,55,202,109,200,25,146,109,35,24,1,215,232,125,78,204,30,167,70,83,0,115,170,118,237,167,131,166,173,90,248,253,82,246,100,140,134,62,45,99,183,180,243,170,229,42,
179,109,173,42,253,89,58,242,167,195,148,1,69,173,204,96,179,117,209,217,55,1,221,103,230,229,105,207,100,55,229,121,172,252,155,247,24,79,203,154,163,65,102,30,95,213,101,149,151,110,40,149,223,182,135,
55,204,42,91,147,239,49,10,176,200,65,182,225,198,8,164,198,194,100,248,167,109,164,58,124,21,125,201,247,38,241,167,129,191,129,212,172,194,186,219,88,3,141,212,91,65,158,194,230,154,203,255,0,177,244,
212,91,147,237,249,42,59,146,220,83,134,66,22,156,64,182,13,164,242,167,140,255,0,214,42,254,184,85,119,34,98,187,245,154,127,174,212,211,37,194,15,255,212,224,91,83,11,65,245,152,217,28,16,249,31,115,
19,250,44,255,0,78,207,185,255,0,249,5,142,146,42,118,61,22,127,167,103,220,255,0,252,130,94,139,63,211,179,238,127,254,65,99,164,146,157,143,69,159,233,217,247,63,255,0,32,151,162,207,244,236,251,159,
255,0,144,88,233,37,246,169,216,244,89,254,157,159,115,255,0,242,9,122,44,255,0,78,207,185,255,0,249,5,142,146,74,118,5,44,157,47,100,252,31,255,0,144,69,174,163,58,92,207,185,255,0,249,5,132,146,116,
126,171,101,183,71,160,125,102,63,157,103,220,255,0,252,138,3,169,108,235,123,62,231,255,0,228,22,50,72,207,234,136,125,62,142,199,162,207,244,236,251,159,255,0,144,75,209,103,250,118,125,207,255,0,200,
44,116,147,62,213,238,199,162,207,244,236,251,159,255,0,144,75,209,103,250,118,125,207,255,0,200,44,116,146,83,177,232,179,253,59,62,231,255,0,228,18,244,89,254,157,159,115,255,0,242,11,29,36,190,213,
59,30,139,63,211,179,238,127,254,65,19,26,166,12,154,79,172,195,239,110,144,255,0,31,234,44,52,146,251,84,255,0,255,217,255,237,22,162,80,104,111,116,111,115,104,111,112,32,51,46,48,0,56,66,73,77,4,4,
0,0,0,0,0,15,28,1,90,0,3,27,37,71,28,2,0,0,2,0,99,0,56,66,73,77,4,37,0,0,0,0,0,16,149,50,34,91,247,43,182,177,155,10,126,10,155,74,188,184,56,66,73,77,4,58,0,0,0,0,0,229,0,0,0,16,0,0,0,1,0,0,0,0,0,11,
112,114,105,110,116,79,117,116,112,117,116,0,0,0,5,0,0,0,0,80,115,116,83,98,111,111,108,1,0,0,0,0,73,110,116,101,101,110,117,109,0,0,0,0,73,110,116,101,0,0,0,0,67,108,114,109,0,0,0,15,112,114,105,110,
116,83,105,120,116,101,101,110,66,105,116,98,111,111,108,0,0,0,0,11,112,114,105,110,116,101,114,78,97,109,101,84,69,88,84,0,0,0,1,0,0,0,0,0,15,112,114,105,110,116,80,114,111,111,102,83,101,116,117,112,
79,98,106,99,0,0,0,12,0,80,0,114,0,111,0,111,0,102,0,32,0,83,0,101,0,116,0,117,0,112,0,0,0,0,0,10,112,114,111,111,102,83,101,116,117,112,0,0,0,1,0,0,0,0,66,108,116,110,101,110,117,109,0,0,0,12,98,117,
105,108,116,105,110,80,114,111,111,102,0,0,0,9,112,114,111,111,102,67,77,89,75,0,56,66,73,77,4,59,0,0,0,0,2,45,0,0,0,16,0,0,0,1,0,0,0,0,0,18,112,114,105,110,116,79,117,116,112,117,116,79,112,116,105,111,
110,115,0,0,0,23,0,0,0,0,67,112,116,110,98,111,111,108,0,0,0,0,0,67,108,98,114,98,111,111,108,0,0,0,0,0,82,103,115,77,98,111,111,108,0,0,0,0,0,67,114,110,67,98,111,111,108,0,0,0,0,0,67,110,116,67,98,111,
111,108,0,0,0,0,0,76,98,108,115,98,111,111,108,0,0,0,0,0,78,103,116,118,98,111,111,108,0,0,0,0,0,69,109,108,68,98,111,111,108,0,0,0,0,0,73,110,116,114,98,111,111,108,0,0,0,0,0,66,99,107,103,79,98,106,
99,0,0,0,1,0,0,0,0,0,0,82,71,66,67,0,0,0,3,0,0,0,0,82,100,32,32,100,111,117,98,64,111,224,0,0,0,0,0,0,0,0,0,71,114,110,32,100,111,117,98,64,111,224,0,0,0,0,0,0,0,0,0,66,108,32,32,100,111,117,98,64,111,
224,0,0,0,0,0,0,0,0,0,66,114,100,84,85,110,116,70,35,82,108,116,0,0,0,0,0,0,0,0,0,0,0,0,66,108,100,32,85,110,116,70,35,82,108,116,0,0,0,0,0,0,0,0,0,0,0,0,82,115,108,116,85,110,116,70,35,80,120,108,64,
88,0,0,0,0,0,0,0,0,0,10,118,101,99,116,111,114,68,97,116,97,98,111,111,108,1,0,0,0,0,80,103,80,115,101,110,117,109,0,0,0,0,80,103,80,115,0,0,0,0,80,103,80,67,0,0,0,0,76,101,102,116,85,110,116,70,35,82,
108,116,0,0,0,0,0,0,0,0,0,0,0,0,84,111,112,32,85,110,116,70,35,82,108,116,0,0,0,0,0,0,0,0,0,0,0,0,83,99,108,32,85,110,116,70,35,80,114,99,64,89,0,0,0,0,0,0,0,0,0,16,99,114,111,112,87,104,101,110,80,114,
105,110,116,105,110,103,98,111,111,108,0,0,0,0,14,99,114,111,112,82,101,99,116,66,111,116,116,111,109,108,111,110,103,0,0,0,0,0,0,0,12,99,114,111,112,82,101,99,116,76,101,102,116,108,111,110,103,0,0,0,
0,0,0,0,13,99,114,111,112,82,101,99,116,82,105,103,104,116,108,111,110,103,0,0,0,0,0,0,0,11,99,114,111,112,82,101,99,116,84,111,112,108,111,110,103,0,0,0,0,0,56,66,73,77,3,237,0,0,0,0,0,16,0,96,0,0,0,
1,0,2,0,96,0,0,0,1,0,2,56,66,73,77,4,38,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,63,128,0,0,56,66,73,77,4,13,0,0,0,0,0,4,255,255,255,212,56,66,73,77,4,25,0,0,0,0,0,4,0,0,0,0,56,66,73,77,3,243,0,0,0,0,0,9,0,0,
0,0,0,0,0,0,1,0,56,66,73,77,39,16,0,0,0,0,0,10,0,1,0,0,0,0,0,0,0,2,56,66,73,77,3,245,0,0,0,0,0,72,0,47,102,102,0,1,0,108,102,102,0,6,0,0,0,0,0,1,0,47,102,102,0,1,0,161,153,154,0,6,0,0,0,0,0,1,0,50,0,0,
0,1,0,90,0,0,0,6,0,0,0,0,0,1,0,53,0,0,0,1,0,45,0,0,0,6,0,0,0,0,0,1,56,66,73,77,3,248,0,0,0,0,0,112,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,3,232,0,0,
0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,3,232,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,3,232,
0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,3,232,0,0,56,66,73,77,4,0,0,0,0,0,0,2,0,2,56,66,73,77,4,2,0,0,0,0,0,6,0,0,0,0,0,0,56,66,73,77,4,48,0,0,0,
0,0,3,1,1,1,0,56,66,73,77,4,45,0,0,0,0,0,6,0,1,0,0,0,4,56,66,73,77,4,8,0,0,0,0,0,16,0,0,0,1,0,0,2,64,0,0,2,64,0,0,0,0,56,66,73,77,4,30,0,0,0,0,0,4,0,0,0,0,56,66,73,77,4,26,0,0,0,0,3,73,0,0,0,6,0,0,0,0,
0,0,0,0,0,0,0,150,0,0,1,24,0,0,0,10,0,115,0,111,0,117,0,110,0,100,0,95,0,119,0,97,0,118,0,101,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,24,0,0,0,150,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0,1,0,0,0,0,0,0,110,117,108,108,0,0,0,2,0,0,0,6,98,111,117,110,100,115,79,98,106,99,0,0,0,1,0,0,0,0,0,0,82,99,116,49,0,0,0,4,0,0,0,0,84,111,112,32,
108,111,110,103,0,0,0,0,0,0,0,0,76,101,102,116,108,111,110,103,0,0,0,0,0,0,0,0,66,116,111,109,108,111,110,103,0,0,0,150,0,0,0,0,82,103,104,116,108,111,110,103,0,0,1,24,0,0,0,6,115,108,105,99,101,115,86,
108,76,115,0,0,0,1,79,98,106,99,0,0,0,1,0,0,0,0,0,5,115,108,105,99,101,0,0,0,18,0,0,0,7,115,108,105,99,101,73,68,108,111,110,103,0,0,0,0,0,0,0,7,103,114,111,117,112,73,68,108,111,110,103,0,0,0,0,0,0,0,
6,111,114,105,103,105,110,101,110,117,109,0,0,0,12,69,83,108,105,99,101,79,114,105,103,105,110,0,0,0,13,97,117,116,111,71,101,110,101,114,97,116,101,100,0,0,0,0,84,121,112,101,101,110,117,109,0,0,0,10,
69,83,108,105,99,101,84,121,112,101,0,0,0,0,73,109,103,32,0,0,0,6,98,111,117,110,100,115,79,98,106,99,0,0,0,1,0,0,0,0,0,0,82,99,116,49,0,0,0,4,0,0,0,0,84,111,112,32,108,111,110,103,0,0,0,0,0,0,0,0,76,
101,102,116,108,111,110,103,0,0,0,0,0,0,0,0,66,116,111,109,108,111,110,103,0,0,0,150,0,0,0,0,82,103,104,116,108,111,110,103,0,0,1,24,0,0,0,3,117,114,108,84,69,88,84,0,0,0,1,0,0,0,0,0,0,110,117,108,108,
84,69,88,84,0,0,0,1,0,0,0,0,0,0,77,115,103,101,84,69,88,84,0,0,0,1,0,0,0,0,0,6,97,108,116,84,97,103,84,69,88,84,0,0,0,1,0,0,0,0,0,14,99,101,108,108,84,101,120,116,73,115,72,84,77,76,98,111,111,108,1,0,
0,0,8,99,101,108,108,84,101,120,116,84,69,88,84,0,0,0,1,0,0,0,0,0,9,104,111,114,122,65,108,105,103,110,101,110,117,109,0,0,0,15,69,83,108,105,99,101,72,111,114,122,65,108,105,103,110,0,0,0,7,100,101,102,
97,117,108,116,0,0,0,9,118,101,114,116,65,108,105,103,110,101,110,117,109,0,0,0,15,69,83,108,105,99,101,86,101,114,116,65,108,105,103,110,0,0,0,7,100,101,102,97,117,108,116,0,0,0,11,98,103,67,111,108,
111,114,84,121,112,101,101,110,117,109,0,0,0,17,69,83,108,105,99,101,66,71,67,111,108,111,114,84,121,112,101,0,0,0,0,78,111,110,101,0,0,0,9,116,111,112,79,117,116,115,101,116,108,111,110,103,0,0,0,0,0,
0,0,10,108,101,102,116,79,117,116,115,101,116,108,111,110,103,0,0,0,0,0,0,0,12,98,111,116,116,111,109,79,117,116,115,101,116,108,111,110,103,0,0,0,0,0,0,0,11,114,105,103,104,116,79,117,116,115,101,116,
108,111,110,103,0,0,0,0,0,56,66,73,77,4,40,0,0,0,0,0,12,0,0,0,2,63,240,0,0,0,0,0,0,56,66,73,77,4,17,0,0,0,0,0,1,1,0,56,66,73,77,4,20,0,0,0,0,0,4,0,0,0,4,56,66,73,77,4,12,0,0,0,0,13,95,0,0,0,1,0,0,0,160,
0,0,0,86,0,0,1,224,0,0,161,64,0,0,13,67,0,24,0,1,255,216,255,237,0,12,65,100,111,98,101,95,67,77,0,2,255,238,0,14,65,100,111,98,101,0,100,128,0,0,0,1,255,219,0,132,0,12,8,8,8,9,8,12,9,9,12,17,11,10,11,
17,21,15,12,12,15,21,24,19,19,21,19,19,24,17,12,12,12,12,12,12,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,1,13,11,11,13,14,13,16,14,14,16,20,14,14,14,20,20,
14,14,14,14,20,17,12,12,12,12,12,17,17,12,12,12,12,12,12,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,255,192,0,17,8,0,86,0,160,3,1,34,0,2,17,1,3,17,1,255,221,
0,4,0,10,255,196,1,63,0,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0,3,0,1,2,4,5,6,7,8,9,10,11,1,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,2,3,4,5,6,7,8,9,10,11,16,0,1,4,1,3,2,4,2,5,7,6,8,5,3,12,51,1,0,2,17,3,4,33,18,49,
5,65,81,97,19,34,113,129,50,6,20,145,161,177,66,35,36,21,82,193,98,51,52,114,130,209,67,7,37,146,83,240,225,241,99,115,53,22,162,178,131,38,68,147,84,100,69,194,163,116,54,23,210,85,226,101,242,179,132,
195,211,117,227,243,70,39,148,164,133,180,149,196,212,228,244,165,181,197,213,229,245,86,102,118,134,150,166,182,198,214,230,246,55,71,87,103,119,135,151,167,183,199,215,231,247,17,0,2,2,1,2,4,4,3,4,5,
6,7,7,6,5,53,1,0,2,17,3,33,49,18,4,65,81,97,113,34,19,5,50,129,145,20,161,177,66,35,193,82,209,240,51,36,98,225,114,130,146,67,83,21,99,115,52,241,37,6,22,162,178,131,7,38,53,194,210,68,147,84,163,23,
100,69,85,54,116,101,226,242,179,132,195,211,117,227,243,70,148,164,133,180,149,196,212,228,244,165,181,197,213,229,245,86,102,118,134,150,166,182,198,214,230,246,39,55,71,87,103,119,135,151,167,183,199,
255,218,0,12,3,1,0,2,17,3,17,0,63,0,243,166,178,83,250,104,149,181,79,106,127,10,222,36,30,154,94,154,62,196,182,165,194,174,36,30,154,94,154,179,85,83,99,68,114,147,235,218,247,55,192,148,184,52,181,
113,139,166,191,166,151,166,142,234,224,193,77,181,46,21,113,33,21,73,3,197,25,152,146,81,49,234,221,115,66,211,171,27,94,52,82,226,197,197,171,22,92,220,46,91,176,227,178,174,250,75,76,21,208,191,23,
67,162,206,203,199,219,192,78,201,134,133,133,184,179,241,26,46,111,166,151,166,143,177,56,172,150,147,216,21,7,11,63,16,107,250,105,122,104,251,116,75,106,92,42,226,65,233,167,244,209,182,121,39,21,19,
172,37,194,174,36,1,131,193,23,25,129,217,21,53,194,90,94,217,7,130,37,62,196,76,102,254,179,87,245,218,151,10,184,159,255,208,225,106,110,156,34,108,149,42,155,42,222,54,62,227,37,90,142,59,107,75,32,
2,208,85,143,51,226,132,218,119,59,108,112,187,75,58,126,35,186,62,9,99,3,110,103,168,219,93,26,187,121,245,107,221,253,86,251,21,27,58,5,53,244,218,115,88,73,186,203,108,109,205,236,27,63,171,123,127,
235,87,169,14,47,151,78,180,215,143,52,61,86,226,227,227,77,204,211,178,22,78,52,94,68,114,229,181,78,62,219,90,99,134,161,228,227,77,224,199,37,72,112,250,107,197,100,121,159,95,209,200,200,199,33,195,
78,193,1,181,203,128,133,187,149,139,238,111,201,85,175,23,244,131,79,20,201,225,245,50,195,152,28,40,112,49,191,88,18,60,87,73,233,214,222,144,198,6,141,199,33,207,221,222,11,90,207,251,234,207,196,199,
219,97,62,18,181,30,223,212,216,223,131,135,205,207,31,193,79,143,24,17,30,109,76,249,76,165,187,159,233,170,121,184,210,36,14,203,160,192,232,217,89,230,207,68,181,190,155,75,206,238,241,249,163,250,
202,171,250,110,69,175,20,49,133,246,184,195,90,59,148,233,8,200,17,219,117,144,200,98,65,114,49,126,174,93,157,135,147,117,50,236,170,223,75,113,232,111,248,65,99,141,119,127,219,91,169,67,199,232,121,
150,116,220,156,198,176,122,88,197,158,166,186,254,145,222,155,118,143,228,187,233,173,220,60,220,206,146,27,117,0,11,55,189,190,225,48,11,90,207,243,155,185,108,116,67,139,246,123,169,202,33,184,247,
91,101,118,142,37,177,35,252,199,57,86,56,168,147,86,216,60,204,171,126,175,156,58,146,9,17,218,84,177,241,159,117,161,140,18,79,3,196,174,151,235,30,13,13,234,55,89,67,61,58,237,104,181,172,2,0,15,1,
241,167,181,84,250,179,141,187,169,210,79,209,109,155,157,240,103,189,223,245,9,190,214,163,177,102,251,197,192,203,176,115,186,143,72,200,233,189,78,238,159,144,90,235,113,220,3,156,201,218,101,162,193,
183,116,59,243,211,51,23,219,199,101,177,212,106,125,249,181,94,255,0,115,173,165,133,196,242,75,75,235,255,0,190,163,99,244,140,139,177,45,201,96,30,157,27,67,135,115,188,159,163,254,106,124,112,129,
187,28,185,157,3,204,58,130,208,76,120,169,97,80,251,51,41,174,182,151,61,207,16,209,228,11,191,234,66,212,200,194,125,109,123,30,210,199,182,65,105,16,71,201,87,233,47,118,62,117,119,48,195,152,31,7,
194,107,177,159,247,229,30,76,92,63,80,207,143,55,16,36,63,255,209,196,207,198,99,70,45,108,110,215,87,142,202,236,243,123,101,207,255,0,207,136,216,152,163,96,209,19,22,230,231,6,216,225,46,178,231,136,
243,118,199,237,255,0,164,187,15,216,88,118,216,218,104,138,205,117,236,36,15,164,250,230,183,255,0,159,107,86,150,51,8,209,61,156,124,210,151,202,59,185,134,173,184,254,159,238,10,143,222,194,173,53,
181,213,78,78,13,141,215,208,169,205,242,115,63,79,255,0,163,158,165,149,87,165,125,205,229,164,176,15,128,138,213,123,114,198,71,84,200,143,206,47,103,200,53,205,10,82,56,171,183,204,213,18,34,218,152,
221,54,204,171,92,218,96,109,99,159,175,131,125,209,253,164,55,116,204,135,58,183,22,64,121,33,164,240,97,109,244,145,85,120,246,220,76,57,219,106,96,241,221,171,191,234,85,129,107,108,171,17,144,52,176,
143,243,142,228,142,67,100,1,166,202,26,0,111,90,121,206,163,211,44,197,200,117,22,67,157,89,137,26,3,162,165,78,38,235,64,3,83,253,235,177,234,21,85,110,11,237,115,102,199,150,56,56,243,160,218,239,250,
165,141,141,129,152,230,187,38,170,230,186,200,4,247,212,255,0,177,24,76,74,55,45,8,211,234,146,100,44,15,228,18,179,234,248,175,1,217,22,146,219,156,224,88,211,198,200,247,59,252,226,171,100,84,27,80,
96,252,218,217,248,151,127,228,150,166,127,82,189,254,166,59,192,2,150,6,136,242,45,84,198,199,216,224,238,213,215,255,0,124,255,0,201,37,3,42,185,119,189,22,200,139,211,193,135,76,202,183,24,184,176,
192,223,91,79,195,118,168,189,63,32,213,156,235,76,77,97,228,124,117,111,241,90,93,83,31,22,186,24,234,24,26,208,90,201,3,146,201,146,179,43,162,201,202,180,52,237,104,137,254,179,196,32,12,102,12,170,
184,180,81,4,26,189,154,93,66,177,99,70,159,158,243,255,0,82,137,99,61,38,53,190,54,61,223,126,213,44,136,4,52,233,171,207,222,227,253,202,207,86,169,181,122,26,131,186,177,102,159,202,213,63,75,136,239,
106,179,94,78,134,37,56,249,76,196,203,186,176,255,0,179,86,107,112,34,65,21,251,153,255,0,159,22,70,31,69,253,159,147,151,34,61,22,218,7,246,189,140,255,0,162,245,107,11,173,213,70,35,241,159,89,46,116,
57,174,210,0,252,249,254,180,35,228,101,28,172,3,149,183,249,198,53,132,248,185,174,115,93,255,0,158,218,161,225,148,103,181,68,154,31,244,151,241,250,42,251,91,135,145,142,11,49,223,251,187,217,247,16,
255,0,253,24,180,186,87,183,22,218,199,15,58,143,234,144,84,49,89,86,69,66,167,126,109,160,31,131,219,255,0,152,45,102,99,97,226,101,10,203,182,210,92,242,210,79,104,5,186,185,62,114,0,24,214,186,159,
177,96,179,173,255,0,34,229,229,116,151,117,78,163,104,100,53,215,58,103,176,144,177,186,151,69,199,194,234,54,140,111,230,153,88,241,250,65,190,157,220,254,245,205,123,151,73,83,139,31,118,69,102,5,84,
23,79,153,30,155,127,42,192,187,51,117,101,239,247,57,245,196,159,31,80,181,71,49,96,246,140,127,99,62,9,200,17,87,172,135,230,255,0,255,210,193,232,119,17,101,16,127,155,202,169,255,0,40,115,143,254,
122,93,38,7,87,204,111,73,61,66,73,126,253,161,199,81,234,27,62,209,255,0,80,185,94,132,28,234,243,108,7,250,53,7,32,252,0,126,60,255,0,219,153,85,168,215,213,178,89,132,122,126,225,246,127,87,237,17,
26,239,219,232,243,251,187,21,216,207,107,115,178,225,226,38,186,61,94,31,80,183,43,33,198,211,36,144,227,242,125,106,159,73,200,245,122,187,65,225,246,128,127,180,118,170,157,15,168,99,83,144,231,100,
186,25,233,91,180,255,0,47,97,52,183,251,86,53,171,51,19,168,190,140,151,89,89,135,2,11,79,152,83,156,163,70,188,121,115,235,209,238,221,187,31,31,22,151,8,115,172,117,142,249,22,210,223,250,135,171,24,
94,145,109,132,188,7,226,177,183,144,124,26,28,31,255,0,86,197,207,229,253,101,103,80,234,53,218,198,122,53,6,52,6,120,31,167,111,254,10,231,42,63,88,242,91,87,89,190,170,44,154,216,237,146,211,161,27,
91,35,79,205,64,203,210,44,209,43,35,128,241,85,116,122,123,58,203,44,104,195,3,232,83,100,59,196,183,244,205,255,0,162,197,62,155,213,104,173,152,152,246,88,43,110,111,168,44,158,3,75,133,85,63,251,47,
173,235,147,193,201,46,234,120,204,6,93,107,133,64,120,155,1,168,55,254,154,135,94,204,165,189,79,236,116,145,179,9,141,196,36,112,95,87,244,135,127,236,67,173,77,153,141,240,244,37,124,48,203,235,78,
253,249,213,229,100,228,186,191,206,107,200,249,65,72,60,140,155,218,59,48,143,243,67,127,242,43,15,161,60,221,158,41,26,155,26,246,129,241,105,91,88,204,117,221,84,214,223,240,175,123,71,204,58,20,209,
144,225,242,12,57,49,240,202,153,223,213,111,123,141,39,90,217,107,158,60,100,173,28,238,163,246,124,6,208,25,30,177,117,174,62,83,177,139,154,54,22,216,79,121,69,234,221,92,100,182,184,110,192,202,153,
92,127,84,123,143,246,156,140,128,244,233,167,204,136,196,221,14,186,47,213,114,136,180,14,61,179,247,151,57,9,153,79,178,144,231,188,187,96,218,217,51,0,125,22,170,29,111,42,163,144,207,73,251,155,232,
212,73,243,44,107,158,223,236,189,200,20,100,254,170,117,238,132,114,139,250,50,251,7,128,31,22,251,178,189,196,255,0,37,31,7,175,222,238,158,48,54,141,140,181,214,111,157,125,195,232,194,192,126,79,184,
235,249,170,24,87,237,121,19,201,37,70,114,131,40,223,66,202,57,122,132,190,143,81,210,179,143,218,94,210,127,194,84,127,234,155,255,0,126,87,250,143,88,199,202,174,143,78,67,153,92,89,253,96,127,216,
213,203,244,155,247,230,218,63,117,161,255,0,230,22,165,94,87,179,82,157,25,196,158,35,184,182,41,224,32,145,224,30,137,253,64,215,210,108,51,30,169,101,127,38,250,206,119,253,67,86,72,183,30,222,140,
219,125,65,235,179,44,83,233,233,37,143,111,218,5,159,217,123,30,213,95,55,169,99,191,163,227,81,89,253,59,108,188,220,223,0,75,61,15,253,24,177,241,221,250,197,103,190,225,170,135,44,251,120,182,57,124,
21,169,232,67,255,211,225,177,242,109,169,182,54,183,150,139,153,233,216,7,231,48,150,191,99,191,183,93,110,79,189,86,97,209,75,114,148,73,143,133,181,93,229,163,149,1,97,26,160,110,75,114,60,103,236,
71,0,111,227,228,254,153,159,5,11,238,155,137,29,138,170,199,195,129,240,76,231,203,137,241,50,143,186,120,107,197,3,16,18,191,6,227,242,172,101,213,219,91,139,44,172,181,236,112,228,57,167,115,93,254,
114,19,174,123,222,108,121,46,123,137,115,156,121,36,157,206,119,246,144,55,202,109,200,25,146,109,35,24,1,215,232,125,78,204,30,167,70,83,0,115,170,118,237,167,131,166,173,90,248,253,82,246,100,140,134,
62,45,99,183,180,243,170,229,42,179,109,173,42,253,89,58,242,167,195,148,1,69,173,204,96,179,117,209,217,55,1,221,103,230,229,105,207,100,55,229,121,172,252,155,247,24,79,203,154,163,65,102,30,95,213,
101,149,151,110,40,149,223,182,135,55,204,42,91,147,239,49,10,176,200,65,182,225,198,8,164,198,194,100,248,167,109,164,58,124,21,125,201,247,38,241,167,129,191,129,212,172,194,186,219,88,3,141,212,91,
65,158,194,230,154,203,255,0,177,244,212,91,147,237,249,42,59,146,220,83,134,66,22,156,64,182,13,164,242,167,140,255,0,214,42,254,184,85,119,34,98,187,245,154,127,174,212,211,37,194,15,255,212,224,91,
83,11,65,245,152,217,28,16,249,31,115,19,250,44,255,0,78,207,185,255,0,249,5,142,146,42,118,61,22,127,167,103,220,255,0,252,130,94,139,63,211,179,238,127,254,65,99,164,146,157,143,69,159,233,217,247,63,
255,0,32,151,162,207,244,236,251,159,255,0,144,88,233,37,246,169,216,244,89,254,157,159,115,255,0,242,9,122,44,255,0,78,207,185,255,0,249,5,142,146,74,118,5,44,157,47,100,252,31,255,0,144,69,174,163,58,
92,207,185,255,0,249,5,132,146,116,126,171,101,183,71,160,125,102,63,157,103,220,255,0,252,138,3,169,108,235,123,62,231,255,0,228,22,50,72,207,234,136,125,62,142,199,162,207,244,236,251,159,255,0,144,
75,209,103,250,118,125,207,255,0,200,44,116,147,62,213,238,199,162,207,244,236,251,159,255,0,144,75,209,103,250,118,125,207,255,0,200,44,116,146,83,177,232,179,253,59,62,231,255,0,228,18,244,89,254,157,
159,115,255,0,242,11,29,36,190,213,59,30,139,63,211,179,238,127,254,65,19,26,166,12,154,79,172,195,239,110,144,255,0,31,234,44,52,146,251,84,255,0,255,217,0,56,66,73,77,4,33,0,0,0,0,0,85,0,0,0,1,1,0,0,
0,15,0,65,0,100,0,111,0,98,0,101,0,32,0,80,0,104,0,111,0,116,0,111,0,115,0,104,0,111,0,112,0,0,0,19,0,65,0,100,0,111,0,98,0,101,0,32,0,80,0,104,0,111,0,116,0,111,0,115,0,104,0,111,0,112,0,32,0,67,0,83,
0,54,0,0,0,1,0,56,66,73,77,4,6,0,0,0,0,0,7,0,4,0,0,0,1,1,0,255,225,13,57,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,0,60,63,120,112,97,99,107,101,
116,32,98,101,103,105,110,61,34,239,187,191,34,32,105,100,61,34,87,53,77,48,77,112,67,101,104,105,72,122,114,101,83,122,78,84,99,122,107,99,57,100,34,63,62,32,60,120,58,120,109,112,109,101,116,97,32,120,
109,108,110,115,58,120,61,34,97,100,111,98,101,58,110,115,58,109,101,116,97,47,34,32,120,58,120,109,112,116,107,61,34,65,100,111,98,101,32,88,77,80,32,67,111,114,101,32,53,46,51,45,99,48,49,49,32,54,54,
46,49,52,53,54,54,49,44,32,50,48,49,50,47,48,50,47,48,54,45,49,52,58,53,54,58,50,55,32,32,32,32,32,32,32,32,34,62,32,60,114,100,102,58,82,68,70,32,120,109,108,110,115,58,114,100,102,61,34,104,116,116,
112,58,47,47,119,119,119,46,119,51,46,111,114,103,47,49,57,57,57,47,48,50,47,50,50,45,114,100,102,45,115,121,110,116,97,120,45,110,115,35,34,62,32,60,114,100,102,58,68,101,115,99,114,105,112,116,105,111,
110,32,114,100,102,58,97,98,111,117,116,61,34,34,32,120,109,108,110,115,58,120,109,112,77,77,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,109,
109,47,34,32,120,109,108,110,115,58,115,116,69,118,116,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,115,84,121,112,101,47,82,101,115,111,117,114,
99,101,69,118,101,110,116,35,34,32,120,109,108,110,115,58,100,99,61,34,104,116,116,112,58,47,47,112,117,114,108,46,111,114,103,47,100,99,47,101,108,101,109,101,110,116,115,47,49,46,49,47,34,32,120,109,
108,110,115,58,112,104,111,116,111,115,104,111,112,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,112,104,111,116,111,115,104,111,112,47,49,46,48,47,34,32,120,109,108,110,
115,58,120,109,112,61,34,104,116,116,112,58,47,47,110,115,46,97,100,111,98,101,46,99,111,109,47,120,97,112,47,49,46,48,47,34,32,120,109,112,77,77,58,68,111,99,117,109,101,110,116,73,68,61,34,56,66,57,
68,66,65,51,67,68,54,50,50,55,54,50,48,49,51,66,70,70,55,66,55,56,48,65,52,66,51,65,55,34,32,120,109,112,77,77,58,73,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,50,48,56,55,57,
56,70,48,65,68,70,65,69,49,49,49,56,50,51,67,68,56,66,49,70,52,48,48,67,53,70,67,34,32,120,109,112,77,77,58,79,114,105,103,105,110,97,108,68,111,99,117,109,101,110,116,73,68,61,34,56,66,57,68,66,65,51,
67,68,54,50,50,55,54,50,48,49,51,66,70,70,55,66,55,56,48,65,52,66,51,65,55,34,32,100,99,58,102,111,114,109,97,116,61,34,105,109,97,103,101,47,106,112,101,103,34,32,112,104,111,116,111,115,104,111,112,
58,67,111,108,111,114,77,111,100,101,61,34,51,34,32,120,109,112,58,67,114,101,97,116,101,68,97,116,101,61,34,50,48,49,50,45,48,57,45,48,56,84,49,55,58,52,54,58,51,51,43,48,50,58,48,48,34,32,120,109,112,
58,77,111,100,105,102,121,68,97,116,101,61,34,50,48,49,50,45,48,57,45,48,57,84,50,48,58,52,49,58,49,55,43,48,50,58,48,48,34,32,120,109,112,58,77,101,116,97,100,97,116,97,68,97,116,101,61,34,50,48,49,50,
45,48,57,45,48,57,84,50,48,58,52,49,58,49,55,43,48,50,58,48,48,34,62,32,60,120,109,112,77,77,58,72,105,115,116,111,114,121,62,32,60,114,100,102,58,83,101,113,62,32,60,114,100,102,58,108,105,32,115,116,
69,118,116,58,97,99,116,105,111,110,61,34,115,97,118,101,100,34,32,115,116,69,118,116,58,105,110,115,116,97,110,99,101,73,68,61,34,120,109,112,46,105,105,100,58,50,48,56,55,57,56,70,48,65,68,70,65,69,
49,49,49,56,50,51,67,68,56,66,49,70,52,48,48,67,53,70,67,34,32,115,116,69,118,116,58,119,104,101,110,61,34,50,48,49,50,45,48,57,45,48,57,84,50,48,58,52,49,58,49,55,43,48,50,58,48,48,34,32,115,116,69,118,
116,58,115,111,102,116,119,97,114,101,65,103,101,110,116,61,34,65,100,111,98,101,32,80,104,111,116,111,115,104,111,112,32,67,83,54,32,40,87,105,110,100,111,119,115,41,34,32,115,116,69,118,116,58,99,104,
97,110,103,101,100,61,34,47,34,47,62,32,60,47,114,100,102,58,83,101,113,62,32,60,47,120,109,112,77,77,58,72,105,115,116,111,114,121,62,32,60,112,104,111,116,111,115,104,111,112,58,68,111,99,117,109,101,
110,116,65,110,99,101,115,116,111,114,115,62,32,60,114,100,102,58,66,97,103,62,32,60,114,100,102,58,108,105,62,56,66,57,68,66,65,51,67,68,54,50,50,55,54,50,48,49,51,66,70,70,55,66,55,56,48,65,52,66,51,
65,55,60,47,114,100,102,58,108,105,62,32,60,47,114,100,102,58,66,97,103,62,32,60,47,112,104,111,116,111,115,104,111,112,58,68,111,99,117,109,101,110,116,65,110,99,101,115,116,111,114,115,62,32,60,47,114,
100,102,58,68,101,115,99,114,105,112,116,105,111,110,62,32,60,47,114,100,102,58,82,68,70,62,32,60,47,120,58,120,109,112,109,101,116,97,62,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,60,63,120,112,97,99,107,101,116,32,101,110,100,61,34,119,34,63,62,255,238,0,14,65,100,111,98,101,0,100,0,0,0,0,1,255,219,0,132,0,6,4,4,4,5,4,6,5,5,
6,9,6,5,6,9,11,8,6,6,8,11,12,10,10,11,10,10,12,16,12,12,12,12,12,12,16,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,1,7,7,7,13,12,13,24,16,16,24,20,14,14,14,20,20,
14,14,14,14,20,17,12,12,12,12,12,17,17,12,12,12,12,12,12,17,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,255,192,0,17,8,0,150,1,24,3,1,17,0,2,17,1,3,17,1,255,221,
0,4,0,35,255,196,1,162,0,0,0,7,1,1,1,1,1,0,0,0,0,0,0,0,0,4,5,3,2,6,1,0,7,8,9,10,11,1,0,2,2,3,1,1,1,1,1,0,0,0,0,0,0,0,1,0,2,3,4,5,6,7,8,9,10,11,16,0,2,1,3,3,2,4,2,6,7,3,4,2,6,2,115,1,2,3,17,4,0,5,33,18,
49,65,81,6,19,97,34,113,129,20,50,145,161,7,21,177,66,35,193,82,209,225,51,22,98,240,36,114,130,241,37,67,52,83,146,162,178,99,115,194,53,68,39,147,163,179,54,23,84,100,116,195,210,226,8,38,131,9,10,24,
25,132,148,69,70,164,180,86,211,85,40,26,242,227,243,196,212,228,244,101,117,133,149,165,181,197,213,229,245,102,118,134,150,166,182,198,214,230,246,55,71,87,103,119,135,151,167,183,199,215,231,247,56,
72,88,104,120,136,152,168,184,200,216,232,248,41,57,73,89,105,121,137,153,169,185,201,217,233,249,42,58,74,90,106,122,138,154,170,186,202,218,234,250,17,0,2,2,1,2,3,5,5,4,5,6,4,8,3,3,109,1,0,2,17,3,4,
33,18,49,65,5,81,19,97,34,6,113,129,145,50,161,177,240,20,193,209,225,35,66,21,82,98,114,241,51,36,52,67,130,22,146,83,37,162,99,178,194,7,115,210,53,226,68,131,23,84,147,8,9,10,24,25,38,54,69,26,39,100,
116,85,55,242,163,179,195,40,41,211,227,243,132,148,164,180,196,212,228,244,101,117,133,149,165,181,197,213,229,245,70,86,102,118,134,150,166,182,198,214,230,246,71,87,103,119,135,151,167,183,199,215,
231,247,56,72,88,104,120,136,152,168,184,200,216,232,248,57,73,89,105,121,137,153,169,185,201,217,233,249,42,58,74,90,106,122,138,154,170,186,202,218,234,250,255,218,0,12,3,1,0,2,17,3,17,0,63,0,243,122,
173,113,85,65,25,195,74,223,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,119,166,113,165,
119,166,113,165,119,166,113,165,109,97,39,182,16,17,106,137,106,75,82,153,49,6,38,106,233,100,118,52,240,254,25,103,3,89,155,79,103,240,244,255,0,58,96,224,72,154,132,150,197,73,219,166,86,98,206,50,83,
244,206,64,134,110,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,174,244,206,52,173,136,78,52,171,132,64,99,74,184,
40,24,210,163,180,123,104,174,53,24,99,148,114,66,119,30,56,210,191,255,208,243,180,106,50,202,98,136,8,41,141,45,187,128,167,249,251,97,165,183,112,31,231,243,198,150,221,197,127,207,229,141,45,187,135,
244,252,113,165,183,113,20,198,150,221,196,127,159,207,26,91,109,98,168,39,252,250,87,15,10,219,92,7,240,193,75,110,226,49,165,183,113,31,231,244,99,75,110,224,49,165,183,112,31,231,244,99,75,110,224,
49,165,180,77,172,1,131,26,127,158,217,102,56,181,78,84,142,134,215,227,59,108,15,252,213,253,50,248,193,199,150,68,100,86,96,170,138,119,3,254,35,151,198,13,7,34,148,150,131,211,173,59,87,254,23,34,113,
178,142,68,37,197,170,212,138,111,95,248,216,12,162,80,114,49,205,45,100,167,95,243,219,49,164,28,144,90,224,42,113,164,219,184,143,233,130,145,110,224,63,207,232,198,150,221,199,252,254,120,105,54,238,
63,231,247,99,75,110,224,49,165,183,113,31,231,244,99,75,110,226,49,165,183,113,24,210,219,184,210,158,216,210,219,168,62,140,105,109,190,34,180,255,0,62,184,210,219,92,69,43,141,45,166,58,2,211,84,135,
231,128,168,47,255,209,243,220,107,182,93,77,118,137,227,254,127,126,26,65,46,43,250,191,128,199,133,11,184,111,254,126,56,240,173,173,225,183,209,255,0,26,226,2,109,190,59,253,63,199,30,20,91,69,118,
31,42,254,24,210,65,119,13,207,177,254,35,15,10,241,34,237,173,249,64,198,157,143,224,135,44,16,105,156,247,66,250,103,145,30,255,0,196,100,37,22,209,45,156,177,150,251,171,248,19,145,165,186,104,167,
235,254,35,26,72,46,225,250,191,129,198,150,219,226,63,207,232,198,145,109,112,255,0,63,191,17,21,180,219,76,182,172,68,159,113,255,0,16,204,204,24,220,93,68,211,56,173,62,54,167,143,241,124,202,142,55,
14,89,17,240,217,138,47,250,203,191,207,142,90,34,227,75,34,148,150,131,209,233,251,63,241,166,3,141,49,202,130,186,180,248,219,198,167,254,78,12,162,120,220,140,121,82,11,155,126,61,191,206,135,48,50,
65,217,98,157,168,4,235,254,125,198,87,77,150,238,20,31,231,218,184,210,218,244,136,181,125,135,241,25,33,20,113,44,224,104,63,207,199,34,67,43,108,169,223,252,252,49,164,2,215,30,159,231,220,227,75,110,
41,177,249,127,76,105,46,42,42,61,246,252,78,60,42,238,53,31,231,222,152,120,86,219,17,18,127,15,188,156,34,40,50,104,165,23,127,243,216,96,165,5,190,31,23,211,252,112,82,219,69,62,31,163,248,99,73,180,
199,66,95,247,39,23,211,250,241,33,65,127,255,210,224,17,71,211,252,251,15,235,153,33,162,209,97,61,191,206,167,37,76,73,104,166,223,71,240,24,162,219,244,207,46,157,255,0,137,197,120,151,199,110,72,175,
183,252,105,146,17,65,154,217,34,42,236,61,233,255,0,13,128,134,81,146,223,78,160,109,219,254,53,192,34,166,74,255,0,86,60,58,111,95,248,220,100,196,88,113,166,86,22,191,232,132,145,251,39,254,32,115,
39,22,61,156,76,217,61,73,109,196,60,101,109,169,241,83,241,25,143,146,59,185,112,150,203,173,32,44,24,211,246,79,224,141,140,34,137,202,138,140,209,113,145,133,58,31,226,50,38,59,178,140,182,91,233,159,
14,223,192,228,105,54,223,167,189,0,239,253,48,82,219,98,18,90,132,83,252,219,12,99,186,153,108,201,116,123,58,219,244,238,127,82,102,207,12,54,117,122,140,155,178,205,55,202,143,62,145,121,169,84,143,
171,201,18,5,3,99,234,52,213,235,225,195,46,228,105,193,150,84,52,118,161,120,138,111,201,118,255,0,129,204,142,26,22,212,102,164,214,193,161,255,0,99,255,0,26,100,120,89,9,161,46,172,254,38,219,246,143,
252,76,101,115,131,108,50,49,187,203,79,135,167,111,248,213,179,95,150,14,207,14,68,190,91,114,175,211,191,252,108,51,28,193,203,132,237,67,211,219,252,252,14,70,153,163,108,173,249,43,26,120,143,185,
151,45,140,90,39,42,67,205,1,86,255,0,63,124,174,113,108,132,148,202,117,255,0,62,227,34,3,43,119,167,211,252,251,156,86,219,88,121,87,229,253,48,128,166,78,244,232,195,231,255,0,27,28,120,82,36,218,66,
89,73,167,111,212,6,34,44,100,81,81,90,238,191,49,255,0,19,57,104,131,81,200,161,113,1,80,13,59,127,198,163,33,40,54,66,106,126,145,228,54,255,0,50,217,6,86,179,135,195,254,126,24,173,166,58,36,127,238,
74,50,61,255,0,94,70,76,162,119,127,255,211,224,208,174,195,252,251,12,204,1,196,37,24,163,245,255,0,22,201,128,198,219,227,240,143,151,252,106,185,26,82,85,99,128,180,157,59,254,182,35,39,24,219,9,73,
27,21,175,238,250,126,207,252,203,25,147,24,56,243,201,186,22,246,18,151,12,41,213,141,62,135,35,41,201,22,252,102,214,193,7,53,6,157,191,90,87,4,32,179,149,35,254,171,240,29,191,106,159,240,227,47,16,
113,142,68,215,79,180,255,0,66,59,126,199,252,202,57,147,138,27,56,153,167,234,73,175,237,105,35,26,126,217,255,0,137,12,197,205,13,220,236,83,217,83,78,181,38,35,183,236,159,248,131,225,195,13,152,102,
201,186,26,242,216,137,79,250,199,245,174,87,56,110,219,138,123,33,26,50,26,158,223,241,171,101,36,55,241,108,190,8,75,63,181,127,138,228,132,88,202,91,34,82,208,243,233,218,159,131,229,177,134,237,71,
38,204,183,69,182,227,111,90,119,63,169,14,108,176,195,103,77,168,158,236,247,78,149,162,242,189,213,184,216,76,229,136,255,0,140,123,127,198,231,25,67,212,225,153,110,197,204,96,178,255,0,172,63,227,
76,188,6,92,74,62,159,238,191,216,255,0,204,179,134,146,11,115,64,25,155,253,111,248,220,100,103,22,113,147,28,191,180,248,122,118,255,0,141,24,230,20,224,236,48,228,86,208,252,188,186,134,175,107,4,130,
177,203,50,43,255,0,170,210,160,63,129,204,121,65,186,89,169,31,249,139,228,118,179,243,70,176,218,92,53,211,34,149,102,71,136,86,36,138,229,90,72,247,21,1,119,162,101,28,54,219,139,83,182,234,126,80,
242,46,167,172,220,53,173,176,10,254,156,146,150,126,148,64,173,77,191,224,115,34,0,14,109,25,243,177,203,253,54,88,101,41,34,241,96,72,35,254,15,250,100,39,30,45,220,140,89,65,75,189,3,82,41,208,126,
174,57,79,3,146,36,179,133,62,117,254,45,145,164,218,99,164,233,51,93,183,20,27,176,160,251,147,45,132,26,50,229,164,223,207,158,69,188,242,158,173,13,141,204,162,103,150,8,174,11,40,162,131,33,106,166,
253,120,145,198,185,18,45,24,179,113,4,142,218,212,152,73,167,99,255,0,17,25,108,32,153,205,31,21,166,235,183,237,15,249,56,217,116,96,227,203,34,26,246,212,240,233,219,254,52,25,86,76,109,184,178,33,
164,182,42,107,239,191,252,25,202,140,27,70,68,33,80,23,222,159,241,174,83,77,224,166,158,95,181,150,109,80,44,74,88,170,187,26,127,42,85,137,63,64,198,113,217,68,168,135,255,212,225,200,128,0,127,207,
162,230,120,14,5,162,194,138,211,181,105,248,182,88,3,18,87,195,15,58,14,212,255,0,141,70,74,48,182,51,146,121,165,233,15,115,114,177,168,221,223,136,250,93,134,92,33,78,30,92,212,203,252,223,228,33,229,
253,73,172,226,102,120,150,36,33,152,212,215,209,94,93,41,251,124,178,220,59,184,147,204,196,110,180,27,235,205,82,59,59,72,140,151,51,204,34,137,6,213,119,152,168,21,52,2,167,42,207,26,115,48,102,217,
73,52,171,139,98,208,207,25,73,99,5,93,15,80,68,116,161,201,66,11,147,53,163,190,167,240,244,253,191,249,152,50,254,7,23,197,77,52,251,81,245,58,120,166,223,242,44,229,240,134,206,46,92,158,164,159,82,
180,248,218,131,246,191,227,117,204,124,144,221,204,193,145,83,78,180,62,145,219,246,79,252,65,240,225,199,179,28,217,55,66,223,90,254,248,237,251,71,254,36,185,92,241,238,219,139,38,201,124,214,131,212,
233,219,248,62,80,96,228,140,155,42,89,218,124,103,110,255,0,197,50,112,131,28,153,54,71,37,175,239,58,118,255,0,170,153,112,134,238,57,203,179,37,176,135,133,176,20,235,95,193,83,51,97,26,14,179,44,172,
178,120,71,251,139,84,238,86,102,63,75,80,127,196,48,31,169,162,247,72,149,78,219,83,226,20,250,66,229,133,60,74,97,63,119,237,79,248,211,20,218,242,135,212,63,61,255,0,224,198,20,9,37,119,214,192,175,
78,162,191,240,141,152,242,139,151,139,37,38,158,85,225,30,173,17,35,116,110,84,247,12,167,41,148,91,37,43,122,4,250,190,131,113,249,118,182,99,131,234,55,54,134,41,29,64,231,254,135,201,163,13,255,0,
60,215,225,204,79,8,218,241,169,254,93,72,182,6,123,216,212,22,85,224,121,10,237,35,196,27,191,133,114,121,32,41,174,83,162,131,243,135,229,104,120,245,141,77,42,169,3,7,182,81,184,96,75,150,251,149,134,
1,147,163,60,89,8,47,27,184,211,90,25,228,82,58,109,248,39,245,195,192,236,6,109,146,153,98,227,53,41,251,95,241,179,140,198,48,221,204,140,182,103,159,151,86,75,38,177,106,133,126,30,106,90,190,1,80,
156,202,199,7,89,170,201,73,191,230,174,163,46,184,44,53,57,104,101,18,205,108,72,0,124,49,202,197,58,127,146,217,3,138,152,233,167,76,34,222,210,176,18,7,111,248,209,114,216,65,183,46,68,194,43,58,21,
219,246,135,252,156,108,188,65,198,150,68,37,245,167,238,186,126,207,252,203,25,9,193,187,22,74,67,77,105,226,59,254,185,27,42,148,27,161,147,116,137,150,128,143,111,248,211,48,228,28,248,73,154,254,93,
73,107,107,125,170,79,50,243,63,163,110,226,136,127,151,47,238,193,250,57,28,25,7,165,168,18,100,31,255,213,226,145,198,197,1,222,148,61,189,151,54,64,58,210,81,194,63,136,237,223,254,54,124,182,152,72,
163,172,173,106,160,211,246,79,224,139,253,114,252,112,113,115,77,152,121,82,216,13,98,216,83,253,222,159,242,117,178,254,7,3,44,246,103,126,106,185,58,141,165,141,228,159,20,141,19,171,147,189,120,143,
249,165,151,14,24,56,115,157,148,175,202,246,214,240,121,170,11,217,83,152,179,50,92,145,226,98,46,195,241,25,94,167,29,183,227,201,65,71,207,186,68,67,91,184,186,134,58,67,118,5,196,95,41,97,231,252,
112,225,136,33,39,37,49,166,179,28,122,126,215,252,204,204,202,218,152,28,136,219,104,66,219,160,255,0,35,254,101,182,89,17,179,68,229,105,110,163,104,57,183,250,223,241,186,229,19,139,147,138,116,171,
167,90,143,79,167,85,255,0,141,91,37,142,12,51,100,221,9,125,104,61,110,159,181,250,217,50,185,195,118,252,115,217,47,158,208,115,233,219,248,73,148,152,55,140,155,42,216,218,124,125,63,107,248,199,146,
140,24,229,201,178,57,45,63,120,54,234,7,252,204,25,104,139,143,226,122,83,136,227,85,141,64,232,5,62,254,57,146,54,20,225,153,39,220,2,195,2,255,0,52,14,126,247,144,255,0,12,172,32,148,162,40,57,186,
175,137,95,212,163,38,182,206,60,143,228,173,55,82,114,111,84,201,18,165,74,84,138,146,188,123,83,199,48,117,89,140,78,205,152,163,196,82,125,127,203,17,216,223,73,20,103,101,115,74,248,9,5,50,252,57,
120,195,94,79,73,75,52,255,0,42,93,234,178,27,120,72,82,17,152,177,240,72,220,255,0,195,100,178,228,17,20,202,18,234,132,182,210,166,181,189,155,144,222,52,150,167,229,65,144,160,77,182,248,150,149,105,
136,233,118,65,239,27,169,255,0,145,50,229,124,46,71,22,204,235,201,215,113,219,233,115,25,118,6,68,74,252,184,159,248,215,19,142,195,137,146,91,178,249,124,195,250,86,214,29,46,6,228,26,222,72,230,79,
230,127,73,248,255,0,192,240,25,137,224,240,155,102,50,91,197,53,155,22,250,236,255,0,5,8,99,81,225,253,222,101,70,0,135,39,142,139,18,185,180,34,249,86,148,5,183,255,0,130,124,199,56,238,78,198,25,46,
47,69,252,189,180,244,164,184,186,34,158,133,180,204,15,249,70,37,69,252,88,101,206,175,60,173,67,93,182,51,104,84,165,125,27,192,223,240,98,65,255,0,26,97,156,119,92,51,73,45,108,235,110,71,249,63,241,
162,229,176,130,114,100,102,222,76,242,124,26,172,242,173,192,37,35,142,71,0,26,124,64,177,93,199,249,71,35,150,124,6,220,115,52,147,86,242,165,234,197,113,36,113,22,138,221,107,43,118,21,64,7,227,132,
207,136,211,60,121,104,36,51,217,16,104,71,237,117,249,72,127,174,25,99,217,200,132,247,98,119,113,113,103,31,228,126,180,57,173,203,26,46,219,12,182,78,244,7,104,205,225,31,180,156,105,243,144,127,76,
134,72,250,83,139,234,15,255,214,136,75,163,91,39,144,173,46,40,61,127,172,59,181,7,197,194,84,84,95,163,148,45,155,72,13,221,12,178,110,199,214,218,178,208,127,63,252,110,249,144,33,186,206,123,39,86,
22,127,185,93,191,99,245,70,185,151,138,14,191,62,86,91,229,139,50,53,104,218,159,97,203,255,0,192,187,28,184,197,196,148,246,79,228,143,158,141,5,119,17,179,1,254,202,36,56,34,41,160,203,117,250,109,
170,162,222,220,83,253,214,35,7,222,91,149,95,248,143,44,175,51,102,51,105,231,152,44,237,175,124,167,165,92,208,25,97,131,210,115,222,130,58,45,126,138,102,54,2,99,42,103,144,216,182,7,115,104,3,144,
6,220,253,191,223,153,181,1,199,19,217,96,183,101,140,124,4,14,52,169,255,0,140,103,199,18,196,148,61,221,185,109,233,251,67,110,191,182,184,200,54,198,74,150,118,114,136,57,8,201,80,187,154,108,42,140,
59,96,166,57,103,186,30,238,215,148,149,35,246,191,91,46,50,131,100,114,108,129,154,211,227,6,157,182,251,164,202,248,27,188,69,75,43,63,139,165,126,47,227,30,17,6,25,50,108,200,52,79,43,221,234,154,132,
86,208,209,76,132,14,71,160,4,184,39,108,25,114,112,70,218,225,46,45,145,55,186,4,214,87,45,4,130,173,27,176,168,239,78,31,211,37,143,39,28,109,168,250,77,35,110,160,225,44,17,211,164,29,61,200,144,255,
0,28,136,59,162,210,72,208,163,130,58,130,191,169,114,240,16,75,42,208,53,153,109,52,187,130,134,135,247,64,87,221,89,191,227,92,195,205,140,22,112,145,5,119,153,117,17,113,168,250,180,218,64,143,79,245,
138,182,28,88,232,49,227,179,186,63,201,151,81,91,199,113,57,2,162,53,64,79,249,100,47,234,202,245,48,186,103,142,124,41,29,240,71,186,188,112,180,248,100,251,204,136,60,50,216,0,166,76,94,198,211,253,
58,48,7,218,36,125,232,249,62,6,223,17,59,181,140,195,164,82,159,106,106,253,193,14,49,13,51,59,166,222,82,186,142,223,86,181,158,67,68,86,5,143,181,28,255,0,198,217,78,174,30,148,227,158,233,198,167,
229,75,59,175,50,75,240,3,28,242,114,166,212,33,189,51,183,209,92,196,132,200,139,145,45,228,194,191,50,60,173,107,23,154,218,91,72,213,96,155,131,168,77,151,226,87,38,148,247,25,61,55,169,200,241,56,
99,72,239,46,233,230,219,68,191,144,138,114,17,199,95,30,65,27,254,53,204,142,174,20,231,186,6,75,99,46,149,125,29,62,201,138,79,186,87,95,248,223,12,163,186,97,145,39,182,181,2,30,159,178,127,226,43,
153,16,139,25,228,103,126,75,152,219,72,204,13,5,81,107,254,180,212,204,108,209,232,198,50,221,55,148,64,52,109,90,23,90,188,170,20,127,177,90,229,21,114,100,50,7,157,221,104,198,105,168,171,191,61,197,
63,226,204,204,232,177,201,69,43,212,191,46,220,121,94,235,89,112,203,44,50,164,106,167,161,70,128,150,235,254,83,38,107,242,157,221,174,28,233,53,142,158,96,75,147,218,180,175,251,38,254,153,86,120,212,
92,189,46,75,152,127,255,215,37,213,237,184,89,73,166,175,75,75,88,17,135,252,88,190,153,111,198,70,205,198,39,154,153,221,34,134,196,250,162,131,246,182,255,0,131,124,205,140,90,178,100,79,172,172,100,
88,208,58,16,120,84,2,40,119,68,254,25,151,136,7,95,150,86,202,252,183,109,194,238,105,8,167,24,228,110,158,60,176,228,14,41,154,54,20,229,166,56,167,217,145,118,249,198,127,166,64,166,69,50,123,79,67,
203,47,55,71,154,225,20,124,163,102,111,214,195,49,231,62,44,141,177,20,16,86,183,50,31,47,205,1,53,88,204,76,7,206,54,79,233,150,28,117,54,190,52,170,8,68,178,208,138,213,255,0,83,140,201,50,217,174,
183,102,154,134,145,104,124,181,97,18,168,18,42,59,176,167,82,234,127,230,156,215,98,201,251,194,92,140,128,112,132,174,239,201,241,71,167,197,117,82,76,146,53,65,3,160,117,3,46,134,166,228,88,207,25,
0,20,227,64,210,109,19,64,191,137,151,226,120,192,2,159,202,11,101,25,114,19,48,217,132,122,73,44,43,84,209,229,74,202,35,38,48,244,231,77,170,10,158,217,177,132,193,46,52,110,173,34,150,218,143,211,246,
118,251,159,250,229,132,54,198,101,48,209,116,225,36,202,8,219,151,227,240,127,102,87,33,195,187,92,201,47,89,208,52,24,180,221,60,106,8,195,213,42,120,169,3,168,173,55,174,105,243,231,226,151,11,159,
135,15,8,226,99,126,103,8,215,142,107,185,36,246,240,67,153,186,97,81,167,11,41,179,105,45,224,174,170,137,224,138,41,243,86,25,144,5,150,28,197,165,16,216,220,205,34,164,72,93,152,173,2,138,147,178,120,
101,220,98,33,59,148,98,218,77,14,148,193,212,130,206,162,135,218,38,7,254,37,149,88,144,77,238,237,79,145,146,6,63,200,181,250,24,12,150,49,76,17,122,100,198,45,42,66,63,110,72,135,220,146,31,224,185,
76,199,169,178,42,82,15,222,222,158,180,168,251,231,76,181,138,91,166,219,242,189,132,211,171,15,184,171,228,164,147,36,198,250,19,21,140,107,216,200,228,125,5,6,87,13,212,161,180,192,222,170,82,189,127,
230,172,178,67,106,99,201,234,54,81,19,29,181,211,10,241,183,53,62,235,240,143,248,215,52,210,32,26,114,241,130,55,74,245,221,22,11,205,42,210,228,40,51,219,185,142,67,223,135,199,198,163,253,150,28,51,
225,155,57,122,163,105,61,220,105,109,229,239,72,108,210,61,72,255,0,81,16,127,198,217,153,13,230,226,30,73,37,140,66,65,119,29,62,220,12,64,247,71,45,255,0,26,230,68,246,44,65,73,189,2,171,198,157,7,
252,106,163,47,137,217,140,153,22,134,172,144,179,83,172,136,62,231,99,152,185,55,54,206,211,187,165,34,59,143,229,144,202,126,232,65,254,57,76,78,236,138,142,133,103,111,46,161,26,56,27,200,7,79,23,195,
154,92,49,92,98,206,232,239,63,222,91,75,105,61,157,187,47,162,214,206,206,163,187,13,215,183,135,76,194,193,18,70,238,116,164,1,20,242,251,203,37,91,57,217,70,204,210,83,253,136,255,0,155,178,205,72,
168,57,58,25,222,64,255,0,255,208,141,88,234,171,168,222,234,18,49,21,154,57,100,175,141,12,109,239,216,102,239,16,217,230,50,2,201,60,165,164,195,168,106,182,240,21,175,57,80,31,151,168,227,50,165,58,
139,132,65,37,232,218,254,135,97,123,168,9,45,66,136,221,126,3,184,20,10,138,41,255,0,3,149,233,242,16,44,184,217,163,189,5,175,229,121,116,177,121,86,229,88,194,134,29,203,200,15,127,167,36,53,28,101,
140,241,112,13,210,8,211,211,180,153,79,110,6,159,236,8,254,57,151,124,131,79,13,162,53,237,64,69,163,217,193,81,187,51,145,243,148,173,127,225,114,188,113,245,146,206,246,75,116,217,68,150,87,72,58,52,
33,190,226,185,116,185,181,213,162,180,59,37,184,190,138,42,211,148,128,87,230,227,223,33,154,117,6,112,22,203,245,195,20,28,224,67,84,138,138,1,223,236,198,202,63,86,96,224,111,204,5,45,186,187,231,163,
42,87,236,50,154,120,6,124,144,133,73,140,164,76,27,210,24,27,120,16,154,9,76,137,255,0,8,70,12,188,215,23,113,93,172,91,65,254,30,104,232,4,129,249,214,157,203,5,254,24,49,18,102,217,32,56,0,121,165,
228,32,75,240,138,236,127,83,251,230,223,138,220,48,10,38,194,59,155,119,70,104,202,6,96,203,90,138,130,80,119,249,101,115,223,100,134,95,127,230,171,203,123,120,109,1,1,61,52,39,109,234,67,31,233,152,
81,211,2,109,200,241,205,82,69,171,95,52,211,169,39,118,64,195,230,85,115,38,48,160,208,57,185,168,218,247,19,218,85,64,126,76,195,199,27,65,27,50,143,37,91,89,197,52,151,18,168,253,202,2,62,144,163,190,
96,106,137,114,244,177,29,84,188,213,105,20,113,21,10,55,119,167,252,8,29,189,178,122,105,18,26,243,80,44,75,82,90,250,20,223,225,252,125,76,216,99,46,57,10,203,19,71,162,198,212,251,114,49,31,37,138,
159,199,42,39,118,125,86,78,64,250,231,187,129,247,200,27,248,101,131,154,10,142,145,26,181,220,3,252,165,223,232,99,140,206,200,2,202,113,230,155,19,106,176,196,194,134,140,196,31,119,20,252,6,83,167,
149,150,204,130,131,29,180,186,88,100,82,78,195,183,252,22,100,240,219,87,74,103,182,30,115,211,6,130,214,178,73,75,128,194,139,78,195,137,205,102,77,41,57,28,177,168,168,82,150,155,230,40,174,154,238,
215,253,249,31,36,30,44,140,205,250,131,99,60,59,219,24,202,163,73,102,191,40,22,22,203,252,200,205,79,153,3,254,53,204,140,35,118,169,114,75,52,41,20,234,11,19,127,187,67,160,235,213,131,129,223,229,
151,102,228,198,2,197,167,94,91,208,109,47,111,74,76,161,163,10,198,157,43,251,177,79,184,230,62,108,220,48,108,193,14,51,72,159,209,177,90,169,65,176,245,64,252,91,250,228,6,75,141,175,14,233,142,175,
111,2,71,107,196,212,203,25,99,254,206,62,63,241,174,87,134,86,91,38,54,73,180,40,228,253,34,206,189,33,15,35,127,177,171,126,186,101,249,206,205,56,133,150,39,123,168,188,151,151,81,177,36,152,100,241,
237,9,62,57,46,16,3,145,8,165,183,151,201,250,55,142,213,115,115,248,113,25,78,172,250,28,190,207,135,239,67,255,209,231,94,79,158,154,146,161,59,75,20,177,211,221,161,20,252,115,113,143,155,161,204,30,
151,249,101,170,67,111,119,127,123,35,83,234,86,178,76,135,252,178,238,137,255,0,12,227,45,153,226,112,39,22,111,162,106,176,92,38,152,57,84,58,240,175,143,30,36,229,134,59,56,114,143,170,211,221,87,204,
54,146,105,81,200,242,39,174,242,17,32,29,194,22,81,183,181,70,83,135,17,18,101,155,45,138,96,239,121,20,176,78,83,167,166,167,238,43,253,115,102,35,179,132,146,121,178,240,169,181,138,187,44,113,17,242,
103,44,63,226,88,199,98,221,140,90,255,0,44,78,101,87,65,191,56,28,125,209,115,253,106,48,228,52,88,202,44,155,202,138,127,74,43,214,139,23,57,24,251,70,121,255,0,198,185,70,163,232,70,63,169,211,234,
18,78,183,44,237,86,162,154,253,20,195,24,177,145,178,138,18,187,90,205,31,94,49,194,192,124,157,15,252,109,145,145,169,50,28,211,45,56,132,143,78,13,182,220,201,246,37,199,252,69,114,169,74,237,148,70,
232,253,114,53,225,61,176,32,148,136,53,61,195,171,127,198,249,70,25,117,110,203,17,76,46,202,214,9,175,149,24,114,175,111,162,76,206,201,35,194,227,194,44,247,81,179,211,110,180,245,116,79,142,201,150,
222,77,169,66,41,252,120,230,183,30,67,25,57,153,113,131,13,185,176,159,53,192,137,168,21,94,138,21,64,255,0,84,48,254,25,179,194,108,56,68,84,64,74,103,94,83,90,173,119,116,69,31,50,21,127,94,95,209,
136,234,208,184,255,0,115,70,74,237,235,87,238,145,142,32,41,228,200,244,139,225,108,151,74,90,148,154,52,35,233,241,255,0,98,115,23,36,44,182,9,163,60,215,121,110,246,150,133,88,114,150,32,231,220,178,
101,90,104,27,162,203,80,65,75,173,116,181,189,104,19,249,152,128,126,111,151,207,39,8,182,168,198,211,95,52,233,54,150,54,80,89,199,214,21,163,19,220,186,146,73,251,179,27,77,144,147,109,249,224,35,179,
18,213,89,99,75,134,241,149,40,62,117,57,176,128,234,227,214,244,145,218,107,95,86,158,57,43,178,30,159,37,124,150,72,220,105,178,49,163,108,135,205,62,104,182,213,110,86,72,9,49,241,94,162,155,209,107,
215,41,211,97,225,92,135,139,155,25,105,133,1,235,211,254,54,57,151,109,96,40,71,119,73,91,127,10,255,0,194,100,120,153,136,39,126,76,189,141,252,207,103,27,183,195,43,240,106,159,231,18,175,127,245,179,
3,86,105,200,132,58,247,178,127,58,173,188,23,63,85,71,218,4,8,7,201,87,250,227,164,36,181,102,135,12,182,98,22,55,235,22,183,103,190,222,172,96,253,50,53,115,43,46,236,113,134,105,229,203,158,18,202,
192,255,0,118,41,247,112,204,60,195,100,226,53,52,127,154,185,90,132,35,246,229,44,62,147,76,26,122,59,46,88,211,25,139,95,186,184,184,182,73,159,146,167,4,81,183,64,7,252,213,153,67,8,142,237,60,211,
173,38,230,43,125,38,250,229,186,177,16,131,254,179,18,127,226,57,137,148,92,128,114,113,138,15,53,142,227,214,215,99,136,31,239,131,199,244,188,5,114,220,135,122,111,132,118,180,171,81,145,208,91,196,
118,168,185,36,123,250,161,127,227,92,197,212,74,226,236,116,3,214,255,0,255,210,229,94,91,184,17,234,246,76,78,222,170,3,242,37,7,241,205,180,36,233,242,69,148,233,87,79,109,163,234,174,166,140,242,219,
219,252,213,165,158,66,63,228,144,203,1,167,14,112,102,254,77,184,145,244,171,91,174,171,104,183,69,207,135,27,104,157,127,28,190,50,112,243,65,33,184,213,110,77,203,130,228,142,116,235,255,0,22,54,100,
192,128,209,225,166,26,45,219,73,12,224,154,143,171,215,238,84,63,195,45,37,162,80,75,188,229,118,70,164,35,255,0,125,172,41,242,160,81,148,206,78,86,12,123,38,94,64,127,87,83,181,140,244,149,125,63,248,
56,74,255,0,198,216,202,87,27,99,154,12,231,76,130,91,27,29,70,225,135,18,160,194,15,188,146,133,63,135,44,160,207,139,103,30,35,116,150,198,67,36,83,215,246,162,7,238,166,100,128,215,33,69,147,104,102,
214,125,100,218,74,69,38,140,197,191,98,2,211,241,92,197,204,118,182,236,49,178,165,175,94,46,155,116,45,131,134,123,84,69,168,238,68,100,159,227,146,195,234,133,163,40,225,41,69,167,155,100,212,60,192,
33,150,148,184,18,65,65,255,0,22,40,69,254,25,41,99,17,1,144,6,65,9,229,77,65,36,243,13,191,170,105,20,127,190,127,245,99,89,92,255,0,196,112,101,145,49,103,28,118,200,188,161,230,43,75,253,110,123,57,
228,253,221,209,149,153,107,64,88,112,122,230,54,72,122,109,178,22,14,252,152,175,153,60,193,21,206,163,33,13,200,18,127,31,83,51,112,236,26,12,44,149,241,56,150,125,53,250,134,3,240,144,101,252,195,69,
82,93,235,147,120,90,155,147,90,251,146,199,39,209,105,51,212,110,154,47,173,133,52,229,114,140,7,181,9,254,57,8,110,81,194,145,141,74,229,209,67,185,96,169,69,4,157,128,143,166,249,103,8,6,211,40,219,
59,242,173,211,22,130,70,21,17,188,132,252,148,163,102,38,113,66,155,32,104,164,186,247,153,46,46,165,145,228,53,7,254,104,111,19,147,197,136,8,162,87,41,218,81,174,93,159,170,212,159,182,241,159,248,
69,63,241,182,88,15,68,194,22,88,140,183,117,166,255,0,231,193,242,39,37,23,40,99,160,154,89,79,206,42,245,161,223,239,92,186,18,221,198,203,10,221,74,226,239,137,167,249,244,147,4,164,184,225,104,21,
187,253,227,239,219,245,112,25,87,19,145,225,210,1,53,171,155,61,86,41,224,126,50,70,192,163,120,16,100,204,105,206,203,153,28,94,134,71,39,153,47,245,39,146,226,238,79,82,87,21,102,59,87,224,76,201,199,
64,56,57,49,209,180,189,181,2,154,148,45,93,195,131,255,0,14,248,39,38,113,199,179,55,178,214,4,11,125,40,52,224,65,251,194,228,72,176,227,17,69,48,243,47,156,237,117,40,173,150,35,186,34,171,246,248,
131,48,52,200,96,193,194,179,245,49,84,212,66,207,27,3,176,32,253,200,41,153,19,178,140,120,211,221,91,82,107,93,11,210,173,12,183,178,131,242,136,133,223,254,13,178,141,140,173,178,24,247,167,156,195,
171,172,58,180,87,21,254,228,137,63,224,99,175,240,204,76,164,243,118,88,241,250,105,149,126,105,91,233,150,94,109,75,91,10,136,141,187,74,69,65,248,166,144,201,181,59,124,89,143,144,220,92,157,8,245,
63,255,211,227,26,101,199,167,113,12,131,246,25,88,127,177,42,127,134,108,162,109,214,204,108,206,53,94,54,122,117,210,83,105,53,73,148,127,171,7,48,63,228,246,93,116,224,213,148,239,201,222,115,211,172,
60,145,175,233,243,72,171,119,63,160,109,16,253,166,4,5,147,143,201,105,203,0,220,176,205,139,118,56,117,33,45,195,53,118,47,95,190,70,57,153,9,181,28,118,202,124,153,4,218,133,216,180,132,23,150,226,
9,21,84,119,38,10,140,178,115,161,110,38,72,210,77,231,249,253,63,49,94,41,59,45,196,131,232,89,136,25,68,229,98,220,189,60,44,35,60,149,173,69,105,115,109,59,53,12,84,53,255,0,86,60,38,117,22,188,184,
247,123,7,157,174,109,116,221,33,184,72,8,191,157,110,16,127,146,236,166,159,137,202,176,115,113,165,29,216,118,135,49,185,141,214,61,201,129,199,221,25,111,225,153,182,209,40,81,221,32,243,15,152,239,
116,189,122,105,109,164,41,45,189,193,40,125,214,85,167,234,202,231,43,20,229,99,197,124,144,18,249,175,80,213,110,102,188,186,122,203,48,44,192,116,221,31,182,89,138,128,70,92,52,90,209,245,51,22,189,
107,51,54,201,112,140,126,66,88,242,51,32,201,156,113,236,202,236,108,13,173,159,152,181,71,110,43,103,3,219,199,255,0,25,37,245,19,254,35,152,242,159,169,148,96,243,200,117,107,136,167,231,20,133,28,
54,204,14,251,250,121,100,39,187,108,241,182,151,238,101,4,177,36,142,191,242,48,229,188,77,71,22,207,64,208,228,50,91,88,203,212,32,155,254,17,85,242,235,183,2,113,162,150,9,15,214,126,145,250,220,100,
250,34,147,61,113,200,10,253,165,244,154,191,36,67,211,253,145,200,67,154,2,65,20,131,143,183,19,255,0,16,203,137,77,61,35,202,210,219,166,129,168,78,204,3,198,220,87,254,122,18,191,195,53,249,201,227,
76,67,207,245,75,196,61,15,137,255,0,133,108,201,18,160,152,67,117,190,100,145,147,76,179,114,41,234,81,129,255,0,87,210,95,225,149,248,142,70,56,110,194,37,188,167,209,255,0,52,182,84,102,231,120,123,
39,122,93,223,238,91,127,243,170,229,240,155,135,155,30,232,107,155,191,139,175,249,210,76,18,147,60,120,210,245,188,253,227,239,181,15,252,105,148,25,185,62,26,81,113,115,254,152,26,189,27,254,54,124,
198,148,247,115,33,143,210,159,88,93,254,236,138,254,207,235,84,204,204,83,217,215,230,130,30,234,243,253,45,55,253,161,255,0,39,31,43,156,183,103,28,94,150,91,53,201,93,62,241,171,246,253,31,248,104,
148,229,208,147,137,56,122,146,248,174,247,90,158,140,63,25,14,93,28,140,101,141,175,173,13,141,123,116,255,0,96,185,86,73,178,140,25,39,230,15,171,100,44,224,113,196,184,123,141,251,137,103,102,7,175,
128,25,71,27,60,120,247,121,28,247,76,89,136,39,161,255,0,147,121,139,146,78,227,28,54,76,45,53,27,171,173,77,90,230,103,153,194,149,12,236,88,208,26,1,189,118,25,78,105,122,91,112,194,164,255,0,255,212,
225,246,108,57,1,211,111,214,23,51,160,93,126,65,179,210,255,0,51,45,225,178,143,74,72,164,18,11,216,63,73,158,63,178,111,26,180,63,46,25,121,147,133,134,54,94,124,39,34,134,189,191,227,85,200,9,209,115,
56,17,176,93,209,206,255,0,181,95,248,115,151,66,123,180,206,22,203,188,145,230,228,208,181,155,77,66,85,50,71,6,238,131,169,30,144,7,245,229,196,216,167,7,46,22,59,230,157,93,175,181,73,167,255,0,126,
74,205,247,200,114,156,178,161,78,94,155,21,33,44,175,157,35,4,53,8,95,249,151,140,39,178,115,98,4,178,75,239,54,106,119,214,214,208,220,204,206,182,170,35,140,146,79,194,178,10,117,246,219,50,4,133,56,
99,5,22,97,249,99,230,43,75,77,82,210,75,199,85,130,148,118,115,240,128,98,97,189,114,103,213,26,112,243,99,245,110,194,252,223,171,199,119,170,221,204,134,170,243,51,2,61,221,78,99,241,112,236,231,225,
197,220,129,211,110,199,165,215,246,15,252,65,242,236,82,182,57,177,110,168,154,128,75,197,106,244,144,26,252,157,50,169,201,148,49,108,244,79,205,45,110,45,39,64,178,210,237,156,51,107,53,213,46,8,254,
73,21,132,107,248,101,70,91,181,233,176,146,94,75,5,233,105,14,253,235,255,0,16,254,152,194,123,185,211,197,65,25,21,207,239,7,203,175,207,212,203,132,238,77,18,199,179,214,188,159,11,77,229,151,185,2,
171,7,174,9,240,50,195,8,25,147,25,110,234,51,199,116,168,133,19,144,199,246,183,62,220,159,50,122,53,0,200,60,207,105,233,232,250,69,203,17,254,144,132,245,254,65,10,159,213,148,98,201,186,120,88,89,
146,136,119,253,147,255,0,16,204,160,118,71,10,50,61,98,242,8,165,183,142,66,33,145,129,116,241,226,251,126,179,144,144,22,144,24,245,238,164,64,171,26,237,255,0,26,54,99,206,78,94,28,104,239,51,249,146,
222,243,70,210,109,227,97,234,91,71,34,204,7,102,51,131,219,219,49,204,233,200,199,139,212,193,229,187,21,235,219,248,54,82,102,231,140,91,39,90,93,216,244,155,127,243,228,153,149,142,110,30,124,123,161,
46,110,254,47,243,255,0,47,35,60,140,241,227,64,173,215,198,251,246,255,0,154,51,31,141,201,240,208,82,75,89,43,238,127,91,229,6,91,183,136,236,153,216,93,252,13,191,236,254,160,185,149,9,236,225,230,
198,161,117,116,77,210,247,248,191,227,118,57,84,229,187,108,113,250,89,190,165,35,39,151,34,156,236,46,86,22,83,227,194,213,3,126,57,124,38,235,204,61,73,36,87,96,50,130,127,104,127,201,198,203,132,211,
40,40,92,106,38,53,4,120,15,248,128,241,202,231,54,204,120,147,47,56,249,204,235,151,86,211,0,84,65,111,12,4,30,181,136,208,157,188,78,82,100,203,22,158,152,75,63,37,63,47,248,214,153,142,100,236,64,164,
195,73,127,247,34,159,38,253,121,94,67,233,103,140,122,159,255,213,224,208,200,69,40,123,127,1,153,98,78,41,138,115,169,235,215,250,159,213,69,219,134,250,156,9,107,13,63,223,113,22,226,15,191,197,150,
113,53,240,32,12,159,8,249,31,248,138,140,128,44,169,122,204,67,212,30,255,0,241,177,203,1,65,138,42,43,162,19,253,143,252,104,50,209,145,162,88,247,81,185,159,148,238,122,252,103,254,38,78,83,146,86,
219,8,169,199,55,16,55,237,255,0,26,83,17,58,76,163,104,223,173,252,29,123,255,0,198,227,46,241,45,167,195,76,236,46,255,0,208,206,255,0,179,255,0,50,206,100,226,150,206,38,92,126,164,162,250,231,148,
172,63,203,255,0,141,151,49,178,203,119,55,12,21,52,251,170,33,21,220,41,255,0,136,54,75,22,77,152,102,133,168,92,93,55,174,204,167,112,196,215,228,87,42,156,247,108,134,63,74,35,87,243,14,161,171,52,
13,120,252,154,214,218,59,88,169,181,35,137,88,40,252,114,174,38,113,199,72,4,155,137,175,191,252,211,146,18,83,21,120,174,184,200,13,127,207,226,203,35,147,212,194,88,246,122,215,146,124,233,109,103,
228,237,83,79,145,169,60,205,19,91,143,26,113,13,250,243,51,28,120,141,186,92,248,170,73,96,213,75,200,212,52,167,74,252,223,51,1,218,156,73,99,76,175,252,201,113,125,167,233,246,110,160,11,46,72,173,
94,161,202,54,8,198,183,81,26,73,253,95,221,87,252,159,249,150,114,96,175,2,149,197,208,12,219,254,215,252,110,48,78,77,144,198,198,175,174,234,135,126,223,241,171,102,22,73,187,76,88,210,217,238,170,
199,231,255,0,27,41,204,89,77,203,132,16,38,74,141,207,111,224,115,28,203,118,240,19,93,54,234,136,194,189,9,255,0,137,46,101,194,123,56,121,160,133,184,186,36,255,0,159,249,95,215,43,201,54,220,80,66,
250,189,125,255,0,230,220,171,137,191,133,194,94,155,247,254,45,130,215,133,86,222,227,136,59,246,254,11,147,140,152,74,13,52,255,0,189,175,98,223,241,177,200,202,91,168,131,49,214,124,217,107,119,228,
175,47,233,177,176,250,197,140,119,43,112,0,223,226,112,83,145,255,0,87,46,140,197,56,131,7,172,148,129,46,193,117,53,238,63,226,103,45,25,18,113,161,111,46,190,10,3,219,254,52,25,84,242,55,98,198,135,
107,142,76,5,123,255,0,198,217,65,155,96,138,151,63,135,175,111,248,215,3,52,195,71,146,186,148,126,224,254,188,132,249,39,24,221,255,214,243,244,110,105,254,126,3,50,1,104,164,82,183,249,253,39,37,104,
33,197,170,62,143,212,6,5,225,111,159,197,244,255,0,19,134,214,155,89,136,3,126,223,173,70,30,36,74,13,25,9,99,238,127,142,3,36,136,181,207,111,162,159,134,37,64,95,235,26,83,223,254,54,195,197,72,225,
76,108,174,105,106,195,252,147,255,0,16,57,145,142,123,56,185,33,234,75,230,155,148,140,125,235,255,0,12,50,137,203,119,38,17,93,111,55,18,71,136,63,241,18,49,140,233,18,142,202,114,57,46,199,220,254,
177,128,201,148,70,203,121,117,249,127,3,130,211,78,229,254,127,118,60,73,166,195,208,237,254,127,107,8,146,8,217,144,233,55,68,65,215,199,254,52,204,236,51,117,154,140,105,156,55,103,212,63,63,226,249,
148,38,226,156,91,38,17,93,15,135,127,218,95,248,215,45,19,183,24,195,117,39,186,253,215,95,217,255,0,141,48,25,178,140,16,119,119,127,19,80,247,63,241,49,149,79,35,124,49,177,187,203,175,135,252,252,
14,96,100,155,179,197,4,19,205,201,143,133,127,227,97,152,230,78,76,96,178,187,15,243,236,112,90,105,19,107,57,80,71,183,235,43,150,70,109,114,141,168,73,41,99,254,126,249,25,22,113,131,69,250,255,0,159,
113,145,180,211,92,142,223,143,222,112,241,47,11,97,232,63,207,219,1,146,56,93,207,112,125,235,248,156,22,146,28,37,33,104,62,95,128,201,2,166,42,201,117,66,42,122,31,248,216,156,34,108,37,141,100,178,
150,249,1,255,0,26,140,6,73,17,165,156,207,45,188,127,227,108,139,42,107,159,195,254,125,134,27,69,38,26,35,31,210,113,125,63,175,4,142,204,162,55,127,255,215,243,212,109,183,79,243,160,203,45,133,34,
57,127,159,223,132,73,20,238,91,127,159,128,195,107,77,243,223,233,254,56,218,211,92,191,87,240,197,14,231,185,167,143,241,195,105,167,114,216,96,181,167,114,223,233,254,35,30,37,87,134,114,35,97,236,
127,21,57,56,201,174,80,221,64,177,228,125,206,68,150,202,217,220,250,111,219,250,224,180,55,207,245,255,0,17,138,211,92,255,0,207,232,56,166,157,203,252,254,236,54,180,209,127,243,251,241,181,9,150,157,
115,198,50,43,210,167,254,35,253,50,252,82,113,115,66,211,24,110,207,50,43,189,127,139,255,0,92,202,142,71,26,88,209,240,222,125,157,251,143,199,142,92,38,227,75,26,148,151,103,210,255,0,99,255,0,26,28,
18,155,40,227,65,220,222,124,71,126,231,254,38,50,137,205,200,199,141,35,154,114,223,135,225,92,193,148,156,248,65,76,49,175,203,250,140,141,179,167,114,52,31,231,227,133,87,44,132,87,220,127,76,68,145,
75,121,109,254,126,248,45,46,229,215,252,252,49,180,55,207,252,254,252,85,220,255,0,207,238,197,105,220,197,127,207,196,226,173,115,219,111,15,233,141,171,139,244,255,0,62,231,27,77,59,150,223,231,225,
134,214,155,13,191,211,252,112,113,43,92,182,251,191,86,60,75,73,142,132,224,234,145,83,196,211,239,196,149,1,255,208,243,202,10,12,154,21,57,98,138,119,44,54,180,215,45,241,226,90,111,150,43,78,229,190,
54,180,215,35,76,11,77,242,250,113,90,112,114,54,195,196,180,238,91,227,106,3,85,197,52,223,44,109,20,224,216,241,45,59,150,54,180,226,199,13,170,180,18,149,174,74,50,97,56,218,42,27,159,140,239,223,248,
156,182,51,105,148,17,145,93,30,35,126,132,127,198,185,112,200,209,44,106,114,93,30,52,246,255,0,141,72,192,102,202,56,208,179,220,84,147,254,127,107,41,156,219,225,4,15,46,249,65,46,64,14,229,134,209,
77,114,193,107,77,243,192,154,107,150,27,69,59,151,227,141,173,55,203,2,211,185,98,180,215,44,54,180,223,44,109,105,220,177,181,167,114,198,214,157,207,122,251,215,2,211,92,177,74,99,229,246,255,0,114,
176,252,241,37,67,255,209,224,214,246,186,123,196,26,107,193,27,158,169,193,205,62,144,184,85,83,234,122,71,252,183,143,249,23,39,252,211,138,183,245,61,39,254,91,199,252,139,147,254,105,192,174,250,158,
147,255,0,45,227,254,69,201,255,0,52,226,173,125,79,72,255,0,150,241,255,0,34,228,255,0,154,112,171,190,167,164,127,203,120,255,0,145,114,127,205,56,171,190,167,164,127,203,120,255,0,145,114,127,205,56,
171,190,167,164,127,203,120,255,0,145,114,127,205,56,171,127,83,210,127,229,188,127,200,185,63,230,156,10,239,169,233,63,242,222,63,228,92,159,243,78,42,239,169,233,63,242,222,63,228,92,159,243,78,42,
215,212,244,143,249,111,31,242,46,79,249,167,21,119,212,244,143,249,111,31,242,46,79,249,167,10,183,245,61,39,254,174,3,254,69,201,255,0,52,224,86,254,167,165,127,203,120,255,0,145,114,127,205,56,171,
133,158,149,93,175,197,127,227,28,159,243,78,73,87,199,103,166,87,107,250,255,0,207,57,63,230,156,144,182,18,164,74,90,105,251,127,166,248,87,224,127,111,242,114,193,109,100,5,143,105,167,113,31,233,219,
111,251,15,225,254,174,59,164,82,132,150,122,101,126,43,241,255,0,34,228,241,255,0,87,42,149,182,5,159,83,210,127,229,188,127,200,185,63,230,156,131,39,125,79,73,255,0,150,241,255,0,34,228,255,0,154,113,
87,125,79,73,255,0,150,241,255,0,34,228,255,0,154,113,87,125,79,73,255,0,150,241,255,0,34,228,255,0,154,113,87,125,79,73,255,0,150,241,255,0,34,228,255,0,154,113,86,190,167,164,127,203,120,255,0,145,114,
127,205,56,85,223,83,210,63,229,188,127,200,185,63,230,156,85,223,83,210,63,229,188,127,200,185,63,230,156,85,191,169,233,63,242,222,63,228,92,159,243,78,5,119,212,244,159,249,111,31,242,46,79,249,167,
21,107,234,122,71,252,183,143,249,23,39,252,211,133,93,245,61,35,254,91,199,252,139,147,254,105,197,91,250,158,147,255,0,45,227,254,69,201,255,0,52,224,87,125,79,73,255,0,150,241,255,0,34,228,255,0,154,
113,84,118,135,107,165,174,165,17,75,222,108,14,203,193,197,126,245,197,95,255,217,0,0};

const char* MainGUI::sound_wave_jpg = (const char*) resource_MainGUI_sound_wave_jpg;
const int MainGUI::sound_wave_jpgSize = 23973;
