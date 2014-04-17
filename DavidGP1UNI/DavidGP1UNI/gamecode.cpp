// GameCode.cpp		Version 11			5/3/08	
// These three functions form the basis of a game loop in the window created in the
// wincode.cpp file

#include "gamecode.h"
#include "mydrawengine.h"
#include "mypicture.h"
#include "mysoundengine.h"
#include "mysound.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "PlayerShip.h"
#include "CStar.h"
#include "CAsteroids.h"
#include "CInvader.h"



MyDrawEngine* pTheDrawEngine;	// A pointer to the drawing engine
MySoundEngine* pTheSoundEngine;	// A pointer to the sound engine
MyInputs* pTheInputs;

extern HWND gHwnd;				// A handle to the main window application (created and declared in wincode.cpp).
extern HINSTANCE g_hinstance;	// A handle to the program instance

// Your global objects ***********************************************************************






PlayerShip* Xwing;
//CAsteroids* asteroids;
CStar* stars;
MyPicture* starPic;
//MyPicture* asteroidPic;

//SOUNDS
MySound* laserEffect;
MySound* explosion;
//MySound* Theme;


//Invaders
CInvader* invaders;
MyPicture* invaderPic;







// Your global functions *********************************************************************
//MySound* pSoundObject;


// The game !!! *********************************************************************************

ErrorType GameInit(bool bFullScreen)
// Called once before entering game loop. 
// Use this function to set up the program
// gHwnd is the handle to the window and is required by the constructors for the engines
{
	// Create the engines - this should be done before creating other DDraw objects
	pTheDrawEngine = MyDrawEngine::Start(SCREENWIDTH, SCREENHEIGHT, COLOURDEPTH, gHwnd, bFullScreen);
	pTheSoundEngine = MySoundEngine::Start(gHwnd);
	pTheInputs = MyInputs::Start(g_hinstance, gHwnd);
	
	








	//asteroidPic = new MyPicture;
	//asteroidPic->LoadBitmapA("Images\\asteroidsbithalf.bmp");



	//(number of asteroids, max scale var, speed of asteroid? or 0 moves all or 1 moves 1)
	//asteroids = new CAsteroids(10,1, 0);
	//asteroids->Init(asteroidPic);
	
	//Theme = new MySound();
	//Theme->LoadWave("   ");


	laserEffect = new MySound();
	laserEffect->LoadWave("Sounds\\xwingwav.wav");

	explosion = new MySound();
	explosion->LoadWave("Sounds\\explosionwav.wav");

	starPic = new MyPicture;
	starPic->LoadBitmapA("Images\\star.bmp");


	invaderPic = new MyPicture;
	invaderPic->LoadBitmapA("Images\\tiefighterbit1.bmp");
	//"Images\\tiefighterbit1.bmp"
	//"Images\\asteroidsbithalf.bmp"
	
	
	invaders = new CInvader();
	invaders->Init(invaderPic, explosion);

	//numberof stars, scale no.




	Xwing = new PlayerShip(invaders, laserEffect);
	Xwing->Init();

	stars = new CStar(200,5);
	stars->Init(starPic);







    
    
    return (SUCCESS);
// ******************************************************************
}

ErrorType GameMain()
// Called repeatedly - the game loop
{
	//  validation routine - should be able to alt-tab out of program
	// (Done in game main just to show that it needs to be done - better to do in MyDrawEngine. really)
	if(pTheDrawEngine->Validate()==FAILURE) return FAILURE;

    //CODE GOES HERE




	//Old non dynamic background

	//MyPicture Background;
	//Background.LoadBitmapA("Images\\SpaceBackgroundbit.bmp");

	//RECT source, dest;

	//source.top = 0;
	//source.left = 0;
	//source.right = 1024;
	//source.bottom = 768;

	//dest.top = 0;
	//dest.left = 0;
	//dest.right = 1024;
	//dest.bottom = 768;
	//
	//MyDrawEngine::GetInstance()->Blit(dest, source, &Background);
	//


	stars ->Update();
	stars ->Draw();

	Xwing->Update();
	Xwing->Draw();


	invaders->Update();
	invaders->Draw();

	//if (invaders->GameOver() == true)
	//{
	//	GameShutdown();
	//}

	//asteroids->Update();
	//asteroids->Draw();



    //Flip and clear the back buffer
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();
	return SUCCESS;
}

// ***********************************************************

void GameShutdown()
// called after the game loop is finished
{ 
	Xwing->Terminate();
	delete Xwing;
	stars ->Terminate();
	delete stars;
	starPic->Release();
	delete starPic;

	invaders->Terminate();
	delete invaders;

	invaderPic->Release();
	delete invaderPic;

	delete laserEffect;
	delete explosion;
	//asteroidPic->Release();
	//delete asteroids;


    // (engines must be terminated last)
	pTheDrawEngine->Terminate();
	pTheSoundEngine->Terminate();
	pTheInputs->Terminate();   
}



