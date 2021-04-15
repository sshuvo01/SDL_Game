#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"
#include "StateMachine.h"
#include "PlayerNew.h"

class CircularBG : public GameObject
{
public:
	CircularBG(const std::string& texturePath, int movementSpeed);
	~CircularBG();
	
	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	PlayerNew*		m_Player;
private:
	Texture			m_Texture;
	std::string		m_TexturePath;
	SDL_Renderer*	m_Renderer;
	int				m_ScreenWidth, m_ScreenHeight;
	int				m_SrcWidth, m_SrcHeight;
	int				m_MovementSpeed;
	int				m_SrcXOffset, m_SrcYOffset;
	bool			m_Moving;
	StateMachine	m_StateMachine;
	/*private functions*/
	void DebugRect(const SDL_Rect& rect) const;
};

