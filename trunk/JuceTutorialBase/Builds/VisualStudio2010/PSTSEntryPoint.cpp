#include "PSTSEntryPoint.h"


PSTSEntryPoint::PSTSEntryPoint(GUIHandler *newGUIHandler)
{
	guiHandler = newGUIHandler;
}


PSTSEntryPoint::~PSTSEntryPoint(void)
{
}

void PSTSEntryPoint::run()
{
	guiHandler->setTimeStretchValue(120);
}