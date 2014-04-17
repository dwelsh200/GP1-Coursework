// MyDrawEngine.h - Header file for MyDrawEngine object

// Version 11a 14/3/08 - ClearBackBuffer blits twice to allow for problems with current NVIDIA
// drivers treating a colour 0 fill as transparent.
// Clipper for fullscreen mode supported.

// version 11 6/3/08
// Vector support
// Windowed mode support

// 7.1 - Added write text method
// 7.2 - Added number writing methods
// 7.3 - DrawAt method fixed

// Inline functions corrected
// Blit and FillRect changed to pass-by-reference
// _RGB15BIT macro fixed

// 8.1 Reacquires surfaces if lost - reloads from file.

// 9.2 Removed a pointer error caused when deleting DX objects that
//		have been released.
//		Cleared up a warning message from TextOutput compiling

// version 10 
// Added error messages with ErrorString
// Updated to DirectDraw7
// Added use of ErrorLogger
// Added drawline function
// Added fill circle function
// Moved Colour constants inside the class as static constants
// More secure - better defensive programming
// Version 10.1
//	Changed to singleton

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")
#pragma once

#include <ddraw.h>		// directX draw
#include "mypicture.h"
#include "errorlogger.h"
#include "vector2d.h"

// Macros ***************************************************
#define MAX_CLIP_RECTS 10

// Colour system
#define _RGB565(r,g,b)  ((((b>>3)%32)) + (((g>>2)%64)<<5) + (((r>>3)%32)<<11))
#define _XRGB(r,g,b) ((r<<16) + (g<<8) +b)

// The class spec *******************************************

// This class provides a simple set of graphics functions that
// use directX for a computer game, using 16-bit graphics.
// The functions are organised in a class for convenience, rather
// than for OO principles.
// Only one instance of this class should appear in your code - otherwise
// you will be trying to have two Direct Draws running - each with their 
// own primary and secondary surface.
// Good OO should have this implemented as a singleton class, but I want
// to keep things simple, so I am just going to trust you not to
// try to create two MyScreens.

class MyDrawEngine 
{
	friend MyPicture;		// To allow MyPicture fast access to directdraw

private:
	USHORT *videoAddress;	// Pointer to start of video buffer,

		// Postcondition:	The primary surface, the buffer, the clipper and DirectDraw have been released.
		// Returns:			SUCCESS
	ErrorType Release();

	static MyDrawEngine* instance;
		// Instance of this singleton

		// Precondition:	A window for the application has been created
		//					DirectDraw has not already been initialised.
		// Postcondition:	A DirectDraw2 interface has been created.
		//					The screen has been put into full-screen, exclusive mode.
		//					The primary surface and the back buffer have been initialised and cleared.
		// Parameters:
		//		width		The pixel width of the screen (in UNN NT labs, you are restricted to 800)
		//		height		The pixel height of the screen (in UNN NT labs, you are restricted to 600)
		//		depth		The colour depth of the screen (bits per pixel - in NT labs, use 16)
		//		hwnd		The handle to the application's window.
	MyDrawEngine(int width, int height, int depth, HWND hwnd, bool bFullScreen);

		// Singleton destructor - calls "Release()"
	~MyDrawEngine();	

	// Public attributes ************************************
	//   Lots of public attributes - it means this object is
	//   less encapsulated, but this works faster. OO principles
	//   are a lot less important than speed in a computer game.

