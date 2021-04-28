#pragma once
#include <string>
#include "Texture.h"
#include "Vector2.h"

class Sprite
{
public:
	Sprite(const std::string& filepath, SDL_Renderer* renderer,
		const std::string& spriteName, int frameW, int frameCount, bool playOnce = false, int frameRate = 10);
	Sprite(Texture* spriteTexture, const std::string& spriteName, int frameW, int frameCount,
		bool PlayOnce = false, int frameRate = 10);
	~Sprite();

	bool Render(const SDL_Rect& dstRect, bool flip = false);
	inline void ResetFrames() { m_FrameNumber = 0; }
	inline const std::string GetName() const { return m_Name; }
private:
	std::string			m_Name;
	std::string			m_Filepath;
	Texture				m_Texture;
	int					m_FrameWidth;
	int					m_FrameNumber;
	const int			m_FrameCount;
	const int			m_FrameRate;
	Uint32				m_LastFrameUpdateTime;
	Uint32				m_FrameDuration;
	bool				m_PlayOnce;
};