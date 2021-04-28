#include "CallOfMonsters.h"
#include "Collision.h"
#include "SpriteController.h"
#include "Timer.h"

CallOfMonsters::CallOfMonsters()
{
}

CallOfMonsters::~CallOfMonsters()
{
}

void CallOfMonsters::Init(GameEngine * ge)
{
	m_GE = ge;
	LoadSpriteTextures();
}

void CallOfMonsters::Update(double deltaTime)
{
	bool spawnLeft = (bool)(rand() % 2);
	if (m_EnemySpawnTimer.TimeUp() && m_ThePlayer->m_StateMachine.GetCurrentState() != "dead")
	{
		int groundHeight = 490; // from top
		Vector2 enemyPos;
		int enemyW = 564 / 2;
		int enemyH = 215 / 2;
		enemyPos[1] = groundHeight - enemyH;

		int rightB =  m_GE->GetScreenWidth();
		spawnLeft ? enemyPos[0] = -enemyW : enemyPos[0] = rightB;

		SpawnEnemy(enemyPos, 2);
		m_EnemySpawnTimer.Start(2200);
	}

	CollisionResolution();
	UpdateEnemy();
}

void CallOfMonsters::Render()
{
}

void CallOfMonsters::HandleInput(const SDL_Event & event, double deltaTime)
{
}

void CallOfMonsters::SpawnBullet(const Vector2 & pos, int speed)
{
	Bullet* bullet = new Bullet(pos, 384 / 20, 320 / 20, speed);
	m_GE->AddGameObjectBuffer(bullet);
	m_Bullets.push_back(bullet);
}

void CallOfMonsters::SpawnEnemy(const Vector2 & pos, int speed)
{
	SDL_Renderer* renderer = m_GE->GetRenderer();
	/*enemy sprites*/
	/*
	Sprite* enemySpriteIdle = new Sprite("res/img/Monster/RedSlimeSheets/RedSlimeIdleSheet.png",
		renderer, "idle", 564, 25, false, 25);
	Sprite* enemySpriteRun = new Sprite("res/img/Monster/RedSlimeSheets/RedSlimeWalkSheet.png",
		renderer, "run", 564, 21, false, 25);
	Sprite* enemySpriteHurt = new Sprite("res/img/Monster/RedSlimeSheets/RedSlimeHurtSheet.png",
		renderer, "hurt", 564, 25, true, 25);
	Sprite* enemySpriteDie = new Sprite("res/img/Monster/RedSlimeSheets/RedSlimeDieSheet.png",
		renderer, "dying", 564, 25, true, 25);
	*/
	Sprite* enemySpriteIdle = new Sprite(m_Idle, "idle", 564, 25, false, 25);
	Sprite* enemySpriteRun = new Sprite(m_Run, "run", 564, 21, false, 25);
	Sprite* enemySpriteHurt = new Sprite(m_Hurt, "hurt", 564, 25, true, 25);
	Sprite* enemySpriteDie = new Sprite(m_Die, "dying", 564, 25, true, 25);

	SpriteController* enemySprite = new SpriteController;
	enemySprite->AddSprite(enemySpriteIdle);
	enemySprite->AddSprite(enemySpriteRun);
	enemySprite->AddSprite(enemySpriteHurt);
	enemySprite->AddSprite(enemySpriteDie);

	/*the enemy*/
	int groundHeight = 490; // from top
	int enemyW = 564 / 2;
	int enemyH = 215 / 2;
	Vector2 enemyPos(100, groundHeight - enemyH);
	EnemyCOM* enemy = new EnemyCOM(pos, enemyW, enemyH);
	enemy->m_SpriteController = enemySprite;

	m_GE->AddGameObjectBuffer(enemy);
	m_Enemies.push_back(enemy);
}