	HWND mHwnd;								// The handle to the window
	LPDIRECTDRAWSURFACE7 lpPrimarySurface;
	LPDIRECTDRAWSURFACE7 lpBackBuffer;
	DDSURFACEDESC2 ddsd;					// Surface "order form"
	IDirectDraw7* lpdd;						// Pointer to direct draw
	int memoryPitch;
	LPDIRECTDRAWCLIPPER lpClipper;
	LPDIRECTDRAWCLIPPER lpBackBufferClipper; //For windowed mode

public:
	static const int BLACK16 = 0;
	static const int RED16 = _RGB565(255,0,0);
	static const int GREEN16 = _RGB565(0,255,0);
	static const int BLUE16 = _RGB565(0,0,255);
	static const int DARKRED16 = _RGB565(128,0,0);
	static const int DARKGREEN16 = _RGB565(0,128,0);
	static const int DARKBLUE16 = _RGB565(0,0,128);
	static const int LIGHTRED16 = _RGB565(255,128,128);
	static const int LIGHTGREEN16 = _RGB565(128,255,128);
	static const int LIGHTBLUE16 = _RGB565(128,128,255);
	static const int WHITE16 = RED16+GREEN16+BLUE16;
	static const int YELLOW16 = RED16+GREEN16;
	static const int CYAN16 = BLUE16+GREEN16;
	static const int PURPLE16 = RED16+BLUE16;
	static const int GREY16 = DARKRED16+DARKBLUE16+DARKGREEN16;

	static const int BLACK32 = 0;
	static const int RED32 = _XRGB(255,0,0);
	static const int GREEN32 = _XRGB(0,255,0);
	static const int BLUE32 = _XRGB(0,0,255);
	static const int DARKRED32 = _XRGB(128,0,0);
	static const int DARKGREEN32 = _XRGB(0,128,0);
	static const int DARKBLUE32 = _XRGB(0,0,128);
	static const int LIGHTRED32 = _XRGB(255,128,128);
	static const int LIGHTGREEN32 = _XRGB(128,255,128);
	static const int LIGHTBLUE32 = _XRGB(128,128,255);
	static const int WHITE32 = RED32+GREEN32+BLUE32;
	static const int YELLOW32 = RED32+GREEN32;
	static const int CYAN32 = BLUE32+GREEN32;
	static const int PURPLE32 = RED32+BLUE32;
	static const int GREY32 = DARKRED32+DARKBLUE32+DARKGREEN32;

	int screenWidth;
	int screenHeight;
	int bytesPerPixel;

	bool mbFullScreen;


	// Public methods ***************************************
	// Yes, that's right - I've made nearly everything public
	// We are games programmers - we need speed, and we trust ourselves.

	// Precondition:	A window for the application has been created
	// Postcondition:	An instance of MyDrawEngine is created and a pointer to it has been
	//					returned.
	//					If a previous instance already exists, this is terminated first.
	//					The screen has been put into full-screen, exclusive mode.
	//					The primary surface and the back buffer have been initialised and cleared.
	// Parameters:
	//		width		The pixel width of the screen (in UNN NT labs, you are restricted to 800)
	//		height		The pixel height of the screen (in UNN NT labs, you are restricted to 600)
	//		depth		The colour depth of the screen (bits per pixel - in NT labs, use 16)
	//		hwnd		The handle to the application's window.
	// Note you should call this static method using MyDrawEngine::Start() before using
	// any other methods of this class.
	static MyDrawEngine* Start(int width, int height, int depth, HWND hwnd, bool bFullScreen);

	// Postcondition:	The instance of MyDrawEngine has been terminated.
	// Returns:			SUCCESS If the instance of MyDrawEngine had been started using Start()
	//					FAILURE if the instance of MyDrawEngine had not been started.
	// Note that you should call this at the end of your game to avoid a memory leak.
	static ErrorType Terminate();

		// Precondition:	shutdown() has not been called
		//					Neither primary nor buffer is locked.
		// Postcondition:	Primary surface and the back buffer have been flipped.
		//					(function will wait until flip is possible)
		// Returns:			SUCCESS
	ErrorType Flip();

		// Postcondition:	A pointer to the instance of MyDrawEngine has been returned.
	// Call this using "MyDrawEngine enginePtr = MyDrawEngine::GetInstance();"
	static MyDrawEngine* GetInstance();

