#include "AudioDevice.h"

namespace GlitterAudio {
	namespace Core {
		namespace Audio {

			AudioDevice::AudioDevice(int driverIndex, int deviceIndex, std::string driver, std::string name)
			{
				AudioDevice::mDriverIndex = driverIndex;
				AudioDevice::mDeviceIndex = deviceIndex;
				AudioDevice::mDriver = driver;
				AudioDevice::mName = name;
			}

			AudioDevice::~AudioDevice(void) {}

			// hardware indexes
			inline int AudioDevice::getDriverIndex() const
			{
				return mDriverIndex;
			}

			inline int AudioDevice::getDeviceIndex() const
			{
				return mDeviceIndex;
			}

			// utils
			inline std::string AudioDevice::getDriver() const
			{
				return mDriver;
			}

			inline std::string AudioDevice::getName() const
			{
				return mName;
			}
		}
	}
}