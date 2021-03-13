#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	m_Texture = NULL;
	m_Renderer = NULL;
	m_Rect = SDL_Rect();
}

Texture::Texture(const std::string & path, SDL_Renderer* renderer, SDL_Rect rect)
{
	LoadTexture(path, renderer, rect);
}

Texture::Texture(const std::string & path, SDL_Renderer * renderer, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	LoadTexture(path, renderer, rect);
}

Texture::~Texture()
{
}

void Texture::LoadTexture(const std::string & path, SDL_Renderer* renderer, SDL_Rect rect)
{
	//std::cout << "load texture: " << rect.w << std::endl;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface)
	{
		std::cout << "failed to load " << path << std::endl;
	}

	m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	m_Renderer = renderer;
	m_Rect = rect;

}

SDL_Texture * Texture::GetTexture() const
{
	return m_Texture;
}

SDL_Rect * Texture::GetRect() 
{
	return &m_Rect;
}

void Texture::SetRect(SDL_Rect rect)
{
	m_Rect = rect;
}

void Texture::SetX(int x)
{
	m_Rect.x = x;
}

void Texture::SetRect(int x, int y, int w, int h)
{
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = w;
	m_Rect.h = h;
}

void Texture::ChangeX(int dx)
{
	m_Rect.x += dx;
}

void Texture::ChangeY(int dy)
{
	m_Rect.y += dy;
}
