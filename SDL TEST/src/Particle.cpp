#include "Particle.h"
#include <iostream>

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Init(int lifetime, const Vector2& position, const Vector2& velocity,
	int widthHeight)
{
	m_Lifetime = lifetime;
	m_Position = position;
	m_Velocity = velocity;
	m_Width = widthHeight;
	m_Height = widthHeight;

	m_Life = m_Lifetime;
}

void Particle::Update(const Vector2& extraVelocity)
{
	if (!IsAlive()) return;

	m_Position += m_Velocity + extraVelocity;
	//m_Velocity = velocity;
}

void Particle::Render()
{
	if (!IsAlive()) return;
	double ratio = (double)m_Lifetime / (double)m_Life;
	//std::cout << (int) (255.0 * ratio) << std::endl;
	//std::cout << "Life time: " << m_Lifetime << std::endl;

	SDL_SetTextureAlphaMod(m_TextureP->GetTexture(), (Uint8) (255.0 * ratio));
	if (m_TextureP) m_TextureP->RenderCopy({ m_Position.X(), m_Position.Y(), m_Width, m_Height });
	m_Lifetime--;
	// reduce the size
	if (m_Width > 2) m_Width--;
	if (m_Height > 2) m_Height--;
}
