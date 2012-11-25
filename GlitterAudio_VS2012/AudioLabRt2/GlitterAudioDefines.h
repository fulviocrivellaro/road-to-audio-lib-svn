// **************** AUDIO LIBRARY ******************* //

#define __GLITTERAUDIO__USE__RTAUDIO__
//#define __GLITTERAUDIO__USE__PORTAUDIO__
//#define __GLITTERAUDIO__USE__JUCE__

// **************** AUDIO DRIVERS ******************* //

#define __GLITTERAUDIO__SUPPORT__ASIO__
//#define __GLITTERAUDIO__SUPPORT__DIRECTSOUND__
//#define __GLITTERAUDIO__SUPPORT__WASAPI__
//#define __GLITTERAUDIO__SUPPORT__COREAUDIO__
//#define __GLITTERAUDIO__SUPPORT__ALSA__

// ****************** CONSTANTS ********************* //

#define __GLITTERAUDIO__MAX__OUTPUT__CHANNELS__ 128

// ****************** LOG LEVEL ********************* //

#define __GLITTERAUDIO__LOG__ERROR__ 4
#define __GLITTERAUDIO__LOG__INFO__ 3
#define __GLITTERAUDIO__LOG__DEBUG__ 2
#define __GLITTERAUDIO__LOG__VERBOSE__ 1

#define __GLITTERAUDIO__LOG__LEVEL__ __GLITTERAUDIO__LOG__ERROR__

// **************** DEPENDENCIES ******************** //
// **************** DO NOT EDIT! ******************** //

// RTAudio directives
#if defined(__GLITTERAUDIO__USE__RTAUDIO__)
	#if defined(__GLITTERAUDIO__SUPPORT__ASIO__)
		#define __WINDOWS_ASIO__
	#endif
	#ifdef __GLITTERAUDIO__SUPPORT__DIRECTSOUND__
		#define __WINDOWS_DS__
	#endif
#endif