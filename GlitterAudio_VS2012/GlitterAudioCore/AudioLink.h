#pragma once

#include <vector>

class IAudioSource;
class IAudioSink;

struct OutputSink {
	IAudioSink* sink;
	unsigned int channel;
};

class AudioLink
{
public:
	AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNode, unsigned int outputChannel);
	AudioLink(IAudioSource* inputNode, unsigned int inputChannel, IAudioSink* outputNodes[], unsigned int outputChannels[], unsigned int outputNodesCount);
	~AudioLink(void);

	//void addSink(IAudioSink* outputNode, unsigned int outputChannel);

	unsigned int moveData(unsigned int chunkSize);

private:
	// input parameters
	IAudioSource* mInputNode;
	unsigned int mInputChannel;

	// output parameters
	//IAudioSink* mOutputNode;
	//unsigned int mOutputChannel;
	std::vector<OutputSink> mSinks;
};

