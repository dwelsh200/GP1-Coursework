#include "CAsteroids.h"

CAsteroids::CAsteroids(int _numAsteroid, int _maxScaleVar, int _delayStart)
{

	m_num = _numAsteroid;
	m_maxScale = _maxScaleVar;

	int numberCreated = 0;

	m_asteroid = new Asteroid[m_num];

//how fast star twinkle
	m_delay = 5;

	m_delayStart = _delayStart;
	m_counter = _delayStart;


}


void CAsteroids::Init(MyPicture* _image)
{
	int initial;
	Vector2D pos;
	int scale;

	for(int i=0; i<m_num; i++)
	{
		initial = rand() %5;

		pos.XValue = rand() % 1024;
		pos.YValue = -64;

		if(m_maxScale == 0)
		{
			m_maxScale = 1;
		}

		scale = 0 + rand() % m_maxScale;

		m_asteroid[i].Init(initial, scale, _image, pos);

	}

}
void CAsteroids::Update()
{

	//--m_counter;


	/*if(m_counter <=0)
	{*/

		for(int i=0; i<m_num; i++)
	{
	//	if(m_counter <=0)
	//{



		for (int D=1 ; D<100000 ; D++) ;


		m_asteroid[i].Update();




		//m_counter = m_delayStart;
	//}
	
		

		//m_counter = m_delayStart;

	}



	/*for(int i=0; i<m_num; i++)
	{
		m_asteroid[i].Update();
	}*/
}
void CAsteroids::Draw()
{
	

	for(int i=0; i<m_num; i++)
	{
		

		for (int i=1 ; i<100 ; i++) ;

		m_asteroid[i].Draw();
		
	}
		

	
}
void CAsteroids::Terminate()
{
	for(int i=0; i<m_num; i++)
	{
		m_asteroid[i].Terminate();
	}
}