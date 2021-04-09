#pragma once
#include "Core.h"
#include "GameEngine.h"

class GameEngine;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init(GameEngine* ge) = 0;
	virtual void Update(double deltaTime) = 0; 
	virtual void Render() = 0;
	virtual void HandleInput(const SDL_Event& event, double deltaTime) = 0;
private:

};