// mysoundengine.cpp	Version 10		9/5/05
// The definition file for the methods in MySoundEngine, declared in mysoundengine.h


#include "mysoundengine.h"
#include "errorlogger.h"

MySoundEngine* MySoundEngine::instance=NULL;

MySoundEngine::MySoundEngine(HWND hwnd)
{
	// Initialise dsound
	HRESULT err;
	if (FAILED(DirectSoundCreate8(&DSDEVID_DefaultPlayback, &lpds, NULL)))
	{
		ErrorLogger::Writeln("Failed to create sound player");
		lpds=NULL;
	}

	// Set cooperative level and check for error
	err=lpds->SetCooperativeLevel(hwnd, DSSCL_NORMAL);

	if (FAILED(err))	// If failed to set cooperative level
	{
		ErrorLogger::Writeln("Failed to set cooperative level\n");
		lpds->Release();
		lpds=NULL;
		ErrorLogger::Writeln(ErrorString(err));
	}
}

MySoundEngine::~MySoundEngine()
{
	Release();
}

ErrorType MySoundEngine::Release()
{
	if (lpds)			// If not already null
	{
		lpds->Release();
		lpds=NULL;
		return SUCCESS;
	}
	return FAILURE;
}

MySoundEngine* MySoundEngine::Start(HWND hwnd)
{
	if(instance)
	{
		instance->Terminate();
	}
	instance = new MySoundEngine(hwnd);
	return instance;
}

MySoundEngine* MySoundEngine::GetInstance()
{
	return instance;
}

ErrorType MySoundEngine::Terminate()
{
	if(instance)
	{
		delete instance;
		instance=NULL;
		return SUCCESS;
	}
	else
		return FAILURE;
}

char* MySoundEngine::ErrorString(HRESULT err)
{
	switch(err)
	{
	case DS_OK:
		return "The method succeeded. ";
	case DS_NO_VIRTUALIZATION:
		return "The buffer was created, but another 3-D algorithm was substituted.";
	case DSERR_ACCESSDENIED:
		return "The request failed because access was denied.";
	case DSERR_ALLOCATED :
		return "The request failed because resources, such as a priority level, were already in use by another caller. ";
	case DSERR_ALREADYINITIALIZED :
		return "The object is already initialized. ";
	case DSERR_BADFORMAT :
		return "The specified wave format is not supported. ";
	case DSERR_BADSENDBUFFERGUID :
		return "The GUID specified in an audiopath file does not match a valid mix-in buffer. ";
	case DSERR_BUFFERLOST :
		return "The buffer memory has been lost and must be restored. ";
	case DSERR_BUFFERTOOSMALL :
		return "The buffer size is not great enough to enable effects processing.";
	case DSERR_CONTROLUNAVAIL :
		return "The buffer control (volume, pan, and so on) requested by the caller is not available. Controls must be specified when the buffer is created, using the dwFlags member of DSBUFFERDESC.";
	case DSERR_DS8_REQUIRED:
		return "A DirectSound object of class CLSID_DirectSound8 or later is required for the requested functionality. For more information, see IDirectSound8 Interface.";
	case DSERR_FXUNAVAILABLE:
		return "The effects requested could not be found on the system, or they are in the wrong order or in the wrong location; for example, an effect expected in hardware was found in software.";
	case DSERR_GENERIC :
		return "An undetermined error occurred inside the DirectSound subsystem. ";
	case DSERR_INVALIDCALL :
		return "This function is not valid for the current state of this object. ";
	case DSERR_INVALIDPARAM :
		return "An invalid parameter was passed to the returning function. ";
	case DSERR_NOAGGREGATION :
		return "The object does not support aggregation. ";
	case DSERR_NODRIVER :
		return "No sound driver is available for use, or the given GUID is not a valid DirectSound device ID.";
	case DSERR_NOINTERFACE :
		return "The requested COM interface is not available. ";
	case DSERR_OBJECTNOTFOUND:
		return "The requested object was not found. ";
	case DSERR_OTHERAPPHASPRIO :
		return "Another application has a higher priority level, preventing this call from succeeding. ";
	case DSERR_OUTOFMEMORY :
		return "The DirectSound subsystem could not allocate sufficient memory to complete the caller's request. ";
	case DSERR_PRIOLEVELNEEDED :
		return "A cooperative level of DSSCL_PRIORITY or higher is required. ";
	case DSERR_SENDLOOP:
		return "A circular loop of send effects was detected.";
	case DSERR_UNINITIALIZED :
		return "The IDirectSound8::Initialize method has not been called or has not been called successfully before other methods were called. ";
	case DSERR_UNSUPPORTED :
		return "The function called is not supported at this time. ";
	default:
		return "Error. There is no message for this error.";
	}
}