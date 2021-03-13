#include "Player.h"
#include <iostream>


void Player::SetupStateMachine()
{
	m_StateMachine.AddTransition("idle", "run");
	m_StateMachine.AddTransition("run", "idle");

	m_StateMachine.AddTransition("run", "goup");
	m_StateMachine.AddTransition("idle", "goup");
	
	m_StateMachine.AddTransition("goup", "godown");
	m_StateMachine.AddTransition("godown", "idle");
}

void Player::CheckObstacleHit(Obstacle * checkHit, Obstacle * placeIfHit)
{
	if (
		Collision::DetectRectCollision({ m_Position, m_Width, m_Height },
			{ checkHit->m_Position, checkHit->m_Width, checkHit->m_Height })
		)
	{
		std::cout << "HIT" << std::endl;
		
		if (!placeIfHit) return;
		int offset = 1;
		int deltaX = m_JumpRight ? placeIfHit->m_Width + offset : -m_Width - offset;
		Vector2 newPos(placeIfHit->m_Position.X() + deltaX, 
			m_Position.Y());
		ChangePosition(newPos);
	}
}


Player::Player(const Vector2& pos, int width, int height)
	: m_Position(pos), 
	m_Width(width), 
	m_Height(height), 
	m_Texture(),
	m_Renderer(NULL),
	m_StateMachine("idle")
{
	m_GroundHeight = m_Position[1] + m_Height;
	m_JumpRight = true;
	m_ObstacleRight = nullptr;
	m_BluBarLeft = nullptr;
	m_Ground = nullptr;
}

Player::~Player()
{
}

void Player::Init(GameEngine * ge)
{
	m_Renderer = ge->GetRenderer();
	m_ScreenWidth = ge->GetScreenWidth();
	m_ScreenHeight = ge->GetScreenHeight();
	
	std::string texturePath = "res/img/pacman.png";
	SDL_Rect rect{ m_Position[0], m_Position[1], m_Width, m_Height };
	m_Texture.LoadTexture(texturePath, m_Renderer, rect);

	SetupStateMachine();

	m_Ground->m_Position[0] = 0;
	m_Ground->m_Position[1] = m_GroundHeight;
	m_Ground->m_Width = m_ScreenWidth;
	m_Ground->m_Height = m_ScreenHeight -m_GroundHeight;
}

void Player::Update(double deltaTime)
{
	int jumpHeight = 200;
	int stp = 2;
	int stpX = 1;
	
	if (m_StateMachine.GetCurrentState() == "goup")
	{
		m_Position[1] -= stp;
		m_JumpRight ? m_Position[0] += stpX : m_Position[0] -= stpX;
		if (m_GroundHeight - m_Position[1] - m_Height > jumpHeight)
		{
			m_StateMachine.TransitionTo("godown");
		}
	}
	if (m_StateMachine.GetCurrentState() == "godown")
	{
		m_Position[1] += stp;
		m_JumpRight ? m_Position[0] += stpX : m_Position[0] -= stpX;
		if (m_Position[1] + m_Height > m_GroundHeight)
		{
			//hit the ground!
			m_Position[1] = m_GroundHeight - m_Height;
			if (m_StateMachine.TransitionTo("idle"))
			{
				std::cout << "hit ground and idle" << std::endl;
			}
		}
	}

	CheckObstacleHit(m_ObstacleRight, m_BluBarLeft);
	CheckObstacleHit(m_BluBarLeft, m_ObstacleRight);
	CheckBoundary();
}

void Player::Render()
{
	m_Texture.SetRect({m_Position[0], m_Position[1], m_Width, m_Height});
	SDL_RendererFlip flip = m_JumpRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(m_Renderer, m_Texture.GetTexture(), NULL, m_Texture.GetRect(), 0.0,
		NULL, flip);
}

void Player::HandleInput(const SDL_Event & event, double deltaTime)
{
	int stp = 12;

	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		if (event.type == SDL_KEYDOWN)
		{
			m_StateMachine.TransitionTo("goup"); 
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
			if (m_StateMachine.TransitionTo("run"))
				DeltaPosition(Vector2(stp, 0));
			m_JumpRight = true;
			break; 
		}
		if (event.type == SDL_KEYUP)
		{
			if (m_StateMachine.GetCurrentState() != "godown")
				m_StateMachine.TransitionTo("idle");
			break;
		}
		break;
	case SDLK_a:
		if (event.type == SDL_KEYDOWN) 
		{ 
			if (m_StateMachine.TransitionTo("run"))
				DeltaPosition(Vector2(-stp, 0));
			m_JumpRight = false;
			break; 
		}
		if (event.type == SDL_KEYUP)
		{
			if(m_StateMachine.GetCurrentState() != "godown")
				m_StateMachine.TransitionTo("idle");
			break;
		}
		break;
	default:
		break;
	}
}

void Player::CheckBoundary()
{
	if (m_Position[0] < 0) m_Position[0] = 0;
	if (m_Position[1] < 0) m_Position[1] = 0;
	
	if (m_Position[0] + m_Width > m_ScreenWidth)  m_Position[0] = m_ScreenWidth - m_Width;
	if (m_Position[1] + m_Height> m_ScreenHeight) m_Position[1] = m_ScreenHeight - m_Height;
}

void Player::ChangePosition(const Vector2& newPos)
{
	m_Position = newPos;
}

void Player::DeltaPosition(const Vector2& step, double deltaTime)
{
	m_Position += step;
}
