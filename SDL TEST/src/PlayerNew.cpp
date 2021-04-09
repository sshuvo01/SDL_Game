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
		if(m_SpriteController) m_SpriteController->Play("run", dstRect, flipHorizontally);
		//m_RunSprite->PlayAnimation(dstRect);
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
	default:
		break;
	}
}

void PlayerNew::SetupStateMachine()
{
	m_StateMachine.AddTransition("idle", "run");
	m_StateMachine.AddTransition("run", "idle");
}
