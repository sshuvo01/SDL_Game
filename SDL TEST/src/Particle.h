#pragma once
#include "Vector2.h"
#include "Texture.h"
#include "Core.h"

class Particle
{
public:
	Particle();
	~Particle();

	void Init(int lifetime, const Vector2& position, const Vector2& velocity, int widthHeight);
	void Update(const Vector2& extraVelocity = Vector2());
	void Render();
	inline void SetTexture(Texture* texture) { m_TextureP = texture; }
	inline bool IsAlive() const { return m_Lifetime > 0; }
private:
	Vector2				m_Position, m_Velocity;
	int					m_Width, m_Height, m_Lifetime, m_Life;
	Texture*			m_TextureP = nullptr;
	/*private functions*/
};
