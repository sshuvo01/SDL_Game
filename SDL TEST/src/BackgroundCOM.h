#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"
#include "StateMachine.h"

class BackgroundCOM : public GameObject
{
public:
	BackgroundCOM();
	~BackgroundCOM();
	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
private:
	Texture			m_Texture;
	SDL_Renderer*	m_Renderer;
	/**/
	int				m_ScreenWidth, m_ScreenHeight;
};

