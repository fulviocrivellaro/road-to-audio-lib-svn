#include "JuceAudioFacade.h"
#include "AudioDevice.h"
#include "CallbackAudioFormatReader.h"
#include "DiracAudioSource.h"

namespace GlitterAudio {
	namespace Abstraction {

			JuceAudioFacade::JuceAudioFacade(void) : 
						mAudioFormatReaderSource(nullptr), 
						mDiracAudioSource(nullptr), 
						mAudioSourcePlayer(nullptr), 
						seekListener(nullptr)
		{
			int nDevices = mAudioDeviceManager.getAvailableDeviceTypes().size();
			for (int i=0; i<nDevices; i++)
			{
				mDrivers.push_back((const char *)mAudioDeviceManager.getAvailableDeviceTypes()[i]->getTypeName().getCharPointer());
			}
			for (unsigned int i=0; i<mDrivers.size(); i++)
			{
				std::vector<std::string> devices = listDevices(i);
				for (unsigned int j=0; j<devices.size(); j++)
				{
					mAudioDevices.push_back(new GlitterAudio::Core::Audio::AudioDevice(i, j, mDrivers[i], devices[j]));
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

			// register basic audio formats
			mAudioFormatManager.registerBasicFormats();

			// dumps info about current output hardware available

			for (int i=0; i<mAudioDevices.size(); i++)
			{
				const GlitterAudio::Core::Audio::IAudioDevice* dev = mAudioDevices[i];
				DBG("DRV (" + String(dev->getDriverIndex()) + "): " + dev->getDriver().c_str() + " - NAME (" + String(dev->getDeviceIndex()) + "): " + dev->getName().c_str());
			}

			mPitchShiftingSemitones = 0;
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
				//mAudioFormatReaderSource->releaseResources();
				mDiracAudioSource->releaseResources();
				mAudioDeviceManager.closeAudioDevice();
				delete mAudioSourcePlayer;
				delete mDiracAudioSource;
				delete mAudioFormatReaderSource;
			}
		}

		std::vector<std::string> JuceAudioFacade::listDrivers() const
		{
			return mDrivers;
		}

		std::vector<std::string> JuceAudioFacade::listDevices(int driverIndex) const
		{
			std::vector<std::string> devices;
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

		std::vector<const GlitterAudio::Core::Audio::IAudioDevice* const> JuceAudioFacade::listAllDevices() const
		{
			return mAudioDevices;
		}

		std::set<std::string> JuceAudioFacade::getSupportedAudioFormats() const
		{
			std::set<std::string> result;
			for (int i=0; i<mAudioFormatManager.getNumKnownFormats(); i++)
			{
				StringArray extensions = mAudioFormatManager.getKnownFormat(i)->getFileExtensions();
				for (int j=0; j<extensions.size(); j++)
				{
					result.insert(extensions[j].getCharPointer());
				}
			}
			return result;
		}


		bool JuceAudioFacade::setFileSource(std::string filename)
		{
			bool initialized = (mAudioSourcePlayer != nullptr);
			if (initialized)
			{
				pause();
			} else {
				mAudioSourcePlayer = new AudioSourcePlayer();
			}

			WavAudioFormat wavAudioFormat;

			// need to create a new, temporary AudioFormatReaderSource, for the player
			AudioFormatReader *audioFormatReader = mAudioFormatManager.createReaderFor(File((const char*) filename.c_str()));
			GlitterAudio::JuceAudio::CallbackAudioFormatReader* newAudioFormatReaderSource = new GlitterAudio::JuceAudio::CallbackAudioFormatReader(audioFormatReader, true, this);
			GlitterAudio::JuceAudio::DiracAudioSource* newDiracAudioSource = new GlitterAudio::JuceAudio::DiracAudioSource(newAudioFormatReaderSource, false, mPitchShiftingSemitones);
			// AFTER setting the new AudioFormatReaderSource, the releaseResources() method is called on the source instance
			mAudioSourcePlayer->setSource(newDiracAudioSource);

			// check if this is not the first run
			if (initialized)
			{
				// now the old AudioFormatReaderSource is no longer needed - can delete it (AudioSourcePlayer will NOT do it)
				delete mAudioFormatReaderSource;
				delete mDiracAudioSource;
			}
			// we can update our pointer to the current AudioFormatReaderSource at last
			mAudioFormatReaderSource = newAudioFormatReaderSource;
			mDiracAudioSource = newDiracAudioSource;

			int fs = mAudioFormatReaderSource->getAudioFormatReader()->sampleRate;

			int bufferSize = mAudioDeviceManager.getCurrentAudioDevice()->getDefaultBufferSize();
			mAudioDeviceManager.getCurrentAudioDevice()->open(0, 3, fs, bufferSize);

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

		bool JuceAudioFacade::isPlaying() const
		{
			return mAudioDeviceManager.getCurrentAudioDevice() != nullptr && mAudioDeviceManager.getCurrentAudioDevice()->isPlaying();
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

		// FX

		void JuceAudioFacade::setPitchShiftingSemitones(int value)
		{
			mPitchShiftingSemitones = value;
			if (mDiracAudioSource != nullptr)
			{
				mDiracAudioSource->setPitchShiftValue(value);
			}
		}

		// events

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
	}
}