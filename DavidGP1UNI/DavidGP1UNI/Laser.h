#ifndef __LASER__
#define __LASER__
#include "vector2D.h"
#include "mydrawengine.h"
#include "CInvader.h"



class Laser
{
private:
	Vector2D m_position;
	CInvader* m_invaders;

public:
	Laser(CInvader *_invaders);
	void Init(Vector2D _shipPos);
	bool Update();
	void Draw();
	void Terminate();


};





#endif