		// Preconditions	thePicture has been initialised to contain an image
		//					destinationRect and sourceRect are valid structures
		//					with values that have been initialised
		// Postcondition	A part of the image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The part of the image in "theSurface" is specified by
		//					sourceRect. If the values of sourceRect extend beyond the
		//					edges of the image in theSurface, the sourceRect will be clipped
		//					to the edges of the image. The location of the destination of the image
		//					is specified by destinationRect. The image will be stretched and scaled
		//					to fit into the destinationRect.
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType Blit( RECT& destinationRect,  RECT& sourceRect, MyPicture *thePicture);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the x,y coordinates specified
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(int x, int y, MyPicture *thePicture);


		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the x,y coordinates specified
		//					The height and width of the image will be scaled according to the
		//					scale sent. (A negative scale will cause the blit to fail.)
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(int x, int y, MyPicture *thePicture, double scale);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the x,y coordinates specified
		//					The height and width of the image will be scaled according to the
		//					height and width sent. (Negative values will cause the blit to fail.)
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(int x, int y, MyPicture *thePicture, int height, int width);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the vector specified
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(Vector2D centre, MyPicture *thePicture);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole of thePicture will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the vector2D specified
		//					The height and width of the image will be scaled according to the
		//					scale sent. (A negative scale will cause the blit to fail.)
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(Vector2D centre, MyPicture *thePicture, double scale=1.0);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The part of the image in thePicture defined by sourceRect will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the vector2D specified
		//					The height and width of the image will be scaled according to the
		//					scale sent. (A negative scale will cause the blit to fail.)
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(Vector2D centre, RECT& sourceRect, MyPicture *thePicture, double scale=1.0);

		// Preconditions	thePicture has been initialised to contain an image
		// Postcondition	The whole image in theSurface will be placed
		//					on the back buffer. (Subject to clipping.)
		//					The centre of the image will be placed at the vector2D specified
		//					The height and width of the image will be scaled according to the
		//					height and width sent. (Negative values will cause the blit to fail.)
		//	Returns			SUCCESS if blit successful. FAILURE otherwise.
	ErrorType DrawAt(Vector2D centre, MyPicture *thePicture, int height, int width);

		// Postcondition	A rectangle in the back buffer will be filled with the specified
		//					colour. (Subject to clipping.) x1 and y1 specify the top left
		//					corner of the rectangle on the back buffer to be filled. x2 and
		//					y2 specify the bottom right corner of the rectangle.
		// Returns			SUCCESS if fill successful. FAILURE otherwise
	inline ErrorType FillRect( RECT& destinationRect, unsigned int colour);

		// Precondition		clipList points to an array of rects, and
		//					numRects is the number of elements of the array
		// Postcondition	The back buffer's clip list will be set to match
		//					the rectangles sent to this method. The previous
		//					clip list will be cleared.
		// Returns			SUCCESS if clip list accepted. FAILURE otherwise
	ErrorType SetClipper(int numRects, LPRECT clipList);

		// Postcondition	The back buffer is locked, to allow direct 
		//					manipulation of the surface.
		// Returns			SUCCESS if lock successful. FAILURE otherwise
	ErrorType LockBackSurface();

		// Postcondition	The back buffer is unlocked, to return control
		//					of the surface to directX
		// Returns			SUCCESS if unlock successful. FAILURE otherwise
	ErrorType UnlockBackSurface();

		// Precondition		The back buffer is locked.
		// Postcondition	A point of the specified colour has been
		//					plotted at x1,y1 on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if the surface is not locked,
	inline ErrorType DrawPoint(int x1, int y1, unsigned int colour);

		// Precondition		The back buffer is locked.
		// Postcondition	A point of the specified colour has been
		//					plotted at x1,y1 on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if the surface is not locked,
	inline ErrorType DrawPoint(Vector2D point, unsigned int colour);

		// Precondition		The back buffer is locked.
		// Returns			an integer indicating the colour of the requested point on the screen
		// Notes			This function will give an invalid answer if x,y is not on the screen.
	unsigned int MyDrawEngine::GetPoint(int x, int y);

		// Precondition		The back buffer is locked.
		// Postcondition	A line between (x1, y1) and (x2, y2)
		//					has been plotted on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if the surface is not locked,
	ErrorType DrawLine(int x1, int y1, int x2, int y2, unsigned int colour);

