#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "Vector2.h"
#include "StateMachine.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector2 pos, int width, int height, int speed);
	~Bullet();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public variables*/

private:
	StateMachine	m_StateMachine;
	int				m_Speed = 0;
	Vector2			m_Position;
	int				m_Width, m_Height, m_ScreenWidth, m_ScreenHeight;
	Texture			m_Texture;
};

