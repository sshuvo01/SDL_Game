#pragma once
#include "GameEngine.h"
#include "Texture.h"
#include "Vector2.h"
#include <vector>
#include "PlayerNew.h"
#include "StateMachine.h"
#include "ParticleEmitter.h"

class Coins : public GameObject
{
public:
	Coins(int groundHeight);
	~Coins();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	/*public members*/
	PlayerNew*			m_Player = nullptr;
	ParticleEmitter*	m_CollectParticle = nullptr;
	ParticleEmitter*	m_HurtParticle = nullptr;
private:
	struct ACoin
	{
		Vector2 position;
		bool	active = true;
	};
	Texture				m_Texture, m_TextureBomb;
	Vector2				m_BombPosition;
	bool				m_BombActive = true;
	int					m_width, m_Height;
	std::vector<ACoin>	m_Coins;
	StateMachine		m_StateMachine;
};

