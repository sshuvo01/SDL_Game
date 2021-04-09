#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"
#include "StateMachine.h"
#include "SpriteController.h"
#include <iostream>

class PlayerNew : public GameObject
{
public:
	enum class FaceDirection
	{
		RIGHT = 1,
		LEFT = -1
	};

	PlayerNew(const Vector2& pos, int width, int height);
	~PlayerNew();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override; 
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public members*/
	Sprite*				m_RunSprite;
	Sprite*				m_IdleSprite;
	SpriteController*	m_SpriteController;
private:
	Vector2				m_Position;
	int					m_Width, m_Height;
	StateMachine		m_StateMachine;
	FaceDirection		m_FaceDirection;
	/*private functions*/
	void SetupStateMachine();
};
