#include "BackgroundCOM.h"

BackgroundCOM::BackgroundCOM()
{
}

BackgroundCOM::~BackgroundCOM()
{
}

void BackgroundCOM::Init(GameEngine * ge)
{
	m_Renderer = ge->GetRenderer();
	std::string path = "res/img/BG1.png";
	m_Texture.LoadTexture(path, m_Renderer);

	m_ScreenWidth = ge->GetScreenWidth();
	m_ScreenHeight = ge->GetScreenHeight();
}

void BackgroundCOM::Update(double deltaTime)
{
}

void BackgroundCOM::Render()
{
	SDL_Rect dstRect = { 0, 0, m_ScreenWidth, m_ScreenHeight };
	m_Texture.RenderCopy(dstRect);
}

void BackgroundCOM::HandleInput(const SDL_Event & event, double deltaTime)
{
}
