#pragma once
#include "GameObject.h"
#include "StateMachine.h"
#include "Texture.h"
#include "Vector2.h"
#include "Collision.h"
#include "Obstacle.h"
#include "Ground.h"

class Player : public GameObject
{
private:
	Vector2			m_Position;
	Texture			m_Texture;
	
	int				m_Width;
	int				m_Height;
	SDL_Renderer*	m_Renderer;

	/**/
	int				m_ScreenWidth;
	int				m_ScreenHeight;
	int				m_GroundHeight;
	StateMachine	m_StateMachine;	

	bool			m_JumpRight;
	/**/
	void CheckBoundary();
	void SetupStateMachine();
	void CheckObstacleHit(Obstacle* checkHit, Obstacle* placeIfHit = nullptr);
	// control metaphohrs
	void ChangePosition(const Vector2& newPos);
	void DeltaPosition(const Vector2& step, double deltaTime = 1.0);
public:
	Obstacle*		m_ObstacleRight;
	Obstacle*		m_BluBarLeft;
	Ground*			m_Ground;
	 Player(const Vector2& pos, int width, int height);
	~Player();


	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override; // send input as parameter
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
};

