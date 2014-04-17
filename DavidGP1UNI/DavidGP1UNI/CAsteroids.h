#ifndef __CAsteroids__
#define __CAsteroids__
#include "Asteroid.h"


class CAsteroids
{
	private:
		int m_num;
		int m_maxScale;
		int m_delay;
		int m_delayStart;
		// Counting down delay t state change
		int m_counter;

		Asteroid* m_asteroid;
		//Stars* m_stars;

	public:
		CAsteroids(int _numAsteroid, int _maxScaleVar, int _delayStart);
		void Init(MyPicture* _image);
		void Update();
		void Draw();
		void Terminate();


};




#endif