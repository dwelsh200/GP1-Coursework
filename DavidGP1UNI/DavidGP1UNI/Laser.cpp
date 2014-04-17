#include "Laser.h"
#include "myinputs.h"
#include "mydrawengine.h"


Laser::Laser(CInvader *_invaders)
{
	m_invaders = _invaders;

}

void Laser::Init(Vector2D _shipPos)
{
	Vector2D temp(74,0);
	m_position = _shipPos + temp;

}
//returns true if bullet still alive
bool Laser::Update()
{
	Vector2D temp(0,-5);//speed of laser
	m_position += temp;

	if(m_invaders->CheckCollision(m_position))
	{
		return false;
	}


	return true;


}

void Laser::Draw()
{
	Vector2D start(m_position.XValue ,m_position.YValue);
	Vector2D end(m_position.XValue ,m_position.YValue -20);//length of laser
	MyDrawEngine::GetInstance()->LockBackSurface();
	MyDrawEngine::GetInstance()->DrawLine(end, start, MyDrawEngine::RED32);
	start.XValue += 1;
	end.XValue += 1;//thickness of laser
	MyDrawEngine::GetInstance()->DrawLine(end, start, MyDrawEngine::RED32);
	MyDrawEngine::GetInstance()->UnlockBackSurface();

}

void Laser::Terminate()
{

}
