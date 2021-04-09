#pragma once
#include "Texture.h"
#include "Vector2.h"
#include <vector>
#include <string>

struct RectPair
{
	SDL_Rect srcRect, dstRect;
};

struct Boundary
{
	int left, right, up, down;
};

class Tileset
{
public:
	Tileset(const std::string& rectsFilepath, const std::string& textureFilepath, 
		SDL_Renderer* renderer);
	Tileset();
	~Tileset();

	void LoadTileset(const std::string& rectsFilepath, 
		const std::string& textureFilepath, SDL_Renderer* renderer);
	void RenderCopy();
	void Debug() const;
	inline void SetBoundary(const Boundary& bound) { m_Boundary = bound; }
	inline void UpdateXOffset(int xOffsetDelta) { m_XOffset += xOffsetDelta; }
	inline void UpdateYOffset(int yOffsetDelta) { m_YOffset += yOffsetDelta; }
	inline void SetXOffset(int xOffset) { m_XOffset = xOffset; }
	inline void SetYOffset(int yOffset) { m_YOffset = yOffset; }
	inline int GetXOffset() const { return m_XOffset; }
	inline int GetYOffset() const { return m_YOffset; }
private:
	std::string					m_RectsFilepath;
	Texture						m_TilesetTexture;
	std::vector<RectPair>		m_RectPairs;
	int							m_XOffset, m_YOffset;
	Boundary					m_Boundary;
	/*private functions*/
	void ParseFile();
	void Load();
	std::vector<std::string> GetWords(const std::string & line) const;
	bool InsideBoundary(const SDL_Rect& rect) const;
};
