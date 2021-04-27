#include "PlayerCOM.h"

PlayerCOM::PlayerCOM(const Vector2& pos, int width, int height)
	:m_StateMachine("idle"),
	m_FaceDirection("right"),
	m_Position(pos),
	m_Width(width),
	m_Height(height)
{
	SetupStateMachine();
}

PlayerCOM::~PlayerCOM()
{
}

void PlayerCOM::Init(GameEngine * ge)
{
	m_ScreenWidth = ge->GetScreenWidth();
	m_ScreenHeight = ge->GetScreenHeight();
}

void PlayerCOM::Update(double deltaTime)
{
	int speed = 3;
	if (m_StateMachine.GetCurrentState() == "run")
	{
		if (m_FaceDirection.GetCurrentState() == "right")
		{
			m_Position[0] += speed;
		}
		else
		{
			m_Position[0] -= speed;
		}
	}
	CheckBoundary();
}

void PlayerCOM::Render()
{
	std::string currentState = m_StateMachine.GetCurrentState();
	SDL_Rect dstRect = { m_Position.X(), m_Position.Y(), m_Width, m_Height };
	bool flipHorizontally = m_FaceDirection.GetCurrentState() == "right" ? false : true;

	if (!BlinkRender()) return;
	/*
	static bool swtch = true;
	swtch = !swtch;
	if (!swtch)
	{
		return;
	}
	*/
	if (currentState == "idle")
	{
		m_SpriteController->Play("idle", dstRect, flipHorizontally);
	}
	else if (currentState == "run")
	{
		m_SpriteController->Play("run", dstRect, flipHorizontally);
	}
	else if (currentState == "shoot")
	{
		bool playedOnce = m_SpriteController->PlayOnce("shoot", dstRect, flipHorizontally);
		if(playedOnce) m_StateMachine.TransitionTo("idle");
	}
}

void PlayerCOM::HandleInput(const SDL_Event & event, double deltaTime)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		if (event.type == SDL_KEYDOWN)
		{
			// shoot
			
			int speed = 10;
			Vector2 bulletOffset;
			bulletOffset[1] = 50;
			bulletOffset[0] = -5;

			if (m_FaceDirection.GetCurrentState() == "right")
			{
				// right
				bulletOffset[0] += m_Width;
			}
			else
			{
				// left
				speed *= -1;
			}

			std::string currentState = m_StateMachine.GetCurrentState();

			if (!m_StateMachine.HasTransition(currentState, "shoot"))
			{
				break;
			}

			if(currentState != "shoot")
				m_GameControl->SpawnBullet(m_Position + bulletOffset, speed);
			m_StateMachine.TransitionTo("shoot");
		}
		if (event.type == SDL_KEYUP)
		{
		}
		break;
	case SDLK_d:
		if (event.type == SDL_KEYDOWN)
		{
			if (m_StateMachine.GetCurrentState() == "run")
			{
				m_StateMachine.TransitionTo("idle");
				break;
			}
			bool b = m_StateMachine.TransitionTo("run");
			if (b) m_FaceDirection.TransitionTo("right");
		}
		if (event.type == SDL_KEYUP)
		{
			// move right
		}
		break;
	case SDLK_a:
		if (event.type == SDL_KEYDOWN)
		{
			//m_StateMachine.TransitionTo("idle");
			if (m_StateMachine.GetCurrentState() == "run")
			{
				m_StateMachine.TransitionTo("idle");
				break;
			}
			bool b = m_StateMachine.TransitionTo("run");
			if (b) m_FaceDirection.TransitionTo("left");
		}
		if (event.type == SDL_KEYUP)
		{
		}
		break;
	default:
		break;
	}
}

void PlayerCOM::SetupStateMachine()
{
	m_StateMachine.AddTransition("idle", "run");
	m_StateMachine.AddTransition("run", "idle");

	m_StateMachine.AddTransition("idle", "shoot");
	m_StateMachine.AddTransition("shoot", "idle");

	/*face direction*/
	m_FaceDirection.AddTransition("right", "left");
	m_FaceDirection.AddTransition("left", "right");
}

void PlayerCOM::CheckBoundary()
{
	if (m_Position[0] < 0) m_Position[0] = 0;
	if (m_Position[1] < 0) m_Position[1] = 0;

	if (m_Position[0] + m_Width > m_ScreenWidth)  m_Position[0] = m_ScreenWidth - m_Width;
	if (m_Position[1] + m_Height > m_ScreenHeight) m_Position[1] = m_ScreenHeight - m_Height;
}

bool PlayerCOM::BlinkRender()
{
	static int blinker = 6;
	if (m_BlinkTimer.TimeUp())
	{
		blinker--;
		if (blinker <= 0)
		{
			m_BlinkTimer.Start(200);
			blinker = 5;
		}
		return false;
	}

	return true;
}
