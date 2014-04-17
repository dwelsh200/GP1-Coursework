#include "Stars.h"


Stars::Stars()
{
	

}

void Stars::Init(int _state, Vector2D _position, int _delay, int _scale, MyPicture* _image)
{
	if(_state >=0 && _state <5)
	{
		m_state = _state;
	}
	else
	{
	m_state = 0;
	}
	m_position = _position;
	m_delay = _delay ;
	m_counter = _delay;
	m_scale = _scale;

	//m_image.LoadBitmapA("Images\\star.bmp");

	
	m_source.top = 0;
	m_source.left = 0+(5*m_state);
	m_source.right = 5+(5*m_state);
	m_source.bottom = 5;

	m_dest.top = 0 + m_position.YValue;
	m_dest.left = 0 + m_position.XValue;
	m_dest.right = 5 + m_position.XValue + m_scale;
	m_dest.bottom = 5 + m_position.YValue + m_scale;

	m_image = _image;




}
void Stars::Update()
{
	--m_counter;


	if(m_counter <=0)
	{

		++m_state;


		if(m_state > 4)
		{
		m_state = 0;
		}
	
		m_source.top = 0;
		m_source.left = 0+(5*m_state);
		m_source.right = 5+(5*m_state);
		m_source.bottom = 5;

		m_counter = m_delay;

	}
}
void Stars::Draw()
{
	//m_dest.top = 0 + m_position.YValue;
	//m_dest.left = 0 + m_position.XValue;
	//m_dest.right = 5 + m_position.XValue + m_scale;
	//m_dest.bottom = 5 + m_position.YValue + m_scale;

	MyDrawEngine::GetInstance()->Blit(m_dest, m_source, m_image);
}
void Stars::Terminate()
{
	
}

