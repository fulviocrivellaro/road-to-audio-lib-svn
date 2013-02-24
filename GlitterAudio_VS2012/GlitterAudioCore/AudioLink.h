#pragma once

class IAudioSource;
class IAudioSink;

class AudioLink
{
public:
	AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNode, unsigned int outputChannel);
	~AudioLink(void);

	unsigned int moveData(unsigned int chunkSize);

private:
	// input parameters
	IAudioSource* mInputNode;
	unsigned int mInputChannel;

	// output parameters
	IAudioSink* mOutputNode;
	unsigned int mOutputChannel;
};

