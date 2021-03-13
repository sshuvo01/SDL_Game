#include "TexturesSlider.h"

TexturesSlider::TexturesSlider()
	:m_Textures(std::vector<Texture>()), m_XUpdate(0), m_XOffsetLeft(0), 
	m_XOffsetRight(0), m_Dir(SliderDirection::LEFT)
{

}

TexturesSlider::TexturesSlider(const std::vector<Texture>& txts, int dx, int xOffLeft, int xOffRight, 
	SliderDirection dir)
	: m_Textures(txts), m_XUpdate(dx), m_XOffsetLeft(xOffLeft), m_XOffsetRight(xOffRight), m_Dir(dir)
{

}

TexturesSlider::~TexturesSlider()
{

}

void TexturesSlider::AddTexture(const Texture & txt)
{
	m_Textures.push_back(txt);
}

void TexturesSlider::RenderCopy(SDL_Renderer * renderer) 
{
	int dirMult = (m_Dir == SliderDirection::LEFT ? -1 : 1);
	int changeInX = dirMult * m_XUpdate;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		SDL_RenderCopy(renderer, m_Textures[i].GetTexture(), NULL, m_Textures[i].GetRect());
		// update X for the next time
		int nextX = changeInX + m_Textures[i].GetRect()->x;

		if (nextX <= m_XOffsetLeft || nextX >= m_XOffsetRight)
		{
			// circular
			(m_Dir == SliderDirection::LEFT) ? m_Textures[i].SetX(m_XOffsetRight) : m_Textures[i].SetX(m_XOffsetLeft);
		}
		else
		{
			m_Textures[i].ChangeX(changeInX);
		}
	} // end of for
}
