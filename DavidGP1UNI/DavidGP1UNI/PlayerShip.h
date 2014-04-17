#ifndef __PLAYER_SHIP__
#define __PLAYER_SHIP__
#include "vector2D.h"
#include "mydrawengine.h"
#include "CInvader.h"
#include "mysound.h"

//xinput test
#include "CXBOXController.h"
#include <iostream>





class Laser;


class PlayerShip
{
private:
	Vector2D m_position;

	RECT m_source, m_dest;
	MyPicture m_image;
	CInvader* m_invaders;
	Laser* m_laser;
	MySound* m_sound;

public:
	PlayerShip(CInvader *_invaders, MySound* _shoot);
	void Init();
	void Update();
	void Draw();
	void Terminate();


};





#endif
