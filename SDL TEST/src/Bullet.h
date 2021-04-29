#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "Vector2.h"
#include "StateMachine.h"

class Bullet : public GameObject
{
public:
	Bullet(Vector2 pos, int width, int height, int speed, Texture* texture);
	~Bullet();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public variables*/
	StateMachine	m_StateMachine;
	Vector2			m_Position;
	int				m_Width, m_Height, m_ScreenWidth, m_ScreenHeight;
private:
	int				m_Speed = 0;
	Texture*		m_Texture;

	/*private functions*/
	void SetupStateMachine();
};

