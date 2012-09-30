#include "JuceAudioFacade.h"
#include "AudioDevice.h"

JuceAudioFacade::JuceAudioFacade(void)
{
	int nDevices = mAudioDeviceManager.getAvailableDeviceTypes().size();
	for (int i=0; i<nDevices; i++)
	{
		mDrivers.push_back((const char *)mAudioDeviceManager.getAvailableDeviceTypes()[i]->getTypeName().getCharPointer());
	}
	for (unsigned int i=0; i<mDrivers.size(); i++)
	{
		vector<string> devices = listDevices(i);
		for (unsigned int j=0; j<devices.size(); j++)
		{
			mAudioDevices.push_back(new AudioDevice(i, j, mDrivers[i], devices[j]));
		}
	}
}


JuceAudioFacade::~JuceAudioFacade(void)
{
	// deallocate AudioDevice objects
	for (int i=0; i<mAudioDevices.size(); i++)
	{
		delete mAudioDevices[i];
	}
}

vector<string> JuceAudioFacade::listDrivers()
{
	return mDrivers;
}

vector<string> JuceAudioFacade::listDevices(int driverIndex)
{
	vector<string> devices;
	int nDevices = mDrivers.size();
	if (driverIndex < nDevices)
	{
		StringArray arr = mAudioDeviceManager.getAvailableDeviceTypes()[driverIndex]->getDeviceNames();
		for (int i=0; i<arr.size(); i++)
		{
			devices.push_back((const char*)arr[i].getCharPointer());
		}
	}
	return devices;
}

vector<const IAudioDevice* const> JuceAudioFacade::listAllDevices()
{
	return mAudioDevices;
}