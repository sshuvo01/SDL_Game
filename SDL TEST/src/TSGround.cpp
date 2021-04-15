#include "TSGround.h"
#include <iostream>

TSGround::TSGround()
	:m_YOffset(0),
	m_StateMachine("idle")
{
}

TSGround::~TSGround()
{
}

void TSGround::Init(GameEngine * ge)
{
	m_Tileset.LoadTileset("res/Tilesets_Data/Ground.tiles", "res/img/TilesetExample.png",
		ge->GetRenderer());
	m_Tileset.SetXOffset(0);
	m_Tileset.SetYOffset(0);
	//m_Tileset.Debug();
	Boundary b;
	b.left = 0;
	b.right = ge->GetWidth();
	b.up = 0;
	b.down = ge->GetHeight();
	m_Tileset.SetBoundary(b);

	/*state machine*/
	m_StateMachine.AddTransition("idle", "moveright");
	m_StateMachine.AddTransition("moveright", "idle");

	m_StateMachine.AddTransition("idle", "moveleft");
	m_StateMachine.AddTransition("moveleft", "idle");

	m_StateMachine.AddTransition("moveleft", "moveright");
	m_StateMachine.AddTransition("moveright", "moveleft");
}

void TSGround::Update(double deltaTime)
{
	if (m_Player->m_StateMachine.GetCurrentState() == "hurt")
	{
		m_StateMachine.TransitionTo("idle");
	}

	int speed = 3;
	if (m_StateMachine.GetCurrentState() == "moveright")
	{
		m_Tileset.UpdateXOffset(speed);
	}
	else if(m_StateMachine.GetCurrentState() == "moveleft")
	{
		m_Tileset.UpdateXOffset(-speed);
	}
}

void TSGround::Render()
{
	m_Tileset.RenderCopy();
}

void TSGround::HandleInput(const SDL_Event & event, double deltaTime)
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
