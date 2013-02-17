#include "RtAudioHardwareFacade.h"
#include "RTAudioPlayer.h"
#include "RTAudioPlayer.h"

RtAudioHardwareFacade::RtAudioHardwareFacade(void)
{
	mRtAudio = new RtAudio();
	int devices = mRtAudio->getDeviceCount();
	if (devices < 1) {
		mRtAudio = 0;
		std::cout << "\nNo audio devices found!\n";
	} else {

		std::cout << "Found " << devices << " devices!" << std::endl << std::endl;

		// Scan through devices for various capabilities
		RtAudio::DeviceInfo info;
		for (int i=0; i<devices; i++) {
			try {
				info = mRtAudio->getDeviceInfo(i);
			} catch (RtError &error) {
				error.printMessage();
				break;
			}

			mDevices.push_back(new AudioDevice(AudioDriver::WIN_ASIO, i, info.inputChannels, info.outputChannels));

#if __GLITTERAUDIO__LOG__VERBOSE__ >= __GLITTERAUDIO__LOG__LEVEL__
			// Print, for example, the maximum number of output channels for each device
			std::cout << "DEVICE = " << i << std::endl;
			std::cout << "name: " << info.name << std::endl;
			std::cout << "- duplex channels: " << info.duplexChannels << std::endl;
			std::cout << "-  input channels: " << info.inputChannels << std::endl;
			std::cout << "- output channels: " << info.outputChannels << std::endl;
			std::cout << "-   default input: " << info.isDefaultInput << std::endl;
			std::cout << "-  default output: " << info.isDefaultOutput << std::endl;
			std::cout << "-  native formats: " << info.nativeFormats << std::endl;
			std::cout << "-          probed: " << info.probed << std::endl;
			//std::cout << "-    sample rates: " << info.sampleRates << std::endl;
			std::cout << std::endl;
#endif
		}
	}

}


RtAudioHardwareFacade::~RtAudioHardwareFacade(void)
{
	// deallocate AudioDevice objects
	for (int i=0; i<mDevices.size(); i++)
	{
		delete mDevices[i];
	}
	if (mRtAudio != 0)
	{
		delete mRtAudio;
	}
}

std::vector<const AudioDevice* const> RtAudioHardwareFacade::listAllDevices() const
{
	return mDevices;
}

std::vector<const AudioDevice* const> RtAudioHardwareFacade::listDevicesForDriver(AudioDriver driver) const
{
	std::vector<const AudioDevice* const> result;
	for (int i=0; i<mDevices.size(); i++)
	{
		if (mDevices[i]->getDriver() == driver)
		{
			result.push_back(mDevices[i]);
		}
	}
	return result;
}

IAudioPlayer* RtAudioHardwareFacade::getBufferedAudioPlayer()
{
	return new RTAudioPlayer(*mRtAudio);
}