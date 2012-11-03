#pragma once

#include "IAudioDevice.h"
#include <string>

namespace GlitterAudio {
	namespace Core {
		namespace Audio {

			class AudioDevice : public IAudioDevice
			{
			public:

				AudioDevice(int driverIndex, int deviceIndex, std::string driver = "", std::string name = "");
				~AudioDevice(void);

				// hardware indexes
				int getDriverIndex() const;
				int getDeviceIndex() const;

				// utils
				std::string getDriver() const;
				std::string getName() const;

			private:

				int mDriverIndex;
				int mDeviceIndex;

				std::string mDriver;
				std::string mName;
			};
		}
	}
}

