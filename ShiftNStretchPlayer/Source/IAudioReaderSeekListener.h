#pragma once
namespace GlitterAudio {
	namespace Core {
		namespace Audio {

			class IAudioReaderSeekListener
			{
			public:

				virtual ~IAudioReaderSeekListener(void) {}

				virtual void onSeek(int samplesRead, long currentPosition) = 0;

			};
		}
	}
}

