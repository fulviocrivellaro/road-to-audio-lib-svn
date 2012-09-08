#pragma once
class GUIReceiver
{
public:

	virtual ~GUIReceiver(void);

	// receive the panpot value
	virtual void onPitchShiftValueChanged(int value);
	virtual void onTimeStretchValueChanged(int value);

	// receive the buttons' callbacks
	virtual void onStartPressed();
	virtual void onPausePressed();
	virtual void onStopPressed();
	virtual void onRewindPressed();

	// receive the progress bar
	virtual void onProgressValueChanged(int value);

};

