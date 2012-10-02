#include "JuceAudioFacade.h"
#include "AudioDevice.h"
#include "CallbackAudioFormatReader.h"

JuceAudioFacade::JuceAudioFacade(void) :
	mAudioFormatReaderSource(nullptr), mAudioSourcePlayer(nullptr), seekListener(nullptr)
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

	DBG("Initializing");
	String outcome = mAudioDeviceManager.initialise(0, 3, nullptr, false);
	if (outcome.isEmpty())
	{
		DBG("OK - playing on " + mAudioDeviceManager.getCurrentAudioDeviceType());
	} else {
		DBG("Initialization error: " + outcome);
	}

	// dumps info about current output hardware available
	
	for (int i=0; i<mAudioDevices.size(); i++)
	{
		const IAudioDevice* dev = mAudioDevices[i];
		DBG("DRV (" + String(dev->getDriverIndex()) + "): " + dev->getDriver().c_str() + " - NAME (" + String(dev->getDeviceIndex()) + "): " + dev->getName().c_str());
	}
}


JuceAudioFacade::~JuceAudioFacade(void)
{
	// deallocate AudioDevice objects
	for (int i=0; i<mAudioDevices.size(); i++)
	{
		delete mAudioDevices[i];
	}

	if (mAudioSourcePlayer != nullptr)
	{
		mAudioFormatReaderSource->releaseResources();
		mAudioDeviceManager.closeAudioDevice();
		delete mAudioSourcePlayer;
		delete mAudioFormatReaderSource;
	}
}

vector<string> JuceAudioFacade::listDrivers() const
{
	return mDrivers;
}

vector<string> JuceAudioFacade::listDevices(int driverIndex) const
{
	vector<string> devices;
	int nDevices = mDrivers.size();
	if (driverIndex < nDevices)
	{
		//mAudioDeviceManager.getAvailableDeviceTypes()[0]->getDeviceNames();
		//StringArray arr = mAudioDeviceManager.getAvailableDeviceTypes()[driverIndex]->getDeviceNames();
		StringArray arr;
		for (int i=0; i<arr.size(); i++)
		{
			devices.push_back((const char*)arr[i].getCharPointer());
		}
	}
	return devices;
}

vector<const IAudioDevice* const> JuceAudioFacade::listAllDevices() const
{
	return mAudioDevices;
}

bool JuceAudioFacade::setFileSource(std::string filename)
{
	int bufferSize = mAudioDeviceManager.getCurrentAudioDevice()->getDefaultBufferSize();

	bool initialized = (mAudioSourcePlayer != nullptr);
	if (initialized)
	{
		stop();
	} else {
		mAudioSourcePlayer = new AudioSourcePlayer();
	}

	WavAudioFormat wavAudioFormat;
	
	// need to create a new, temporary AudioFormatReaderSource, for the player
	AudioFormatReaderSource* newAudioFormatReaderSource = new CallbackAudioFormatReader(wavAudioFormat.createReaderFor(File((const char*) filename.c_str()).createInputStream(), false), true, this);
	// AFTER setting the new AudioFormatReaderSource, the releaseResources() method is called on the source instance
	mAudioSourcePlayer->setSource(newAudioFormatReaderSource);

	// check if this is not the first run
	if (initialized)
	{
		// now the old AudioFormatReaderSource is no longer needed - can delete it (AudioSourcePlayer will NOT do it)
		delete mAudioFormatReaderSource;
	}
	// we can update our pointer to the current AudioFormatReaderSource at last
	mAudioFormatReaderSource = newAudioFormatReaderSource;
	
	int fs = mAudioFormatReaderSource->getAudioFormatReader()->sampleRate;

	mAudioDeviceManager.getCurrentAudioDevice()->open(0, 3, fs, bufferSize);
	mAudioFormatReaderSource->prepareToPlay(bufferSize, fs);

	return true;
}

int JuceAudioFacade::getSamplingFrequency() const
{
	if(mAudioFormatReaderSource != nullptr)
	{
		return mAudioFormatReaderSource->getAudioFormatReader()->sampleRate;
	}
	return -1;
}

long JuceAudioFacade::getSourceLength() const
{
	if (mAudioFormatReaderSource != nullptr)
	{
		return mAudioFormatReaderSource->getTotalLength();
	} else {
		return 0;
	}
}

bool JuceAudioFacade::play()
{
	if (mAudioFormatReaderSource != nullptr)
	{
		mAudioDeviceManager.getCurrentAudioDevice()->start(mAudioSourcePlayer);
		return true;
	} else {
		return false;
	}
}

bool JuceAudioFacade::stop()
{
	if (pause())
	{
		return seek(0);
	} else {
		return false;
	}
}

bool JuceAudioFacade::pause()
{
	if (mAudioFormatReaderSource != nullptr)
	{
		mAudioDeviceManager.getCurrentAudioDevice()->stop();
		return true;
	} else {
		return false;
	}
}

bool JuceAudioFacade::seek(long newPosition)
{
	if(mAudioFormatReaderSource != nullptr)
	{
		mAudioFormatReaderSource->setNextReadPosition(newPosition);
		return true;
	}
	return false;
}

void JuceAudioFacade::onSeek(int samplesRead, long currentPosition)
{
	if (seekListener != nullptr)
	{
		seekListener->onSeek(samplesRead, currentPosition);
	}
}

void JuceAudioFacade::setAudioSeekListener(IAudioReaderSeekListener *newSeekListener)
{
	seekListener = newSeekListener;
}