#pragma once
#include "Sprite.h"
#include <string>
#include <map>

class SpriteController
{
public:
	SpriteController();
	~SpriteController();

	void AddSprite(Sprite* sprite);
	void Play(const std::string& spriteName, const SDL_Rect& dstRect, bool flip = false);
	bool PlayOnce(const std::string& spriteName, const SDL_Rect& dstRect, bool flip = false);
private:
	std::map<std::string, Sprite*>		m_SpriteMap;
	std::string							m_LastPlayedSprite;
};