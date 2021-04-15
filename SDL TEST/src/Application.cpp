#include <iostream>
#include <string>

#include "Core.h"
#include "Texture.h"
#include "TexturesSlider.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Player.h"
#include "Vector2.h"
#include "Obstacle.h"
#include "CircularBG.h"
#include "Sprite.h"
#include "PlayerNew.h"
#include "TSGround.h"
#include <map>
#include "SpriteController.h"
#include "ParticleEmitter.h"
#include "Coins.h"

int main()
{
	/**/
	/*
	GameEngine theGE;
	Player* thePlayer = new Player({ 2, 300 }, 60, 60);
	Obstacle* lb = new Obstacle({ 140, 280 }, 30, 80);
	Obstacle* rb = new Obstacle({ 800, 280 }, 30, 80);
	Ground* gr = new Ground({ 0, 0 }, 100, 100);

	thePlayer->m_BluBarLeft = lb;
	thePlayer->m_ObstacleRight = rb;
	thePlayer->m_Ground = gr;

	theGE.AddGameObject(thePlayer);
	theGE.AddGameObject(lb);
	theGE.AddGameObject(rb);
	theGE.AddGameObject(gr);

	theGE.Run();
	*/
	/*
	double Y[3] = { 1.1, 1.1, 1.1 };
	float delta[3] = { 0.1f, 0.1f, 0.1f };
	size_t i = Y[0] / delta[0]; // i=10
	size_t j = (float)Y[1] / (float)delta[1]; // j=11
	size_t k = (double)Y[1] / (double)delta[1]; // k=10

	std::cout << i << " " << j << " " << k << std::endl;
	std::cin.get();
	if (1.1 + 2.2 == 3.3)
	{
		std::cout << "asdf";
	}
	
	{
		std::map<char, int> first;

		first['a'] = 10;
		first['a'] = 20;
		first['b'] = 30;
		first['c'] = 50;
		first['d'] = 70;

		std::cout << first.count('e') << std::endl;

		std::cin.get();
	}
	*/
	GameEngine theGameEngine;
	SDL_Renderer* renderer = theGameEngine.GetRenderer();
	
	int groundHeight = 490; // from top
	/*sprites*/
	Sprite runSprite("res/img/Run_Sprite.png", renderer, "run", 384, 7);
	Sprite idleSprite("res/img/Idle_Sprite.png", renderer, "idle", 384, 10);
	Sprite hurtSprite("res/img/Hurt_Sprite.png", renderer, "hurt", 384, 7, true);
	SpriteController playerSprite;
	playerSprite.AddSprite(&runSprite);
	playerSprite.AddSprite(&idleSprite);
	playerSprite.AddSprite(&hurtSprite);
	/*sprites*/

	/*player*/
	int playerW = 96;
	int playerH = 125;
	Vector2 playerPos(500, groundHeight - playerH);
	PlayerNew plNew = PlayerNew(playerPos, playerW, playerH);
	plNew.m_IdleSprite = &idleSprite;
	plNew.m_RunSprite = &runSprite;
	plNew.m_SpriteController = &playerSprite;
	/*player*/

	CircularBG bg("res/img/BG2.png", 1);
	CircularBG cloudsBG("res/img/clouds2.png", 2);
	ParticleEmitter peRed(50, "res/img/red.png");
	ParticleEmitter peWhite(30, "res/img/white.png");
	TSGround tsGround;

	bg.m_Player = &plNew;
	cloudsBG.m_Player = &plNew;
	tsGround.m_Player = &plNew;
	Coins theCoins(groundHeight);
	theCoins.m_Player = &plNew;
	theCoins.m_CollectParticle = &peWhite;
	theCoins.m_HurtParticle = &peRed;
	/*this order is important*/
	theGameEngine.AddGameObject(&bg);
	theGameEngine.AddGameObject(&cloudsBG);
	theGameEngine.AddGameObject(&plNew);
	theGameEngine.AddGameObject(&theCoins);
	theGameEngine.AddGameObject(&tsGround);
	theGameEngine.AddGameObject(&peRed);
	theGameEngine.AddGameObject(&peWhite);
	theGameEngine.Run();
	/*******************************/
	std::cin.get();
	return 0;
}

int main22()
{
	GameEngine theGameEngine;
	SDL_Renderer* renderer = theGameEngine.GetRenderer();

	ParticleEmitter pe(30, "res/img/red2.png");
	theGameEngine.AddGameObject(&pe);
	theGameEngine.Run();

	std::cin.get();
	return 0;
}