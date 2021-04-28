#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Texture.h"
#include "Bullet.h"
#include "PlayerCOM.h"
#include "Vector2.h"
#include "EnemyCOM.h"
#include "Timer.h"
#include "HUD.h"

class PlayerCOM;

class CallOfMonsters : public GameObject
{
public:
	CallOfMonsters();
	~CallOfMonsters();

	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
	//
	void SpawnBullet(const Vector2& pos, int speed);
	void SpawnEnemy(const Vector2& pos, int speed);
	/*private data*/
	PlayerCOM*		m_ThePlayer = nullptr;
	HUD*			m_TheHUD = nullptr;
private:
	GameEngine*					m_GE = nullptr;
	std::vector<Bullet*>		m_Bullets;
	std::vector<EnemyCOM*>		m_Enemies;
	Timer						m_EnemySpawnTimer;
	Texture						*m_Idle = nullptr, *m_Run = nullptr, *m_Hurt = nullptr, *m_Die = nullptr;
	/*private functions*/
	void CollisionResolution();
	void UpdateEnemy();
	void LoadSpriteTextures();
};

