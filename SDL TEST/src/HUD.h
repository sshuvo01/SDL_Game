#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "Texture.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Collision.h"

class HUD : public GameObject
{
private:

      SDL_Renderer*	m_Renderer;
	    Texture	m_Texture;
      SDL_Texture* mScore;
      SDL_Rect text;

public:
	    int	x_Position;
	    int y_Position;
	    int	m_Width;
	    int	m_Height;
	    int lives;
      int score;
      TTF_Font *font;

	    HUD();
	    HUD(int life);
	    ~HUD();

      int getLives();
      int getScore();
	    void Init(GameEngine* ge) override;
	    void Render() override;
      void Update(double deltaTime);
      void HandleInput(const SDL_Event& event, double deltaTime);
	    void LostLife();
      void AddScore(int scoreIncrease);
};
