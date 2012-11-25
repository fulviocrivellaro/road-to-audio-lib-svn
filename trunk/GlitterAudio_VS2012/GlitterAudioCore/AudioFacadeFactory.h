#pragma once

#include "IAudioHardwareFacade.h"

class AudioFacadeFactory
{
public:
	static IAudioHardwareFacade* createAudioFacade();
};

