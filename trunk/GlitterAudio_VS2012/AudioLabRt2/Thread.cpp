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

void Thread::start()
{
	// mThread must NOT exist
	if (!mThread)
	{
		mThread = new std::thread(runAndDestroy, (void*)mRunnable, mDeleteOnTerminate);
	}
}

void Thread::join()
{
	// mThread MUST exist
	if (mThread)
	{
		mThread->join();
	}
}

void Thread::detach()
{
	// mThread MUST exist
	if (mThread)
	{
		mThread->detach();
	}
}

void Thread::startAndJoin()
{
	this->start();
	this->join();
}

void Thread::startAndDetach()
{
	this->start();
	this->detach();
}
