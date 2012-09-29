#include "JuceAudioFacade.h"
#include "AudioDevice.h"

JuceAudioFacade::JuceAudioFacade(void)
{
}


JuceAudioFacade::~JuceAudioFacade(void)
{
}

vector<string> JuceAudioFacade::listDrivers()
{
	vector<string> drivers = vector<string>();
	int nDevices = audioDeviceManager.getAvailableDeviceTypes().size();
	for (int i=0; i<nDevices; i++)
	{
		drivers.push_back((const char *)audioDeviceManager.getAvailableDeviceTypes()[i]->getTypeName().getCharPointer());
	}
	return drivers;
}

vector<string> JuceAudioFacade::listDevices(int driverIndex)
{
	vector<string> devices;
	int nDevices = audioDeviceManager.getAvailableDeviceTypes().size();
	if (driverIndex < nDevices)
	{
		StringArray arr = audioDeviceManager.getAvailableDeviceTypes()[driverIndex]->getDeviceNames();
		for (int i=0; i<arr.size(); i++)
		{
			devices.push_back((const char*)arr[i].getCharPointer());
		}
	}
	return devices;
}

vector<AudioDevice> JuceAudioFacade::listAllDevices()
{
	vector<AudioDevice> deviceObjs;
	vector<string> drivers = listDrivers();
	for (unsigned int i=0; i<drivers.size(); i++)
	{
		vector<string> devices = listDevices(i);
		for (unsigned int j=0; j<devices.size(); j++)
		{
			deviceObjs.push_back(AudioDevice(i, j, drivers[i], devices[j]));
		}
	}
	return deviceObjs;
}