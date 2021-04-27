#pragma once

#include "GameEngine.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "SpriteController.h"
#include <iostream>
#include "CallOfMonsters.h"
#include "Timer.h"

class CallOfMonsters;

class PlayerCOM : public GameObject
{
public:
	PlayerCOM(const Vector2& pos, int width, int height);
	~PlayerCOM();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public members*/
	SpriteController*	m_SpriteController = nullptr;
	Vector2				m_Position;
	int					m_Width, m_Height;
	StateMachine		m_StateMachine, m_FaceDirection;
	CallOfMonsters*		m_GameControl;
private:
	int				m_ScreenWidth, m_ScreenHeight;
	Timer			m_BlinkTimer;
	/*private functions*/
	void SetupStateMachine();
	void CheckBoundary();
	bool BlinkRender();
};

