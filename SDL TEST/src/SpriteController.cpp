#include "SpriteController.h"
#include <iostream>

SpriteController::SpriteController()
{
	m_LastPlayedSprite = "";
}

SpriteController::~SpriteController()
{
}

void SpriteController::AddSprite(Sprite * sprite)
{
	std::string name = sprite->GetName();
	if (m_SpriteMap.count(name) != 0)
	{
		// already exists
		std::cout << "Sprite " << name << " already exists\n";
		return;
	}
	m_SpriteMap[name] = sprite;
}

void SpriteController::Play(const std::string & spriteName, const SDL_Rect& dstRect, bool flip)
{
	if (m_SpriteMap.count(spriteName) == 0)
	{
		std::cout << "Sprite " << spriteName << " not found\n";
		return;
	}

	m_SpriteMap[spriteName]->Render(dstRect, flip);
	
	if (spriteName != m_LastPlayedSprite)
	{
		// sprite switch
		if (m_LastPlayedSprite != "") m_SpriteMap[m_LastPlayedSprite]->ResetFrames();
	}
	m_LastPlayedSprite = spriteName;
}
