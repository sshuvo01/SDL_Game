#include "EnemyCOM.h"

EnemyCOM::EnemyCOM(const Vector2& pos, int width, int height)
	: m_Position(pos),
	m_Width(width),
	m_Height(height),
	m_StateMachine("run"),
	m_FaceDirection("right"),
	m_PlayerPositionX(500),
	m_Hitpoint(3)
{
	srand(time(NULL));
	SetupStateMachine();
}

EnemyCOM::~EnemyCOM()
{
	m_SpriteController->FreeSprites();
	delete m_SpriteController;
}

void EnemyCOM::Init(GameEngine * ge)
{
	m_Hitpoint = 3;
	m_HitPlayer = false;
	m_ScreenWidth = ge->GetScreenWidth();
	m_ScreenHeight = ge->GetScreenHeight();
}

void EnemyCOM::Update(double deltaTime)
{
	std::string currentState = m_StateMachine.GetCurrentState();
	if (currentState == "dying" || currentState == "dead") return;

	if (currentState == "run" && BecomeIdle())
	{
		m_StateMachine.TransitionTo("idle");
		m_IdleTimer.Start(2000);
	}
	/*-----------*/
	if (m_IdleTimer.TimeUp() && currentState == "idle")
	{
		m_StateMachine.TransitionTo("run");
	}

	//
	int speed = 2;
	if (m_Position.X() < m_PlayerPositionX)
	{
		m_FaceDirection.TransitionTo("right");
		speed = 2;
	}
	else 
	{
		m_FaceDirection.TransitionTo("left");
		speed = -2;
	}

	if(currentState == "run")
		m_Position[0] += speed;
}

void EnemyCOM::Render()
{
	std::string currentState = m_StateMachine.GetCurrentState();
	//std::cout << "curent state: " << currentState << std::endl;
	if (currentState == "dead") return;

	SDL_Rect dstRect = { m_Position.X(), m_Position.Y(), m_Width, m_Height };
	bool flip = true;
	if (m_FaceDirection.GetCurrentState() == "left") flip = false;

	if(currentState == "idle") m_SpriteController->Play("idle", dstRect, flip);
	else if (currentState == "run") m_SpriteController->Play("run", dstRect, flip);
	else if (currentState == "hurt")
	{
		bool playedOnce = m_SpriteController->PlayOnce("hurt", dstRect, flip);
		if (playedOnce)
		{
			m_StateMachine.TransitionTo("idle");
			m_IdleTimer.Start(1000);
		}
	}
	else if (currentState == "dying")
	{
		bool playedOnce = m_SpriteController->PlayOnce("dying", dstRect, flip);
		if (playedOnce) m_StateMachine.TransitionTo("dead");
	}
	//else if (currentState == "hitplayer")
	//{
	//	m_SpriteController->Play("idle", dstRect, flip);
	//}
}

void EnemyCOM::HandleInput(const SDL_Event & event, double deltaTime)
{
}

bool EnemyCOM::BecomeIdle() const
{
	int chance = 5;// chance to become idle = chance/1000
	int randomN = rand() % 1000;
	randomN++;

	if (randomN <= chance) return true;
	return false;
}

void EnemyCOM::SetupStateMachine()
{
	m_StateMachine.AddTransition("run", "idle");
	m_StateMachine.AddTransition("idle", "run");

	m_StateMachine.AddTransition("idle", "hurt");
	m_StateMachine.AddTransition("hurt", "idle");

	m_StateMachine.AddTransition("run", "hurt");

	m_StateMachine.AddTransition("idle", "dying");
	m_StateMachine.AddTransition("run", "dying");
	m_StateMachine.AddTransition("hurt", "dying");

	m_StateMachine.AddTransition("dying", "dead");
	/*
	m_StateMachine.AddTransition("idle", "hitplayer");
	m_StateMachine.AddTransition("hitplayer", "idle");
	
	m_StateMachine.AddTransition("run", "hitplayer");
	m_StateMachine.AddTransition("hitplayer", "run");
	*/
	// face direction
	m_FaceDirection.AddTransition("right", "left");
	m_FaceDirection.AddTransition("left", "right");
}
