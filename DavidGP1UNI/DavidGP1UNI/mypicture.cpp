// version 10 9/5/05
// The definition file for the methods in MyPicture, declared in mypicture.h


#include "Mypicture.h"
#include "mydrawengine.h"

#define BITMAP_ID 0x4D42
#define MAX_COLORS_PALETTE 256

// *****************************************************************

MyPicture::MyPicture()
{	
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

	if(!pTheDrawEngine)
	{
		ErrorLogger::Writeln("Error creating MyPicture, no MyDrawEngine");
	}
	ZeroMemory(&ddsd, sizeof(ddsd));
	height=0;
	width=0;
	this->lpdd=pTheDrawEngine->lpdd;
	lpTheSurface=NULL;
	memoryPitch=0;
	videoAddress=NULL;
	mpszSourceFileName = NULL;
}

MyPicture::~MyPicture()
{
	// Make sure memory and ddraw have been released
	if (lpTheSurface)
	{
		lpTheSurface->Release();
	}

	if(mpszSourceFileName)
	{
		delete mpszSourceFileName;
		mpszSourceFileName=NULL;
	}
}

bool MyPicture::Validate()
{
	if (FAILED(lpTheSurface->IsLost()))		// See if primary surface is lost
	{	
		if(FAILED(lpTheSurface->Restore()))	// Try to reaquire
			return FAILURE;					// If it is still postal
		else
		{
			// Need to reload. Damn. Is this going to be churning all the time I have ALT-TABBED? Don't think so.
			if(mpszSourceFileName)	// If it has a file name
			{
				if(FAILED(LoadBitmap(mpszSourceFileName))) // Reload
					return FAILURE;	
			}
			else					// Must be a blank one. Hope it hasn't been drawn on.
			{
				// Blank out
				RECT whole;
				whole.left=0;
				whole.top=0;
				whole.bottom=height;
				whole.right=width;

				FillRect(whole, 0);
			}
			return SUCCESS;						// If it recovered
		}
	}
	return SUCCESS;								// If it never went away
}

void MyPicture::Release()
{ 
	// Set everything to zero or null
	height=0;
	width=0;
	lpdd=NULL;

	// If it is still valid, release the surface
	if (lpTheSurface)
	{
		lpTheSurface->Release();
		lpTheSurface=NULL;
	}
}

ErrorType MyPicture::LoadBitmap(char *pszFilename, int flags)
{
	// Keep a permanent record of the filename

	int length = int(strlen(pszFilename)+1);

	mpszSourceFileName = new char[length];

	strcpy_s(mpszSourceFileName, length, pszFilename);

	HBITMAP hbm;
	BITMAP bmInfo;
	DDSURFACEDESC2 ddsd;
	HDC hdcImage = NULL;
	HDC surfaceDC = NULL;

	flags=0;

	// Load an image from file to a bitmap handle
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), pszFilename, IMAGE_BITMAP, 0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

	// If it didn't load, bug out.
	if (hbm == NULL)
	{
		ErrorLogger::Writeln("File didn't load\n");
		ErrorLogger::Writeln(*pszFilename);
		  return FAILURE;
	}

	// Put the info about the bitmap into a struct
	GetObject(hbm,sizeof(bmInfo),&bmInfo);

	// Select Image into a device context

	hdcImage = CreateCompatibleDC(NULL);

	if(hdcImage == NULL)
	{
		  ErrorLogger::Writeln("Couldn't create DC\n");
		  return FAILURE;
	}


	SelectObject(hdcImage, hbm);

	// now to create the DDraw surface so I can load the image onto it
	
	this->height=bmInfo.bmHeight;
	this->width=bmInfo.bmWidth;

	// Fill in the order form
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;		// Set capablilties
	ddsd.dwHeight	=this->height;						// Set height
	ddsd.dwWidth	=this->width;						// Set width
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|flags;	// Set as offscreen surface, also any
														// flags requested by call - such as
														// a request for video memory storage

	// Create the surface

	int err;
	(err=(lpdd->CreateSurface(&ddsd, &lpTheSurface, NULL)));
	if (FAILED(err))
	{
		ErrorLogger::Writeln("Could not create a surface");
		ErrorLogger::Writeln(*pszFilename);
		ErrorLogger::Writeln(MyDrawEngine::ErrorString(err));

		  return FAILURE;
	}

	// Set colour key to 0
	DDCOLORKEY ddColourKey;
	ddColourKey.dwColorSpaceHighValue=0;
	ddColourKey.dwColorSpaceLowValue=0;

	lpTheSurface->SetColorKey(DDCKEY_SRCBLT, &ddColourKey);

	// Copy the bitmap info into it.

	if (FAILED(lpTheSurface->GetDC(&surfaceDC)))
	{
		  ErrorLogger::Writeln("Couldn't get DC of bitmap\n");
		  return FAILURE;
	}


	StretchBlt(surfaceDC,0,0,width,height,hdcImage,0,0,width, height, SRCCOPY);
	lpTheSurface->ReleaseDC(surfaceDC);

	DeleteDC(hdcImage);

	return SUCCESS;
}

