// MyPicture.h Specification for the class MyPicture

// Chris Rook

// version 10 9/5/05

// Inline functions corrected
// Blit and FillRect changed to pass-by-reference
// Picture now reloads if alt-tabbed away

// Version 10
// Safer code
// Use of ErrorLogger and more error messages
// Update to DirectDrawSurface 7

#ifndef mypicture_h
#define mypicture_h

#pragma comment(lib, "ddraw.lib")

#include <ddraw.h>		// directX draw
#include "errortype.h"

class MyDrawEngine;


// Macros ****************************************************

// Class Spec ************************************************

class MyPicture
{
	friend MyDrawEngine;				// So that MyDrawEngine can access the lpTheSurface attribute

private:
	IDirectDraw7* lpdd;
	LPDIRECTDRAWSURFACE7 lpTheSurface;	// The surface that MyPicture encapsulates
	char* mpszSourceFileName;
	USHORT *videoAddress;				// Pointer to start of video buffer
	DDSURFACEDESC2 ddsd;					// Surface "order form"

public:

// Public attributes
	int width;				// The width of the image (after loading)
	int height;				// The height of the image (after loading)
	int memoryPitch;

// Public methods

		// Precondition		The surface is locked.
		//					x1 and y1 specify a point on the MyPicture
		// Postcondition	A point of the specified colour has been
		//					plotted at x1,y1 on the surface
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if the surface is not locked,
		//					and (x1,y1) is not on the MyPicture area.
ErrorType DrawPoint(int x, int y, int colour);

		// Postcondition	The colour of the specified point has been
		//					returned
		// Returns			SUCCESS
		// Note: if the specified point is not located on the surface, the result
		// is invalid
int GetPoint(int x, int y);

	// Precondition:
	//  MyPicture has been initalised using LoadBitmap or MakeBlank
	// Postcondition:
	//  The surface is locked for the purposes of pixel plotting.
	// Note:
	//  Should be Unlocked after pixel plotting using "Unlock()"
ErrorType Lock();

	// Precondition:
	//  MyPicture has been Locked
	// Postcondition:
	//  The surface is unlocked and can now be used normally
ErrorType Unlock();


	// Precondition:
	//	MyDrawEngine has had "Start" called on it.
	// Postcondition
	//  A secondary surface is created. lpTheSurface points to it.
	MyPicture();

	// postcondition:
	//  The surface has been checked for validity (still usable for on-screen drawing)
	// If not, the function will attempt to reaquire.
	// If reaquisition is successful, the function will attempt to reload from file,
	// if the MyPicture was initialised using LoadBitmap.
	// If the MyPicture was initialised using MakeBlank(), the surface is blanked.
	// Note:
	//	All memory of any drawing to the surface since initialising will be lost.
	// Returns:
	//	true if surface was valid or successfully reloaded.
	//	false otherwise
	bool Validate();

	// Destructor. Calls "Release"
	~MyPicture();

	// Loads a bitmap with the specified filename into the MyPicture
	// Preconditions:
	//	If the MyPicture already holds an image, or a blank image, the dimesions
	//  of both the existing image and the image to be loaded must match.
	//  Should not really load an image over an existing image. Causes a mild memory leak.
	//	
	// Postcondition:
	//  The image in the file is loaded into the MyPicture object or FAILURE will have been returned
	// Parameters:
	//	pszFilename - a string containing the filename of the bitmap to be loaded
	//  flags - any flags that you wish to pass onto the directDrawSurfaceDescriptor.
	//		Normally leave blank for defaults. Use "DDSCAPS_SYSTEMMEMORY to specify creation in system memory
	//		Use "DDSCAPS_VIDEOMEMORY" to insist on creation in video memory.
	// Returns:
	//  SUCCESS if file loaded successfully
	//  FAILURE if file failed to load (file not found, file wrong format)
	ErrorType LoadBitmap(char* pszFilename, int flags=NULL);

	// Loads the MyPicture with a blank image of the size specified.
	// The image will be entirely of colour zero.
	// Preconditions:
	//	If the MyPicture already holds an image, or a blank image, the dimesions
	//  of both the existing image and the blank image to be created must match.
	// Postcondition:
	//  A blank (0) image of the specified dimensions has been created in the MyPicture or
	//	FAILURE will have been returned
	// Parameters:
	//	width - the width of the image to be created, in pixels
	//	height - the height of the image to be created, in pixels
	//  flags - any flags that you wish to pass onto the directDrawSurfaceDescriptor.
	//		Normally leave blank for defaults. Use "DDSCAPS_SYSTEMMEMORY to specify creation in system memory
	//		Use "DDSCAPS_VIDEOMEMORY" to insist on creation in video memory.
	// Returns:
	//  SUCCESS if blank image created successfully
	//  FAILURE if failed to create blank image
	ErrorType MakeBlank(int width, int height, int flags=NULL);

	// Draws another MyPicture onto this MyPicture
	// Preconditions:
	//	Not fully tested. Not sure how it will behave if the destinationRect goes off
	//	the edge of the current picture.
	//	The MyPicture and the sourcePicture must contain an image, either using MakeBlank,
	//	or LoadBitmap.
	// Postconditions:
	//  The image from sourcePicture will be drawn onto this MyPicture using the specified
	//	destinationRect and sourceRect  or FAILURE will have been returned.
	// Parameters:
	//	destinationRect - The rectangle describing where to blit to.
	//	sourceRect - The rectangle describing where to blit from on the sourcePicture
	//  sourcePicture - The MyPicture to copy the image from
	// Returns:
	//  SUCCESS if blit performed successfully
	//  FAILURE if blit failed
	ErrorType Blit(RECT& destinationRect, RECT& sourceRect, MyPicture *sourcePicture);

	// Draws a rectangle of the specified colour onto this MyPicture
	// Preconditions:
	//	Not fully tested. Not sure how it will behave if the destinationRect goes off
	//	the edge of the current picture.
	//	The MyPicture must contain an image, either using MakeBlank,
	//	or LoadBitmap.
	// Postconditions:
	//  A rectangle will be drawn onto this MyPicture using the specified
	//	destinationRect and colour or FAILURE will have been returned.
	// Parameters:
	//	destinationRect - The rectangle describing where to blit to.
	//  colour - the colour of the rectangle to be drawn.
	// Returns:
	//  SUCCESS if blit performed successfully
	//  FAILURE if blit failed
	ErrorType FillRect(RECT& destinationRect, int colour);

	// Postcondition
	//  Releases memory and the DirectX surface
	//  lpdd set to NULL
	//  lpTheSurface set to NULL
	//	height an width are set to 0.
	// Returns:
	//  SUCCESS if lpTheSurface was previously initialised
	//  FAILURE if lpTheSurface was not previously initialised
	void Release();


};




#endif