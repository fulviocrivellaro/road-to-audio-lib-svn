#pragma once

class IAudioReaderSeekListener
{
public:

	virtual ~IAudioReaderSeekListener(void) {}

	virtual void onSeek(int samplesRead, long currentPosition) = 0;

};