			// Precondition		The back buffer is locked.
		// Postcondition	A line between start and end
		//					has been plotted on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if the surface is not locked,
	ErrorType DrawLine(const Vector2D& start, const Vector2D& end,  unsigned int colour);

		// Precondition		The back buffer is locked.

		//					A circle with the specified radius will completely fit on the screen
		// Postcondition	A circle centred on (x1,y1) with the radius "radius" has been
		//					filled on the screen with the specified colour
		//					has been plotted on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if you have forgotten to Lock()
	ErrorType FillCircle(int x1, int y1, int radius, unsigned int colour);

		// Precondition		The back buffer is locked.
		//					centre specifies a point on the screen
		//					A circle with the specified radius will completely fit on the screen
		// Postcondition	A circle centred on centre with the radius "radius" has been
		//					filled on the screen with the specified colour
		//					has been plotted on the back buffer.
		// Returns			SUCCESS
		// Notes			This function will crash your computer into
		//					next week if you have forgotten to Lock()
	ErrorType FillCircle(const Vector2D& centre, int radius, unsigned int colour);

		// Postcondition	The back buffer is cleared (all black)
		// Returns			SUCCESS if successful FAILURE otherwise.
	ErrorType ClearBackBuffer();

		// Returns			SUCCESS if the device is still valid or if it was successfully reaquired
		//					FAILURE if the screen is unavailable
	ErrorType Validate();


		// This method writes text to the screen at the specified coordinates.
		// IMPORTANT: This function is slow. Use your own text engine.
		// Parameters:
		//	x			X-coordinate to write to
		//	y			Y-Coordinate to write to
		//	text		A null-terminated string of text to write
		// Returns			SUCCESS if the write was successful
		//					FAILURE if the write was unsuccessful
	ErrorType WriteText(int x, int y, char text[]);


	ErrorType WriteInt(int num, int x, int y);
	ErrorType WriteDouble(double num, int x, int y);
		// Functions to write numbers to the screen
		// Slow and ugly - just for debugging really.

	// Returns a string describing the directDraw error for most HRESULTs sent to it
	static char* ErrorString(HRESULT err);

	// Returns a bool that returns true if the game is displayed in full screen mode
	// or false if the game is in windowed mode
	inline bool IsWindowFullScreen(void) const;

};	// End of class definition

// **************************************************************

inline ErrorType MyDrawEngine::FillRect(RECT& destinationRect, unsigned int colour)
{

	DDBLTFX ddbltfx;	// FX order form

	memset(&ddbltfx,0,sizeof(ddbltfx));
	ddbltfx.dwSize=sizeof(ddbltfx);


	// set FX to the colour requested
	ddbltfx.dwFillColor = colour; 


	// Fill in the surface
	HRESULT err=lpBackBuffer->Blt(&destinationRect, 
			   NULL,							// nothing to copy from            
			   NULL,							// nothing to copy from
			   DDBLT_COLORFILL | DDBLT_WAIT,	// fill and wait for complete
			   &ddbltfx);						// the order form
	if(FAILED(err))
	{
		ErrorLogger::Writeln("Could not fill a rect");
		ErrorLogger::Writeln(ErrorString(err));
		return FAILURE;
	}

	return SUCCESS;
}



// **************************************************************

inline ErrorType MyDrawEngine::DrawPoint(int x1, int y1, unsigned int colour)
{
	if(x1>=0 && y1>=0 && x1<screenWidth && y1<screenHeight)
	{
		*(ULONG*)(videoAddress+x1*bytesPerPixel/2+y1*memoryPitch)=colour;
		return SUCCESS;
	}
	else 
		return FAILURE;
}

// **************************************************************

inline ErrorType MyDrawEngine::DrawPoint(Vector2D point, unsigned int colour)
{
	return DrawPoint(int(point.XValue), int(point.YValue), colour);
}

// ****************************************************************

inline bool MyDrawEngine::IsWindowFullScreen(void) const
{
	return mbFullScreen;
}