ErrorType MyPicture::MakeBlank(int width, int height, int flags)
{

	DDSURFACEDESC2 ddsd;				// An "order form" for the surface

	// create the DDraw surface
	
	this->height=height;
	this->width=width;

	// Fill in the order form
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags=DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT;		// Set capablilties
	ddsd.dwHeight	=this->height;						// Set height
	ddsd.dwWidth	=this->width;						// Set width
	ddsd.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN|flags;	// Set as offscreen surface, also any
														// flags requested by call - such as
														// a request for video memory storage
	// Create the surface

	int err;
	(err=(lpdd->CreateSurface(&ddsd, &lpTheSurface, NULL)));
	if (err!=DD_OK)
	{
		ErrorLogger::Writeln("Couldn't make blank surface.\n");
		ErrorLogger::Writeln(MyDrawEngine::GetInstance()->ErrorString(err));
		  return FAILURE;
	}

	// Set colour key to 0
	DDCOLORKEY ddColourKey;
	ddColourKey.dwColorSpaceHighValue=0;
	ddColourKey.dwColorSpaceLowValue=0;

	lpTheSurface->SetColorKey(DDCKEY_SRCBLT, &ddColourKey);

	// Blank the surface with black pixels

	RECT tempRect;
	tempRect.top=0;
	tempRect.bottom=height-1;
	tempRect.left=0;
	tempRect.right=width-1;

	FillRect(tempRect, 0);

	return SUCCESS;

}	// End function


ErrorType MyPicture::Blit(RECT& destinationRect, RECT& sourceRect, MyPicture *sourcePicture)
{
	// Adjust the sourceRect to make sure it does not go beyond the size of the sourcePicture
	if (sourceRect.left<0)	sourceRect.left		= 0;
	if (sourceRect.top<0)	sourceRect.top		= 0;
	if (sourceRect.right>sourcePicture->width)		sourceRect.right	= sourcePicture->width;
	if (sourceRect.bottom>sourcePicture->height)	sourceRect.bottom	= sourcePicture->height;

	// Adjust the destinationRect to make sure it does not go beyond the size of this MyPicture	
	if (destinationRect.left<0) destinationRect.left=0;
	if (destinationRect.top<0) destinationRect.top=0;
	if (destinationRect.right<0) destinationRect.right=width;
	if (destinationRect.bottom<0) destinationRect.bottom=height;

	// Attempt to blit and return failure if DDraw reports failure
	HRESULT err= lpTheSurface->Blt(&destinationRect, sourcePicture->lpTheSurface, &sourceRect, (DDBLT_WAIT | DDBLT_KEYSRC),NULL);
	if (FAILED(err))
	{
		ErrorLogger::Writeln("Blit failed\n");
		if(this->mpszSourceFileName!=NULL)
			ErrorLogger::Writeln(mpszSourceFileName);
		ErrorLogger::Writeln(MyDrawEngine::GetInstance()->ErrorString(err));
		  return FAILURE;
	}

	return SUCCESS;
}	// End function

ErrorType MyPicture::DrawPoint(int x, int y, int colour)
{
	if(x>=0 && x<width)
		{
		if(y>=0 && y<height)
			{
			videoAddress[x+y*memoryPitch]=colour;
			return SUCCESS;
			}
		}
	return FAILURE;
}

int MyPicture::GetPoint(int x, int y)
{
	if(x>=0 && x<width)
		{
		if(y>=0 && y<height)
			{
			return videoAddress[x+y*memoryPitch];
			}
		}
	return -1;
}

ErrorType MyPicture::Lock()
{
	if (!lpTheSurface)
	   return FAILURE;

	// lock the surface
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if FAILED(lpTheSurface->Lock(NULL,&ddsd,DDLOCK_WAIT |
DDLOCK_SURFACEMEMORYPTR,NULL))
		return FAILURE;

	videoAddress	= (USHORT*)ddsd.lpSurface;
	memoryPitch		= ddsd.lPitch>>1;
	
	return SUCCESS;
}

ErrorType MyPicture::Unlock()
{

	// check actually exists
	if (!lpTheSurface)
	   return FAILURE;

	// unlock it
	if FAILED(lpTheSurface->Unlock(NULL))
		return FAILURE;

	// return success
	return SUCCESS;
}


ErrorType MyPicture::FillRect(RECT& destinationRect, int colour)
{
	// to do: clip this rectangle - or is it done by the DDclipper?

	DDBLTFX ddbltfx;	// FX order form

	memset(&ddbltfx,0,sizeof(ddbltfx));
	ddbltfx.dwSize=sizeof(ddbltfx);


	// set FX to the colour requested
	ddbltfx.dwFillColor = colour; 


	// Fill in the surface
	lpTheSurface->Blt(&destinationRect, 
			   NULL,							// nothing to copy from            
			   NULL,							// nothing to copy from
			   DDBLT_COLORFILL | DDBLT_WAIT,	// fill and wait for complete
			   &ddbltfx);						// the order form

	return SUCCESS;
}	// End function

