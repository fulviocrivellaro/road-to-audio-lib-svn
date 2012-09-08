#pragma once

#include "guihandler.h"

class PSTSEntryPoint
{
public:
	PSTSEntryPoint(GUIHandler *newGUIHandler);
	~PSTSEntryPoint(void);
	void run(void);
private:
	GUIHandler *guiHandler;
};

