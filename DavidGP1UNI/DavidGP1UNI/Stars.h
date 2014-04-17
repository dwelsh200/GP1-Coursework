#ifndef __STAR__
#define __STAR__
#include "vector2D.h"
#include "mydrawengine.h"



class Stars
{
private:
	Vector2D m_position;
	RECT m_source, m_dest;
	

	//Current sprite being used
	int m_state;
	// Deley between changes of state
	int m_delay;
	// Counting down delay t state change
	int m_counter;
	//increase dest rect by this value
	int m_scale;

	MyPicture *m_image;

public:
	Stars();
	void Init(int _state, Vector2D _position, int _delay, int _scale, MyPicture* _image);
	void Update();
	void Draw();
	void Terminate();


};




#endif
