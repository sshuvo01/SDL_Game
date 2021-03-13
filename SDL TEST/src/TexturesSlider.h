#pragma once

#include "Core.h"
#include "Texture.h"
#include <vector>

enum class  SliderDirection
{
	LEFT,
	RIGHT
};

class TexturesSlider
{
private:
	std::vector<Texture>	m_Textures;
	int						m_XUpdate; 
	int						m_XOffsetLeft;
	int						m_XOffsetRight;
	SliderDirection			m_Dir;
public:
	TexturesSlider();
	TexturesSlider(const std::vector<Texture>& txts, int dx, int xOffLeft, int xOffRight, 
		SliderDirection dir = SliderDirection::LEFT);
	~TexturesSlider();
	
	void AddTexture(const Texture& txt);
	void RenderCopy(SDL_Renderer* renderer);
};

