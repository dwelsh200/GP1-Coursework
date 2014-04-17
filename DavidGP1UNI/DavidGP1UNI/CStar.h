#ifndef __CStar__
#define __CStar__
#include "Stars.h"


class CStar
{
	private:
		int m_num;
		int m_maxScale;
		int m_delay;

		Stars* m_stars;


	public:
		CStar(int _numStars, int _maxScaleVar);
		void Init(MyPicture* _image);
		void Update();
		void Draw();
		void Terminate();


};




#endif