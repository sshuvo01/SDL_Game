#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string& filepath, SDL_Renderer* renderer,
	const std::string& spriteName, int frameW, int frameCount)
	: m_Filepath(filepath),
	m_Name(spriteName),
	m_FrameWidth(frameW),
	m_Texture(filepath, renderer),
	m_FrameNumber(0),
	m_FrameCount(frameCount),
	m_FrameRate(10)
{
	m_LastFrameUpdateTime = SDL_GetTicks();
	m_FrameDuration = 1000 / m_FrameRate;
}

Sprite::~Sprite()
{
}

void Sprite::Render(const SDL_Rect& dstRect, bool flip)
{
	Uint32 currentTime = SDL_GetTicks();
	Uint32 elapsedTime = currentTime - m_LastFrameUpdateTime;

	int i = m_FrameNumber % m_FrameCount;
	int h = m_Texture.GetSrcHeight();
	SDL_Rect srcRect = { i * m_FrameWidth, 0, m_FrameWidth, h };
	
	flip ? m_Texture.RenderCopyHFlip(srcRect, dstRect) : 
		m_Texture.RenderCopy(srcRect, dstRect);

	if (elapsedTime >= m_FrameDuration)
	{
		/*advance to the next frame, for the next call*/
		m_LastFrameUpdateTime = SDL_GetTicks();
		m_FrameNumber++;
	}
}
