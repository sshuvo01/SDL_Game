#include "CircularBG.h"
#include <iostream>

CircularBG::CircularBG(const std::string& texturePath, int movementSpeed)
	: m_Texture(),
	m_TexturePath(texturePath),
	m_MovementSpeed(movementSpeed), 
	m_Renderer(nullptr),
	m_Moving(false),
	m_StateMachine("idle")
{
}

CircularBG::~CircularBG()
{
}

void CircularBG::Init(GameEngine * ge)
{
	m_Renderer = ge->GetRenderer();
	m_ScreenWidth = ge->GetScreenWidth();
	m_ScreenHeight = ge->GetScreenHeight();

	m_Texture.LoadTexture(m_TexturePath, m_Renderer, 
		SDL_Rect(), &m_SrcWidth, &m_SrcHeight);
	//m_NegMovement = 0;
	m_SrcXOffset = 20;
	m_SrcYOffset = 330;

	/*states*/
	m_StateMachine.AddTransition("idle", "moveright");
	m_StateMachine.AddTransition("moveright", "idle");

	m_StateMachine.AddTransition("idle", "moveleft");
	m_StateMachine.AddTransition("moveleft", "idle");

	m_StateMachine.AddTransition("moveleft", "moveright");
	m_StateMachine.AddTransition("moveright", "moveleft");
}

void CircularBG::Update(double deltaTime)
{
	if (m_Player->m_StateMachine.GetCurrentState() == "hurt")
	{
		m_StateMachine.TransitionTo("idle");
	}

	if (m_StateMachine.GetCurrentState() == "moveleft")
	{
		m_SrcXOffset += m_MovementSpeed;
	}
	else if (m_StateMachine.GetCurrentState() == "moveright")
	{
		m_SrcXOffset -= m_MovementSpeed;
	}
}

void CircularBG::Render()
{
	//int negMovement = -1200;
	/*
	if (std::abs(m_NegMovement) > m_ScreenWidth)
	{
		m_NegMovement = m_ScreenWidth + m_NegMovement;
	}

	SDL_Rect srcRect = { 0, 0, m_SrcWidth, m_SrcHeight };
	SDL_Rect m_DstRect1 = { m_NegMovement, 0, m_ScreenWidth, m_ScreenHeight };
	m_Texture.RenderCopy(srcRect, m_DstRect1);
	m_DstRect2 = { m_NegMovement + m_DstRect1.w, 0, m_ScreenWidth, m_DstRect1.h };
	m_Texture.RenderCopy(srcRect, m_DstRect2);
	*/
	/*
	std::cout << "Screen Width: " << m_ScreenWidth << std::endl;
	std::cout << "Screen Height: " << m_ScreenHeight << std::endl;
	std::cout << "Src Width: " << m_SrcWidth << std::endl;
	std::cout << "Src Height: " << m_SrcHeight << std::endl;
	*/
	//int height = m_SrcYOffset + m_ScreenHeight;
	int height = m_SrcHeight - m_SrcYOffset;
	int width = m_SrcXOffset + m_ScreenWidth;

	if (m_SrcXOffset > m_SrcWidth)
	{
		m_SrcXOffset -=  m_SrcWidth;
	}

	if (m_SrcXOffset < - m_SrcWidth)
	{
		m_SrcXOffset = m_SrcWidth + m_SrcXOffset;
	}

	if (m_SrcXOffset < 0) // wrap left
	{
		SDL_Rect srcRect1;
		srcRect1.x = m_SrcWidth + m_SrcXOffset; // from right side
		srcRect1.y = m_SrcYOffset;
		srcRect1.w = -m_SrcXOffset;
		srcRect1.h = height;
		SDL_Rect dstRect1 = { 0, 0, srcRect1.w, m_ScreenHeight };

		SDL_Rect srcRect2;
		srcRect2.x = 0;
		srcRect2.y = m_SrcYOffset;
		srcRect2.w = m_ScreenWidth - srcRect1.w;
		srcRect2.h = height;

		SDL_Rect dstRect2 = { dstRect1.w, 0, srcRect2.w, m_ScreenHeight };
		m_Texture.RenderCopy(srcRect1, dstRect1);
		m_Texture.RenderCopy(srcRect2, dstRect2);
	}

	else if (m_SrcXOffset + m_ScreenWidth > m_SrcWidth) // wrap right
	{
		//std::cout << "Positive value\n";
		// 2 rects
		int extraWidth = (m_SrcXOffset + m_ScreenWidth) - m_SrcWidth;
		int src1Width = m_ScreenWidth - extraWidth;
		
		SDL_Rect srcRect1 = { m_SrcXOffset, m_SrcYOffset, src1Width, height };
		SDL_Rect srcRect2 = { 0, m_SrcYOffset, extraWidth, height };

		SDL_Rect dstRect1 = { 0, 0, srcRect1.w, m_ScreenHeight };
		SDL_Rect dstRect2 = { m_ScreenWidth-extraWidth , 0, srcRect2.w, m_ScreenHeight };
	
		m_Texture.RenderCopy(srcRect1, dstRect1);
		m_Texture.RenderCopy(srcRect2, dstRect2);
	}
	else
	{
		// 1 rect
		SDL_Rect srcRect1 = { m_SrcXOffset, m_SrcYOffset, m_ScreenWidth, height };
		SDL_Rect dstRect1 = { 0, 0, m_ScreenWidth, m_ScreenHeight };
		m_Texture.RenderCopy(srcRect1, dstRect1);
	}
}

void CircularBG::HandleInput(const SDL_Event & event, double deltaTime)
{
	static bool move = false;

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

void CircularBG::DebugRect(const SDL_Rect & rect) const
{
	std::cout << rect.x << ", " << rect.y << ", "
		<< rect.w << ", " << rect.h << ", " << std::endl;
}
