#include "Thread.h"
#include "IRunnable.h"

#include <iostream>

void runAndDestroy(void* runnableVoid, bool deleteOnTerminate)
{
	// cast to IRunnable
	IRunnable *runnable = (IRunnable*) runnableVoid;
	// execute
	runnable->run();
	// release resources
	if (deleteOnTerminate)
	{
		delete runnable;
	}
}

Thread::Thread(IRunnable* runnable, bool deleteOnTerminate)
{
	mDeleteOnTerminate = deleteOnTerminate;
	mRunnable = runnable;
	mThread = 0;
}

Thread::~Thread(void)
{
	if (mDeleteOnTerminate && mThread != 0)
	{
		delete mThread;
	}
}

void Thread::startAndJoin()
{
	doStart();
	mThread->join();
}

void Thread::startAndDetach()
{
	doStart();
	mThread->detach();
}

void Thread::doStart()
{
	if (!mThread)
	{
		mThread = new std::thread(runAndDestroy, (void*)mRunnable, mDeleteOnTerminate);
	}
}
