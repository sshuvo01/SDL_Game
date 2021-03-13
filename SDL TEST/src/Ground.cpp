#include "Ground.h"

Ground::Ground(const Vector2& pos, int width, int height)
	: m_Position(pos), 
	m_Width(width), 
	m_Height(height), 
	m_Renderer(NULL), 
	m_Texture()
{
}

Ground::~Ground()
{
}

void Ground::Init(GameEngine * ge)
{
	m_Renderer = ge->GetRenderer();
	std::string path = "res/img/ground.png";
	m_Texture.LoadTexture(path, m_Renderer, { m_Position[0], m_Position[1], m_Width, m_Height });
}

void Ground::Update(double deltaTime)
{
}

void Ground::Render()
{
	m_Texture.SetRect({ m_Position[0], m_Position[1], m_Width, m_Height });
	SDL_RenderCopy(m_Renderer, m_Texture.GetTexture(), NULL, m_Texture.GetRect());
}

void Ground::HandleInput(const SDL_Event & event, double deltaTime)
{
}

