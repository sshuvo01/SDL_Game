#include "PlayerNew.h"

PlayerNew::PlayerNew(const Vector2& pos, int width, int height)
	:m_StateMachine("idle"),
	m_RunSprite(nullptr),
	m_IdleSprite(nullptr),
	m_SpriteController(nullptr),
	m_Position(pos),
	m_Width(width),
	m_Height(height),
	m_FaceDirection(FaceDirection::RIGHT)
{
}

PlayerNew::~PlayerNew()
{
}

void PlayerNew::Init(GameEngine * ge)
{
	SetupStateMachine();
}

void PlayerNew::Update(double deltaTime)
{
	int speed = 1;
	if (m_StateMachine.GetCurrentState() == "run")
	{
		if (m_FaceDirection == FaceDirection::RIGHT)
		{
			//m_Position[0] += speed;
		}
		else
		{
			//m_Position[0] -= speed;
		}
	}
}

void PlayerNew::Render()
{
	SDL_Rect dstRect = { m_Position[0], m_Position[1], m_Width, m_Height };
	bool flipHorizontally = (m_FaceDirection == FaceDirection::LEFT) ? true : false;

	

	if (m_StateMachine.GetCurrentState() == "idle")
	{
		//m_IdleSprite->PlayAnimation(dstRect);
		if(m_SpriteController) m_SpriteController->Play("idle", dstRect, flipHorizontally);
	}
	else if (m_StateMachine.GetCurrentState() == "run")
	{
		if (m_SpriteController)
		{
			if (m_SpriteController) m_SpriteController->Play("run", dstRect, flipHorizontally);
			//bool playedLast = m_SpriteController->PlayOnce("run", dstRect, flipHorizontally);
			/*if (playedLast)
			{
				//std::cout << "The end of a sprite\n";
			}
			else
			{
				std::cout << "This is not the end\n";
			}
			*/
		}
		//m_RunSprite->PlayAnimation(dstRect);
	}
	else if (m_StateMachine.GetCurrentState() == "hurt")
	{
		bool playedLast = m_SpriteController->PlayOnce("hurt", dstRect, flipHorizontally);
		if (playedLast)
		{
			m_StateMachine.TransitionTo("idle");
		}
	}
}

void PlayerNew::HandleInput(const SDL_Event & event, double deltaTime)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_a:
		if (event.type == SDL_KEYDOWN)
		{
			//std::cout << "Pressed A\n";
			if (m_StateMachine.GetCurrentState() == "run")
			{
				if (m_FaceDirection == FaceDirection::RIGHT)
				{
					m_FaceDirection = FaceDirection::LEFT;
				}
				else
				{
					m_StateMachine.TransitionTo("idle");
				}
			}
			else
			{
				m_StateMachine.TransitionTo("run");
			}
			m_FaceDirection = FaceDirection::LEFT;
			break;
		}
		if (event.type == SDL_KEYUP)
		{

			break;
		}
		break;
	case SDLK_d:
		if (event.type == SDL_KEYDOWN)
		{
			if (m_StateMachine.GetCurrentState() == "run")
			{
				if (m_FaceDirection == FaceDirection::LEFT)
				{
					// change direction
					m_FaceDirection = FaceDirection::RIGHT;
				}
				else
				{
					m_StateMachine.TransitionTo("idle");
				}
			}
			else
			{
				m_StateMachine.TransitionTo("run");
			}
			m_FaceDirection = FaceDirection::RIGHT;
			break;
		}
		if (event.type == SDL_KEYUP)
		{
			//std::cout << "Released D" << "\n";
			//m_StateMachine.TransitionTo("idle");
			//m_RunSprite->ResetFrames();
			break;
		}
		break;
	case SDLK_w:
		if (event.type == SDL_KEYDOWN)
		{
			m_StateMachine.TransitionTo("hurt");
		}
		break;
	default:
		break;
	}
}

void PlayerNew::SetupStateMachine()
{
	m_StateMachine.AddTransition("idle", "run");
	m_StateMachine.AddTransition("run", "idle");
	
	m_StateMachine.AddTransition("idle", "hurt");
	m_StateMachine.AddTransition("hurt", "idle");

	m_StateMachine.AddTransition("run", "hurt");
}
