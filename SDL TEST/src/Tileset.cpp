#include "Tileset.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

Tileset::Tileset(const std::string & rectsFilepath, const std::string & textureFilepath, 
	SDL_Renderer* renderer)
	:m_RectsFilepath(rectsFilepath), 
	m_TilesetTexture(textureFilepath, renderer),
	m_XOffset(0), m_YOffset(0)
{
	Load();
}

Tileset::Tileset()
	:m_XOffset(0), m_YOffset(0)
{
}

Tileset::~Tileset()
{
}

void Tileset::LoadTileset(const std::string& rectsFilepath, 
	const std::string& textureFilepath, SDL_Renderer* renderer)
{
	m_TilesetTexture.LoadTexture(textureFilepath, renderer);
	m_RectsFilepath = rectsFilepath;

	Load();
}

void Tileset::RenderCopy()
{
	for (const RectPair& pair : m_RectPairs)
	{
		SDL_Rect offsetRect = { pair.dstRect.x + m_XOffset, pair.dstRect.y + m_YOffset,
			pair.dstRect.w, pair.dstRect.h };
		if (InsideBoundary(offsetRect))
		{
			m_TilesetTexture.RenderCopy(pair.srcRect, offsetRect);
		}
	}
}

void Tileset::Debug() const
{
	for (const RectPair& pair : m_RectPairs)
	{
		std::cout << "srcRect: " << pair.srcRect.x << ", " << pair.srcRect.y << ", "
			<< pair.srcRect.w << ", " << pair.srcRect.h << "\n";
		std::cout << "dstRect: " << pair.dstRect.x << ", " << pair.dstRect.y << ", "
			<< pair.dstRect.w << ", " << pair.dstRect.h << "\n";
	}
	std::cout << "\n";
}

void Tileset::ParseFile()
{
	std::ifstream filestream(m_RectsFilepath);

	if (!filestream.is_open())
	{	
		std::cout << "Failed to open file: " << m_RectsFilepath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(filestream, line))
	{
		// skip blank lines
		if (line == "")
		{
			continue;
		}
		if (line.size() != 0 && line[0] == '#')
		{
			// ignore comment
			continue;
		}
		std::vector<std::string> words = GetWords(line);
		// x1 y1 w1 h1 | x2 y2 w2 h2 format
		/*
		if (words.size() != 9)
		{
			std::cout << "size: " << words.size() << std::endl;
			std::cout << "Invalid file format\n";
			return;
		}
		*/
		SDL_Rect srcRect, dstRect;
		srcRect.x = std::stoi(words[0]);
		srcRect.y = std::stoi(words[1]);
		srcRect.w = std::stoi(words[2]);
		srcRect.h = std::stoi(words[3]);
		if (words[4] != "|")
		{
			std::cout << "Invalid file format\n";
			return;
		}
		dstRect.x = std::stoi(words[5]);
		dstRect.y = std::stoi(words[6]);
		dstRect.w = std::stoi(words[7]);
		dstRect.h = std::stoi(words[8]);
		
		m_RectPairs.push_back({ srcRect, dstRect });
	}
	
	filestream.close();
}

void Tileset::Load()
{
	try
	{
		ParseFile();
	}
	catch (const std::invalid_argument& ia)
	{
		m_RectPairs.clear();
		std::cout << "Error parsing " << m_RectsFilepath << std::endl;
		std::cout << ia.what() << std::endl;
	}
}

std::vector<std::string> Tileset::GetWords(const std::string & line) const
{
	std::string word = "";
	std::vector<std::string> wordVec;

	for (char ch : line)
	{
		if (ch == ' ' && word != "")
		{
			wordVec.push_back(word);
			word = "";
			continue;
		}
		if (ch != ' ') word += ch;
	}
	if (word != "") wordVec.push_back(word);

	return wordVec;
}

bool Tileset::InsideBoundary(const SDL_Rect & rect) const
{
	int halfW = rect.w / 2;
	int halfH = rect.h / 2;
	int midX = rect.x + halfW + 1;
	int midY = rect.y + halfH + 1;

	if (midX < m_Boundary.left - halfW) return false;
	if (midX > m_Boundary.right + halfW) return false;
	if (midY < m_Boundary.up - halfH) return false;
	if (midY > m_Boundary.down + halfH) return false;
	 
	return true;
}
