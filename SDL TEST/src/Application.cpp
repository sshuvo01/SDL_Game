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

int main()
{
	/**/
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

	std::cin.get();

	return 0;
}

