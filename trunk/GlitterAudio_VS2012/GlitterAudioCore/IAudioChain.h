#pragma once

class IAudioSource;
class IAudioSink;

class IAudioChain
{
public:
	virtual void link(IAudioSource* source, unsigned int sourceChannel, IAudioSink* sink, unsigned int destChannel) = 0;
	virtual void link(IAudioSource* source, unsigned int sourceChannel, IAudioSink* outputNodes[], unsigned int outputChannels[], unsigned int outputNodesCount) = 0;
	virtual void processChunk() = 0;
	virtual void processChunks(unsigned int count) = 0;

	// simple transport methods
	virtual void start() = 0;
	virtual void stop() = 0;

	// TODO: seek?
};

