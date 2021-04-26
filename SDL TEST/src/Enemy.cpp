#include "Enemy.h"

Enemy::Enemy(const Vector2& pos, int width, int height)
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

Enemy::~Enemy()
{
}

void Enemy::Init(GameEngine * ge)
{
	SetupStateMachine();
}

void Enemy::Update(double deltaTime)
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

void Enemy::Render()
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

void Enemy::HandleInput(const SDL_Event & event, double deltaTime)
{
	//Enemies dont need input
}

void Enemy::SetupStateMachine()
{
	m_StateMachine.AddTransition("idle", "run");
	m_StateMachine.AddTransition("run", "idle");
	
	m_StateMachine.AddTransition("idle", "hurt");
	m_StateMachine.AddTransition("hurt", "idle");

	m_StateMachine.AddTransition("run", "hurt");
}
