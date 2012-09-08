/*
 ==============================================================================
 
 JUCE library : Starting point code, v1.26
 Copyright 2005 by Julian Storer. [edited by haydxn, 3rd April 2007, MR 09/2010]
 
 ------------------------------------------------------------------------------
 
 MainComponent.h :
 
 This file defines the behaviour of the application. The main part of the
 program that the user interacts with IS this MainComponent object. It is
 placed within the MainAppWindow instance, and so exists at whatever size
 the window provides in its content area.
 
 All of the widgets and controls that your main program window will display
 will be on this component (either directly or somewhere down the children
 hierarchy).
 
 ------------------------------------------------------------------------------
 
 Please feel free to do whatever you like with this code, bearing in mind that
 it's not guaranteed to be bug-free!
 
 ==============================================================================
 */
#ifndef _MAINCOMPONENT_H_
#define _MAINCOMPONENT_H_


/*
 Using <juce/juce.h> here assumes the juce source tree is accessible

 In Xcode add the directory containing 'juce' as a source tree named JUCE_SOURCE
 */
#include <../JuceLibraryCode/JuceHeader.h>
#include <iostream>

class MainComponent  :	public Component,
						public Button::Listener,
						public Slider::Listener,
						public Label::Listener
						
	// Here we specify any base classes that
	// give this type predefined characteristics.
	// Naturally, this is a Component, but we could
	// also inherit other qualities. For example, if
	// we want to respond to button presses, we can
	// inherit 'ButtonListener', by changing it thus:
	// e.g.
	// public Component,
	// public ButtonListener
	
	// (Notice that they're separated by a comma, and nothing comes after the
	//  final one in the list - i.e. no semicolon, because the next character
	//  must be the '{' denoting the start of the class body).
	
	// We can inherit many different classes from Juce (or classes we make
	// ourselves), but be aware that some base classes require you to define
	// some function bodies before it will allow your app to compile. These
	// functions are called 'pure virtual' functions - an example would be
	// 'buttonClicked' in ButtonListener. Some base classes will provide many
	// other virtual functions - not just pure virtual ones - which you can
	// define if you choose, but you do not have to do so.
	
	{
	private:
		//==============================================================================
		
		// Here are some members that are useful to have in any application...
		
		TooltipWindow tooltipWindow;   // To add tooltips to an application, you
		// just need to create one of these and leave it
		// there to do its work.
		
		// Your app will obviously have some kind of member variables, and so this
		// is the place you can declare them. For example, if you wanted to have a
		// widget or some component you've made, you'd have a pointer for it here;
		// you'd then instantiate the object in the constructor, and use the pointer
		// to access it elsewhere (e.g. to position it, update it, or respond to it).
		
		// e.g.
		// TextButton* myButton;

		// custom components
		TextButton* button1;
		TextButton* button2;
		TextButton* button3;
		Slider* slider;
		Label* label;

		String paintText;
		
	public:
		//==============================================================================
		MainComponent ()
		{
			// This is where the main component is created, so we initialise and
			// configure it according to our needs.
			
			// One thing that covers is creating any widgets and components we want to
			// display. Also, if any widgets will need responding to, we must hook them up
			// to their listeners here too (and it's likely that this class itself will be
			// the listener in question, providing we've inherited the appropriate class!)
			
			// Create and add the rest of your components here!
			// e.g.
			//myButton = new TextButton (T("my button"), T("Click me!"));
			//addAndMakeVisible (myButton);

			paintText = "Text here";
			
			// instantiate components
			button1 = new TextButton("Add 1");
			button2 = new TextButton("Remove 2");
			button3 = new TextButton("Refresh");
			slider = new Slider("Slider");
			label = new Label("Label", "text here...");

			// add to the GUI
			addAndMakeVisible(button1);
			addAndMakeVisible(button2);
			addAndMakeVisible(button3);
			addAndMakeVisible(slider);
			addAndMakeVisible(label);

			// set bounds
			label->setBounds(10, 10, 280, 20);
			slider->setBounds (20, 40, 260, 20);
			button1->setBounds (20, 70, 260, 20);
			button2->setBounds (20, 100, 260, 20);
			button3->setBounds (20, 130, 260, 20);

			// registering listeners
			button1->addListener (this);
			button2->addListener (this);
			button3->addListener (this);
			slider->addListener (this);
			label->addListener (this);

			button3->setClickingTogglesState(true);

			// custom calls
			slider->setValue(2);
			
		}
		
		~MainComponent ()
		{
			// Be sure to destroy any objects you've created using 'new' here. If your objects
			// are on the stack (i.e. they were created without pointers or the 'new' operator,
			// then they die automatically. If you've created them
			// manually on the heap (for example, if you've got a pointer and you've created a new
			// object for it) then it must be deleted.
			
			// However, juce has a nice neat function that will destroy all Components that have
			// been added to a Component...
			
			deleteAllChildren();   // This will remove all the contained components, and delete
			// the objects for you.
		}
		
		//==============================================================================
		void resized ()
		{
			// This is called whenever this component's size changes. We could respond
			// to this in a number of ways, but the most obvious thing to do is reposition
			// all our widgets, using their 'setBounds()' function.
			// It's nice to position them relative to the size of this Component. That means
			// making use of the 'getWidth()' and 'getHeight()' functions to determine where
			// to put them and how big they should be.
		}
		
		void paint (Graphics& g)
		{
			// This does any drawing required on this Component's face. You can simply
			// call functions on the provided Graphics object - although you may want to
			// make use of 'getWidth()' and 'getHeight()' (members of this Component) to
			// make sure you're drawing in the right place!

			//g.drawFittedText(PROJECT_NAME_IDENTIFIER, 0, 0, getWidth(), getHeight(), Justification::centred, 0xFFFFF);
			
			// size
			int width  = this->getWidth();
			int height = this->getHeight();

			g.setColour (Colours::black.withAlpha(.5f));
			g.drawRoundedRectangle (10, 160, width-20, height/3, 20, 2);

			g.setColour (Colours::blueviolet.withAlpha((float)(slider->getValue() / 10)));
			g.setFont (40);
			g.drawFittedText (paintText, 10, 160, width-20, height/3, Justification::centred, 1);
			
		}

		// ButtonListener
		void buttonClicked (Button* button)
		{
			if (button == button1)
			{
				// respond to button1
				label->setText ("Increase!", false);
				slider->setValue (slider->getValue() + 1, false);
			}
			else if (button == button2)
			{
				// respond to button2
				label->setText ("Decrease!", false);
				slider->setValue (slider->getValue() - 2, false);
				label->setEditable (false, true);
				label->setBorderSize(1, 1);
				label->setColour (Label::ColourIds::backgroundColourId, Colours::white);
				label->setColour (Label::ColourIds::outlineColourId, Colours::black);
			}
			else if (button == button3)
			{
				// respond to button3
				if (button->getToggleState())
				{
					repaint ();
				}
			}
		}

		// slider listener
		void Slider::Listener::sliderValueChanged (Slider* slider)
		{
			if (slider == this->slider)
			{
				label->setText("Slide changed to " + String(slider->getValue(), 2), false);
			}
			if (button3->getToggleState())
			{
				repaint ();
			}
		}

		// label listener
		void labelTextChanged (Label* labelThatHasChanged)
		{
			if (labelThatHasChanged == label)
			{
				paintText = label->getText();
				repaint ();
			}
		}
				
		
		//==============================================================================
	};

#endif//_MAINCOMPONENT_H_ 