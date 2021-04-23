#include "CallOfMonsters.h"

CallOfMonsters::CallOfMonsters()
{
}

CallOfMonsters::~CallOfMonsters()
{
}

void CallOfMonsters::Init(GameEngine * ge)
{
	m_GE = ge;
}

void CallOfMonsters::Update(double deltaTime)
{
}

void CallOfMonsters::Render()
{
}

void CallOfMonsters::HandleInput(const SDL_Event & event, double deltaTime)
{
}

void CallOfMonsters::SpawnBullet(const Vector2 & pos, int speed)
{
	Bullet* bullet = new Bullet(pos, 384 / 16, 320 / 16, speed);
	m_GE->AddGameObjectBuffer(bullet);
	m_Bullets.push_back(bullet);
}
