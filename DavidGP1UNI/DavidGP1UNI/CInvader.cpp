#include "CInvader.h"





void CInvader::Init(MyPicture* _image, MySound* _explode)
{

	Vector2D pos(0,0);
	m_explosion = _explode;

	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			m_invaders[j][i].Init(_image, pos);
			pos.XValue += 64;


		}
		pos.XValue = 0;
		pos.YValue += 64;
	}

}
void CInvader::Update()
{
	bool changeDir = false;
	bool Endgame = false;
	//checks each invader for reaching the edge of screen
	//sets change direction if any have reached edge
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			if (m_invaders[j][i].AtScreenEdge())
			{
				changeDir = true;
			}
			


		}
	}
	
	
	
	//updates invader, and changes direction and moves down if changeDir is true
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{

			if(changeDir ==true)
			{
				m_invaders[j][i].ChangeDirection();
				m_invaders[j][i].MoveDown();

			}

			m_invaders[j][i].Update();
			


		}
	}


	//game over if invader touches bottom
		for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			if (m_invaders[j][i].m_position.YValue >= 690)
			{
				MyDrawEngine::GetInstance()->WriteText(480, 380, "Game Over");
				MyDrawEngine::GetInstance()->WriteText(450, 400, "Press ESC to Quit");
				bool EndGame = true;
				GameOver();
			}
			


		}
	}


}
void CInvader::Draw()
{
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			m_invaders[j][i].Draw();
			


		}
	}
}

bool CInvader::CheckCollision(Vector2D _position)
{
	//check each invader in grid
	for (int i=0; i<NUM_COLS; i++)
	{
		for (int j=0; j<NUM_ROWS; j++)
		{
			//if invader alive, check for collision
			if(m_invaders[i][j].m_alive)
			{
				if(_position.YValue < m_invaders[i][j].m_dest.bottom &&
					_position.YValue > m_invaders[i][j].m_dest.top &&
					_position.XValue > m_invaders[i][j].m_dest.left &&
					_position.XValue < m_invaders[i][j].m_dest.right)
				{
					//invader has been shot, remove invader, and play sound
					m_explosion->Stop();
					m_explosion->Play(0);
					//PlayerShip::Player1->Vibrate(65535, 0);
					m_invaders[i][j].m_alive = false;
					return true;
				}
				//Player1->Vibrate();
			}
		}
	}

	return false;

}

bool CInvader::GameOver()
{

	
	
		//MyDrawEngine::GetInstance()->WriteText(100, 100, "working");
		return true;

	





}

void CInvader::Terminate()
{

}