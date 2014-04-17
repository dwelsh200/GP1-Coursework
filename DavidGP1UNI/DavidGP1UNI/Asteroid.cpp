#include "Asteroid.h"

void Asteroid::Init(int _state, int _scale, MyPicture* _image, Vector2D _position)
{
	if(_state >=0 && _state <4)
	{
		m_state = _state;
	}
	else
	{
	m_state = 0;
	}





	//+(4*m_state)

	m_scale = _scale;
	m_position = _position;
	m_image = _image;

	//for asteroidsbit.bmp
	/*m_source.top = 0;
	m_source.left = 0+(4*m_state);
	m_source.right = 128+(4*m_state);
	m_source.bottom = 128;*/



	//for asteroidsbithalf.bmp
	m_source.top = 0;
	m_source.left = 0+(4*m_state);
	m_source.right = 64+(4*m_state);
	m_source.bottom = 64;

	
	//m_dest.top = 0 + m_position.YValue;
	//m_dest.left = 0 + m_position.XValue;
	//m_dest.right = 64 + m_position.XValue + m_scale;
	//m_dest.bottom = 64 + m_position.YValue + m_scale;


	//m_image.LoadBitmapA("Images\\asteroidsbit.bmp");

	//to move asteroid down?
	//m_velocity.XValue = 0;
	//m_velocity.YValue = 1;
	
}

void Asteroid::Update()
{
	//m_scale = 0;
	////just for now

	//m_dest.top = 0 + m_position.YValue;
	//m_dest.left = 0 + m_position.XValue;
	//m_dest.right = 128 + m_position.XValue + m_scale;
	//m_dest.bottom = 128 + m_position.YValue + m_scale;



	//int m_delayStart;
	//int m_counter;
	//int _delayStart;
	//m_delayStart = _delayStart;
	//counter = _delayStart;



	/*int counter;
	counter = 0;


	if(counter <=2)
	{
		counter++;
	}
	else
	{*/

	for (int i=1 ; i<100000 ; i++) ;

	Vector2D temp(0,1);
	m_position = m_position + temp;

	
	//m_counter = m_delayStart;
	//}


}

void Asteroid::Draw()
{

	//just for now
	//for asteroidsbit.bmp
	//m_dest.top = 0 + m_position.YValue;
	//m_dest.left = 0 + m_position.XValue;
	//m_dest.right = 128 + m_position.XValue + m_scale;
	//m_dest.bottom = 128 + m_position.YValue + m_scale;

	//for asteroidsbithalf.bmp
	m_dest.top = 0 + m_position.YValue;
	m_dest.left = 0 + m_position.XValue;
	m_dest.right = 64 + m_position.XValue + m_scale;
	m_dest.bottom = 64 + m_position.YValue + m_scale;


	MyDrawEngine::GetInstance()->Blit(m_dest, m_source, m_image);
}

void Asteroid::MoveDirection()
{
	//moving down just now

}

void Asteroid::Terminate()
{
	
}



