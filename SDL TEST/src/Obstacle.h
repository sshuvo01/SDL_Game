#pragma once

#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"

class Obstacle : public GameObject
{
private:
	Texture			m_Texture;
	SDL_Renderer*	m_Renderer;
public:
	Vector2			m_Position;
	int				m_Width;
	int				m_Height;

	Obstacle(const Vector2& pos, int width, int height);
	~Obstacle();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override; 
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
};
