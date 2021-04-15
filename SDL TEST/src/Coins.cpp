#include "Coins.h"
#include "Collision.h"

Coins::Coins(int groundHeight)
	:m_StateMachine("idle")
{
	int nOfCoins = 3;
	m_width = 50;
	m_Height = 50;

	for (int i = 0; i < nOfCoins; i++)
	{
		Vector2 pos(650 * i, groundHeight - m_Height);
		m_Coins.push_back({ pos, true });
	}

	m_BombPosition[0] = 740;
	m_BombPosition[1] = groundHeight - m_Height;
	m_BombActive = true;

	/*state machine*/
	m_StateMachine.AddTransition("idle", "moveright");
	m_StateMachine.AddTransition("moveright", "idle");

	m_StateMachine.AddTransition("idle", "moveleft");
	m_StateMachine.AddTransition("moveleft", "idle");

	m_StateMachine.AddTransition("moveleft", "moveright");
	m_StateMachine.AddTransition("moveright", "moveleft");
}

Coins::~Coins()
{
}

void Coins::Init(GameEngine * ge)
{
	m_Texture.LoadTexture("res/img/coin.png", ge->GetRenderer());
	m_TextureBomb.LoadTexture("res/img/bomb2.png", ge->GetRenderer());
}

void Coins::Update(double deltaTime)
{
	if (m_Player->m_StateMachine.GetCurrentState() == "hurt")
	{
		m_StateMachine.TransitionTo("idle");
	}

	// Collision detection
	for (ACoin& coin : m_Coins)
	{
		if (!coin.active) continue;
		// 
		if (Collision::DetectRectCollision({ coin.position, m_width, m_Height },
			{ m_Player->m_Position, m_Player->m_Width,m_Player->m_Height }))
		{
			coin.active = false; // coin collected
			//collision, emit some particles
			if(m_CollectParticle) m_CollectParticle->Emit(coin.position);
		}
	}

	// collision detection for bomb
	if (m_BombActive)
	{
		if (Collision::DetectRectCollision({ m_BombPosition, m_width, m_Height },
			{ m_Player->m_Position, m_Player->m_Width,m_Player->m_Height }))
		{
			m_BombActive = false;//hit the bomb
			m_Player->m_StateMachine.TransitionTo("hurt");

			if (m_HurtParticle) m_HurtParticle->Emit(m_BombPosition);
		}
	}
	
	int step = 3;
	for (ACoin& coin : m_Coins)
	{
		if (coin.active)
		{
			if (m_StateMachine.GetCurrentState() == "moveright")
				coin.position[0] += step;
			else if (m_StateMachine.GetCurrentState() == "moveleft")
				coin.position[0] -= step;
		}
	}
	// bomb
	if (m_BombActive)
	{
		if (m_StateMachine.GetCurrentState() == "moveright")
			m_BombPosition[0] += step;
		else if (m_StateMachine.GetCurrentState() == "moveleft")
			m_BombPosition[0] -= step;
	}
}

void Coins::Render()
{
	for (ACoin coin : m_Coins)
	{
		if (coin.active) m_Texture.RenderCopy({ coin.position.X(), coin.position.Y(), m_width, m_Height });
	}

	// render the bomb
	if (m_BombActive)
	{
		m_TextureBomb.RenderCopy({ m_BombPosition.X(), m_BombPosition.Y(), m_width, m_Height });
	}
}

void Coins::HandleInput(const SDL_Event & event, double deltaTime)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_a:
		if (event.type == SDL_KEYDOWN)
		{
			if (m_StateMachine.GetCurrentState() == "moveright")
			{
				m_StateMachine.TransitionTo("idle");
			}
			else
			{
				m_StateMachine.TransitionTo("moveright");
			}
			break;
		}
		if (event.type == SDL_KEYUP)
		{

			break;
		}
		break;
	case SDLK_d:
		if (event.type == SDL_KEYDOWN)
		{
			if (m_StateMachine.GetCurrentState() == "moveleft")
			{
				m_StateMachine.TransitionTo("idle");
			}
			else
			{
				m_StateMachine.TransitionTo("moveleft");
			}

			break;
		}
		if (event.type == SDL_KEYUP)
		{
			break;
		}
		break;
	default:
		break;
	}
}
