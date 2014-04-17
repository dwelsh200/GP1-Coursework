#ifndef __ASTEROID__
#define __ASTEROID__
#include "vector2D.h"
#include "mydrawengine.h"


class Asteroid
{
private:
		Vector2D m_velocity;

		Vector2D m_position;

		RECT m_source, m_dest;
		
		MyPicture *m_image;
		int m_state;

		int m_scale;
		//set @ 0 just now. option to change scale of asteroid?

public:
		void Init(int _state, int _scale, MyPicture* _image, Vector2D _position);

		void Update();

		void Draw();

		void MoveDirection();

		void Terminate();
};








#endif
