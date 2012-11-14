#pragma once

#include <thread>

class IRunnable;

class Thread
{
public:
	Thread(IRunnable *runnable, bool deleteOnTerminate = true);
	~Thread(void);

	void startAndJoin();
	void startAndDetach();

private:
	void doStart();

	IRunnable *mRunnable;
	std::thread* mThread;

	bool mDeleteOnTerminate;
};

