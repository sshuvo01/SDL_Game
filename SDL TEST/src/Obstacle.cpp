#include "Obstacle.h"

Obstacle::Obstacle(const Vector2& pos, int width, int height)
	: m_Position(pos.X(), pos.Y()), 
	m_Texture(),
	m_Width(width), 
	m_Height(height), 
	m_Renderer(NULL)
{
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init(GameEngine * ge)
{
	m_Renderer = ge->GetRenderer();
	std::string path = "res/img/portal.png";
	m_Texture.LoadTexture(path, m_Renderer, {m_Position[0], m_Position[1], m_Width, m_Height});
}

void Obstacle::Update(double deltaTime)
{
}

void Obstacle::Render()
{
	SDL_RenderCopy(m_Renderer, m_Texture.GetTexture(), NULL, m_Texture.GetRect());
}

void Obstacle::HandleInput(const SDL_Event & event, double deltaTime)
{
}
