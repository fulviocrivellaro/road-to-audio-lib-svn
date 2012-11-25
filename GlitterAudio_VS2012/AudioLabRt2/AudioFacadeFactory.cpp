#include "AudioFacadeFactory.h"
#include "GlitterAudioDefines.h"

// RtAudio specific factory
#ifdef __GLITTERAUDIO__USE__RTAUDIO__
#include "RtAudioHardwareFacade.h"
IAudioHardwareFacade* AudioFacadeFactory::createAudioFacade()
{
	return new RtAudioHardwareFacade();
}
#endif

// PortAudio specific factory
#ifdef __GLITTERAUDIO__USE__PORTAUDIO__
#include "PortAudioHardwareFacade.h"
IAudioHardwareFacade* AudioFacadeFactory::createAudioFacade()
{
	return new PortAudioHardwareFacade();
}
#endif