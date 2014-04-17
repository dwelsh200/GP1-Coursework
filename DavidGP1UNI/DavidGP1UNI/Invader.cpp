#include "Invader.h"



void Invader::Init(MyPicture* _image, Vector2D _position)
{

	m_position = _position;
	m_image = _image;



	m_source.top = 0;
	m_source.left = 0;
	m_source.right = 64;
	m_source.bottom = 64;

	m_velocity.XValue = 1;
	m_velocity.YValue = 0;

	m_alive = true;
}

void Invader::Update()
{
	if (m_alive)
	{
	m_position += m_velocity;


	m_dest.top = 0 + m_position.YValue;
	m_dest.left = 0 + m_position.XValue;
	m_dest.right = 64 + m_position.XValue;
	m_dest.bottom = 64 + m_position.YValue;
	}

	if (m_position.YValue >= 960 && m_alive)
			{
				MyDrawEngine::GetInstance()->WriteText(510, 510, "Game Over");
			}
}

void Invader::Draw()
{
	if (m_alive)
	{
	MyDrawEngine::GetInstance()->Blit(m_dest, m_source, m_image);
	}
}

void Invader::MoveDown()
{
	if (m_alive)
	{
	m_position.YValue += 64;
	}
}

void Invader::ChangeDirection()
{
	if (m_alive)
	{

	if(m_velocity.XValue > 0)
	{
		m_velocity.XValue = -1;
	}

	else
	{
		m_velocity.XValue = 1;
	}

	}
}

bool Invader::AtScreenEdge()
{
	if (m_alive)
	{

	if((m_position.XValue <0 )||(m_position.XValue > 960))
	{
		return true;
	}
	}
	return false;
	
}
