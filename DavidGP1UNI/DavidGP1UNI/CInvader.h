#ifndef __CINVADER__
#define  __CINVADER__
#include "Invader.h"
#include "mysound.h"
#include "mydrawengine.h"



#define NUM_ROWS 4
#define NUM_COLS 10

class CInvader
{
private:
	Invader m_invaders[NUM_COLS][NUM_ROWS];
	MySound* m_explosion;



public:

	void Init(MyPicture* _image, MySound* _explode);
	void Update();
	bool CheckCollision(Vector2D _position);
	bool GameOver();
	void Draw();
	
	void Terminate();

	



};






#endif