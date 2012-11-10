#include "GlitterAudio.h"
#include "AudioFacadeFactory.h"
#include "IAudioSink.h"

GlitterAudio::GlitterAudio(void)
{
	facade = AudioFacadeFactory::createAudioFacade();
}

GlitterAudio::~GlitterAudio(void)
{
	delete facade;
}

std::vector<const AudioDevice* const> GlitterAudio::listAllDevices() const
{
	return facade->listAllDevices();
}

std::vector<const AudioDevice* const> GlitterAudio::listDevicesForDriver(AudioDriver driver) const
{
	return facade->listDevicesForDriver(driver);
}

IAudioSink* GlitterAudio::getAudioSinkForDevice()
{
	return facade->getAudioSink();
}