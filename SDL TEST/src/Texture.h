#pragma once

#include "Core.h"
#include <string>

class Texture
{
private:
	SDL_Texture*	m_Texture;
	SDL_Renderer*	m_Renderer;
	SDL_Rect		m_Rect;
public:
	Texture();
	Texture(const std::string& path, SDL_Renderer* renderer, SDL_Rect rect = SDL_Rect());
	Texture(const std::string& path, SDL_Renderer* renderer, int x, int y, int w, int h);
	~Texture();

	void LoadTexture(const std::string& path, SDL_Renderer* renderer, SDL_Rect rect = SDL_Rect());

	SDL_Texture* GetTexture() const;
	SDL_Rect* GetRect();

	void SetRect(SDL_Rect rect);
	void SetX(int x);
	void SetRect(int x, int y, int w, int h);
	void ChangeX(int dx);
	void ChangeY(int dy);
};


