#pragma once
#include "Core.h"
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& path, SDL_Renderer* renderer, SDL_Rect rect = SDL_Rect());
	Texture(const std::string& path, SDL_Renderer* renderer, int x, int y, int w, int h);
	~Texture();
	void LoadTexture(const std::string& path, SDL_Renderer* renderer, SDL_Rect rect = SDL_Rect(), 
		int* srcW = nullptr, int* srcH = nullptr);
	void RenderCopy(const SDL_Rect& srcRect, const SDL_Rect& dstRect);
	void RenderCopyHFlip(const SDL_Rect& srcRect, const SDL_Rect& dstRect);
	SDL_Texture* GetTexture() const;
	SDL_Rect* GetRect();
	void SetRect(SDL_Rect rect);
	void SetX(int x);
	void SetRect(int x, int y, int w, int h);
	void ChangeX(int dx);
	void ChangeY(int dy);
	inline int GetSrcWidth() const { return m_SrcWidth; }
	inline int GetSrcHeight() const { return m_SrcHeight; }
	inline std::string GetFilepath() const { return m_Filepath; }
private:
	SDL_Texture*	m_Texture;
	SDL_Renderer*	m_Renderer;
	SDL_Rect		m_Rect;
	std::string		m_Filepath;
	int				m_SrcWidth, m_SrcHeight;
};


