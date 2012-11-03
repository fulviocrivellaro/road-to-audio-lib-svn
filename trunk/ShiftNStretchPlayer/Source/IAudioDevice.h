#pragma once

#include <string>

namespace GlitterAudio {
	namespace Core {
		namespace Audio {
			class IAudioDevice
			{
			public:
				virtual ~IAudioDevice(void) {};

				// hardware indexes
				virtual int getDriverIndex() const = 0;
				virtual int getDeviceIndex() const = 0;

				// utils
				virtual std::string getDriver() const = 0;
				virtual std::string getName() const = 0;
			};
		}
	}
}
