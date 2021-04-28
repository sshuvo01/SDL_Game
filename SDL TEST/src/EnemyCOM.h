#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Vector2.h"
#include "SpriteController.h"
#include "StateMachine.h"
#include <ctime>
#include "Timer.h"

class EnemyCOM : public GameObject
{
public:
	EnemyCOM(const Vector2& pos, int width, int height);
	~EnemyCOM();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public  data*/
	SpriteController*		m_SpriteController = nullptr;
	StateMachine			m_StateMachine, m_FaceDirection;
	Vector2					m_Position;
	int						m_Width, m_Height, m_ScreenWidth, m_ScreenHeight;
	int						m_PlayerPositionX, m_Hitpoint;
	Timer					m_IdleTimer;
	bool					m_HitPlayer;
private:
	/*private functions*/
	bool BecomeIdle() const;
	void SetupStateMachine();
};