void CallOfMonsters::CollisionResolution()
{
	int enemyHitOffsetX = 60, enemyHitOffsetX2 = 140;
	//std::cout << "Bla\n";
	for (Bullet* b : m_Bullets)
	{
		if (b->m_StateMachine.GetCurrentState() != "fired") continue;
		// check against all the enemies
		for (EnemyCOM* enm : m_Enemies)
		{
			std::string enemyState = enm->m_StateMachine.GetCurrentState();
			if (enemyState == "dead" || enemyState == "dying") continue;
			Vector2 enmHitboxPos = enm->m_Position;
			enmHitboxPos[0] += enemyHitOffsetX;

			if (Collision::DetectRectCollision({ b->m_Position, b->m_Width, b->m_Height },
				{ enmHitboxPos, enm->m_Width-enemyHitOffsetX2, enm->m_Height }))
			{
				//std::cout << "Hit an enemy!\n";
				
				enm->m_Hitpoint--;
				if (enm->m_Hitpoint <= 0)
				{
					m_TheHUD->AddScore(5);
					// dead
					enm->m_StateMachine.TransitionTo("dying");
				}
				else
				{
					m_TheHUD->AddScore(1);
					// hurt but not dead
					enm->m_StateMachine.TransitionTo("hurt");
					if (enemyState == "hurt")
						enm->m_SpriteController->ResetSprite("hurt"); // play the hurt animation from the start
				}
				b->m_StateMachine.TransitionTo("hitenemy");
			}
		}
	}
	// collision with the player
	for (EnemyCOM* enm : m_Enemies)
	{
		std::string enemyState = enm->m_StateMachine.GetCurrentState();
		if (enemyState == "dead" || enemyState == "dying") continue;
		int enemyHitOffsetX = 60, enemyHitOffsetX2 = 140;
		Vector2 enmHitboxPos(enm->m_Position.X() + enemyHitOffsetX, enm->m_Position.Y());

		if (Collision::DetectRectCollision({ m_ThePlayer->m_Position, m_ThePlayer->m_Width, 
			m_ThePlayer->m_Height }, { enmHitboxPos, enm->m_Width - enemyHitOffsetX2, enm->m_Height }))
		{
			if (enemyState != "hurt")
			{
				enm->m_StateMachine.TransitionTo("idle");
				enm->m_IdleTimer.Start(1000);
			}
			//std::cout << "hit the player\n";
			if (m_ThePlayer->m_HurtTimer.TimeUp())
			{
				std::string playerState = m_ThePlayer->m_StateMachine.GetCurrentState();
				if(m_ThePlayer->m_Hitpoint > 0) m_ThePlayer->m_Hitpoint--;
				//std::cout << "Health - 1\n";
				//std::cout << "health: " << m_ThePlayer->m_Hitpoint << std::endl;
				m_TheHUD->LostLife();
				if (playerState != "dead" || playerState != "dying")
				{
					if (m_ThePlayer->m_Hitpoint <= 0)
					{
						//std::cout << "Dead\n";
						m_ThePlayer->m_StateMachine.TransitionTo("dying");
						m_ThePlayer->m_Hurt = false;
						continue;
					}
				}

				m_ThePlayer->m_Hurt = true;
				m_ThePlayer->m_HurtTimer.Start(2000);//hurt agian after this time
			}

		}
	}
}

void CallOfMonsters::UpdateEnemy()
{
	for (EnemyCOM* enm : m_Enemies)
	{
		enm->m_PlayerPositionX = m_ThePlayer->m_Position.X();
	}
}

void CallOfMonsters::LoadSpriteTextures()
{
	m_Idle = new Texture("res/img/Monster/RedSlimeSheets/RedSlimeIdleSheet.png", m_GE->GetRenderer());
	m_Run = new Texture("res/img/Monster/RedSlimeSheets/RedSlimeWalkSheet.png", m_GE->GetRenderer());
	m_Hurt = new Texture("res/img/Monster/RedSlimeSheets/RedSlimeHurtSheet.png", m_GE->GetRenderer());
	m_Die = new Texture("res/img/Monster/RedSlimeSheets/RedSlimeDieSheet.png", m_GE->GetRenderer());
}
