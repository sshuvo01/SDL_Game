#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string& filepath, SDL_Renderer* renderer,
	const std::string& spriteName, int frameW, int frameCount, bool playOnce, int frameRate)
	: m_Filepath(filepath),
	m_Name(spriteName),
	m_FrameWidth(frameW),
	m_Texture(filepath, renderer),
	m_FrameNumber(0),
	m_FrameCount(frameCount),
	m_FrameRate(frameRate),
	m_PlayOnce(playOnce)
{
	m_LastFrameUpdateTime = SDL_GetTicks();
	m_FrameDuration = 1000 / m_FrameRate;
}

Sprite::Sprite(Texture * spriteTexture, const std::string & spriteName, int frameW, int frameCount, 
	bool PlayOnce, int frameRate)
	:m_Name(spriteName),
	m_FrameWidth(frameW),
	m_FrameNumber(0),
	m_FrameCount(frameCount),
	m_FrameRate(frameRate),
	m_Texture(*spriteTexture),
	m_PlayOnce(PlayOnce)
{
	//m_Texture = *spriteTexture;
	m_LastFrameUpdateTime = SDL_GetTicks();
	m_FrameDuration = 1000 / m_FrameRate;
}

Sprite::~Sprite()
{
}

bool Sprite::Render(const SDL_Rect& dstRect, bool flip)
{
	Uint32 currentTime = SDL_GetTicks();
	Uint32 elapsedTime = currentTime - m_LastFrameUpdateTime;

	bool playingLastFrame = false;

	int i = m_FrameNumber % m_FrameCount;
	if (m_PlayOnce)
	{
		if (m_FrameNumber >= m_FrameCount)
		{
			i = m_FrameCount - 1;
			playingLastFrame = true;
		}
	}

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

	return playingLastFrame;
}
