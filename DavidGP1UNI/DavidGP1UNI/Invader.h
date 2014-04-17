#ifndef __INVADER__
#define __INVADER__
#include "vector2D.h"
#include "mydrawengine.h"


class Invader
{
private:
		Vector2D m_velocity;

		

		
		
		MyPicture *m_image;
		

public:
		void Init( MyPicture* _image, Vector2D _position);

		RECT m_source, m_dest;

		Vector2D m_position;

		void Update();

		void Draw();

		void MoveDown();

		void ChangeDirection();

		bool AtScreenEdge();

		bool m_alive;
	
};

#endif