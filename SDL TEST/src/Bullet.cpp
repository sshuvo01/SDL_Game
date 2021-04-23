#include "Bullet.h"
#include "Collision.h"

Bullet::Bullet(Vector2 pos, int width, int height, int speed)
	:m_Position(pos),
	m_Width(width),
	m_Height(height),
	m_Speed(speed),
	m_StateMachine("fired")
{
	m_StateMachine.AddTransition("fired", "hitboundary");
	m_StateMachine.AddTransition("fired", "hitenemy");
}

Bullet::~Bullet()
{
}

void Bullet::Init(GameEngine * ge)
{
	m_Texture.LoadTexture("res/img/bullets/bullet3.png", ge->GetRenderer());
	m_ScreenWidth = ge->GetWidth();
	m_ScreenHeight = ge->GetHeight();
}

void Bullet::Update(double deltaTime)
{
	if (Collision::DetectXBoundaryCollision(
		{ m_Position, m_Width, m_Height }, 0, m_ScreenWidth))
	{
		// hit the boundary
		m_StateMachine.TransitionTo("hitboundary");
	}
	std::string currentState = m_StateMachine.GetCurrentState();
	
	if (currentState == "fired")
	{
		m_Position[0] += m_Speed; // m_Speed can be positive or negative
	}
}

void Bullet::Render()
{
	if (m_StateMachine.GetCurrentState() != "fired") return;
	SDL_Rect dstRect = { m_Position.X(), m_Position.Y(), m_Width, m_Height };
	m_Speed < 0 ? m_Texture.RenderCopyHFlip(dstRect) : m_Texture.RenderCopy(dstRect);
}

void Bullet::HandleInput(const SDL_Event & event, double deltaTime)
{
}

