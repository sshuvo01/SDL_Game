#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"

class Ground : public GameObject
{
private:

	SDL_Renderer*	m_Renderer;
	Texture			m_Texture;
public:
	Vector2			m_Position;
	int				m_Width;
	int				m_Height;

	Ground(const Vector2& pos, int width, int height);
	~Ground();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
};

