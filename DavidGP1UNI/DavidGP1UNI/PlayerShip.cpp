#include "PlayerShip.h"
#include "myinputs.h"
#include "Laser.h"
#include "gamecode.h"

//xbox test
CXBOXController* Player1;


PlayerShip::PlayerShip(CInvader *_invaders, MySound* _shoot)
{
	m_sound = _shoot;
	m_invaders = _invaders;
	m_laser = NULL;
}


void PlayerShip::Init()
{
	//xbox test
	Player1 = new CXBOXController(1);






	//set starting position
	m_position.set(462,635);

	m_image.LoadBitmapA("Images\\xwingbit.bmp");
	//tiefighterbit
	//xwingbit
	m_source.top = 0;
	m_source.left = 0;
	m_source.right = 148;
	m_source.bottom = 122;

	
}

void PlayerShip::Update()
{
	//Get Keyboard state
	MyInputs::GetInstance()->SampleKeyboard();
	
	Vector2D temp(2,0);

	//Check Keyboard for left or right movement
	if((MyInputs::GetInstance()->KeyPressed(DIK_A))||(MyInputs::GetInstance()->KeyPressed(DIK_LEFT)) || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)))
	{
		if(m_position.XValue > 4)
		{
		m_position = m_position - temp;
		}
	}

	else if((MyInputs::GetInstance()->KeyPressed(DIK_D))||(MyInputs::GetInstance()->KeyPressed(DIK_RIGHT))   || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)))
	{
		if(m_position.XValue < 875)
		{
		m_position = m_position + temp;
		}
	}

	////for vertical movement
	//Vector2D tempV(0,2);

	////Check Keyboard for up or down movement
	//if((MyInputs::GetInstance()->KeyPressed(DIK_W))||(MyInputs::GetInstance()->KeyPressed(DIK_UP)))
	//{
	//	m_position = m_position - tempV;

	//}

	//else if((MyInputs::GetInstance()->KeyPressed(DIK_S))||(MyInputs::GetInstance()->KeyPressed(DIK_DOWN)))
	//{
	//	m_position = m_position + tempV;
	//}


	
	//fire laser
			if(MyInputs::GetInstance()->KeyPressed(DIK_SPACE)   || ((Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A))   || ((Player1->GetState().Gamepad.bRightTrigger )))  // if space bar pressed fire laser
	{
		m_sound->Stop();
		m_sound->Play();
		Player1->Vibrate(65535, 65535);
		m_laser = new Laser(m_invaders);
		m_laser->Init(m_position);


	}

	Player1->Vibrate();
	 




			//update laser
	if(m_laser &&!m_laser->Update())
	{
		Player1->Vibrate(65535,0);
		delete m_laser;
		m_laser = NULL;

	}

	
	Player1->Vibrate();


}

void PlayerShip::Draw()
{
	



	m_dest.top = 0 + m_position.YValue;
	m_dest.left = 0 + m_position.XValue;
	m_dest.right = 148 + m_position.XValue;
	m_dest.bottom = 122 + m_position.YValue;

	MyDrawEngine::GetInstance()->Blit(m_dest, m_source, &m_image);


	//draw laser
	if(m_laser)
	{
		m_laser->Draw();

	}
}


void PlayerShip::Terminate()
{
	m_image.Release();
}
