#include "CStar.h"

CStar::CStar(int _numStars, int _maxScaleVar)
{

	m_num = _numStars;
	m_maxScale = _maxScaleVar;

	int numberCreated = 0;

	m_stars = new Stars[m_num];

//how fast star twinkle
	m_delay = 5;



}


void CStar::Init(MyPicture* _image)
{
	int initial;
	Vector2D pos;
	int scale;

	for(int i=0; i<m_num; i++)
	{
		initial = rand() %5;

		pos.XValue = rand() % 1024;
		pos.YValue = rand() % 768;

		if(m_maxScale == 0)
		{
			m_maxScale = 1;
		}

		scale = 0 + rand() % m_maxScale;

		m_stars[i].Init(initial, pos, m_delay, scale, _image);

	}

}
void CStar::Update()
{
	for(int i=0; i<m_num; i++)
	{
		m_stars[i].Update();
	}
}
void CStar::Draw()
{
	for(int i=0; i<m_num; i++)
	{
		m_stars[i].Draw();
	}
}
void CStar::Terminate()
{
	for(int i=0; i<m_num; i++)
	{
		m_stars[i].Terminate();
	}
}