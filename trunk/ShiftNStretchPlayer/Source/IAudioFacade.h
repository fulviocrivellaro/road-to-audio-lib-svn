/*
  ==============================================================================

    IAudioFacade
    Created: 28 Sep 2012 8:48:54am
    Author:  audiolib

  ==============================================================================
*/

#ifndef __IAUDIOFACADE_CA2E7815__
#define __IAUDIOFACADE_CA2E7815__

#include <vector>
#include <string>

using namespace std;

class IAudioFacade
{
public:

	// hardware methods
	virtual vector<string> getDrivers() = 0;
	virtual vector<string> getDevices(string driver) = 0;

	// audio methods
	/*
	virtual bool play() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool seek() = 0;
	*/
}



#endif  // __IAUDIOFACADE_CA2E7815__
