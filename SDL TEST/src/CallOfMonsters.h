#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "Bullet.h"
#include "PlayerCOM.h"
#include "Vector2.h"

class CallOfMonsters : public GameObject
{
public:
	CallOfMonsters();
	~CallOfMonsters();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	void SpawnBullet(const Vector2& pos, int speed);
private:
	GameEngine*					m_GE = nullptr;
	std::vector<Bullet*>		m_Bullets;
};

