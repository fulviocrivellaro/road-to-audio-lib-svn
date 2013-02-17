#include "GlitterAudio.h"
#include "AudioFacadeFactory.h"
#include "IAudioPlayer.h"
#include "IAudioChain.h"

GlitterAudio::GlitterAudio(void)
{
	facade = AudioFacadeFactory::createAudioFacade();
	mAudioChain = NULL;
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

IAudioPlayer* GlitterAudio::getBufferedAudioPlayerForDevice()
{
	return facade->getBufferedAudioPlayer();
}

void GlitterAudio::setAudioChain(IAudioChain* audioChain)
{
	mAudioChain = audioChain;
}

void GlitterAudio::start()
{
	if (mAudioChain != NULL)
	{
		mAudioChain->start();
	}
}

void GlitterAudio::stop()
{
	if (mAudioChain != NULL)
	{
		mAudioChain->stop();
	}
}