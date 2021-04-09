#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Tileset.h"
#include "StateMachine.h"

class TSGround : public GameObject
{
public:
	TSGround();
	~TSGround();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override; 
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
private:
	Tileset			m_Tileset;
	int				m_YOffset;
	StateMachine	m_StateMachine;
};
