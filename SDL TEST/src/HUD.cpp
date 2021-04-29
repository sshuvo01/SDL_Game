#include "HUD.h"

HUD::HUD() {
	x_Position = 0;
	y_Position = 0;
	m_Width = 30;
	m_Height = 30;
	score = 0;
	lives = 3;
	text.x = 1050;
	text.y = 0;
	text.w = 60;
	text.h = 20;
}

HUD::HUD(int life) {
	x_Position = 0;
	y_Position = 0;
	if (life <= 5)
		lives = life;
	else
		lives = 5;
	m_Width = lives * 10;
	m_Height = lives * 10;
	score = 0;
	text.x = 1050;
	text.y = 0;
	text.w = 60;
	text.h = 20;
}


HUD::~HUD() {}


void HUD::Init(GameEngine * ge) {
	m_Renderer = ge->GetRenderer();
	if (score < 10) {
		text.x = 1000;
		text.y = 0;
		text.w = 110;
		text.h = 22;
	}
	else if (score < 100) {
		text.x = 980;
		text.y = 0;
		text.w = 100;
		text.h = 24;
	}
	else if (score < 1000) {
		text.x = 980;
		text.y = 0;
		text.w = 120;
		text.h = 26;
	}
	else if (score < 10000) {
		text.x = 960;
		text.y = 0;
		text.w = 140;
		text.h = 28;
	}


	//Initialize SDL_ttf
	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Open Font
	font = TTF_OpenFont("res/scoreFont.ttf", 80);
	//Check if font opened properly and display error
	if (font == NULL) {
		std::cout << "Font did not load, Error:" << TTF_GetError() << std::endl;
	}

	char *t;
	std::string temp = "SCORE: " + std::to_string(score);
	t = (char*)temp.c_str();
	//Set Text color and render it to a solid of a surface
	SDL_Color ColorOfText = { 255, 255, 255 };
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, t, ColorOfText);
	if (text_surface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	//Create a texture from the text on the surface
	mScore = SDL_CreateTextureFromSurface(m_Renderer, text_surface);
	if (mScore == NULL)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << TTF_GetError() << std::endl;
	}

	SDL_FreeSurface(text_surface);
	std::string path = "res/img/lives.png";
	m_Texture.LoadTexture(path, m_Renderer, { x_Position, y_Position, m_Width, m_Height });
}


void HUD::Render() {

	for (int i = 0; i < lives; i++) {
		m_Texture.SetRect({ x_Position + (i * m_Width), y_Position, m_Width, m_Height });
		SDL_RenderCopy(m_Renderer, m_Texture.GetTexture(), NULL, m_Texture.GetRect());
	}
	SDL_RenderCopy(m_Renderer, mScore, nullptr, &text);
}

void HUD::Update(double deltaTime) {
	char *t;
	std::string temp = "SCORE: " + std::to_string(score);
	t = (char*)temp.c_str();
	//Set Text color and render it to a solid of a surface
	SDL_Color ColorOfText = { 255, 255, 255 };
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, t, ColorOfText);
	if (text_surface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	//Create a texture from the text on the surface
	mScore = SDL_CreateTextureFromSurface(m_Renderer, text_surface);
	if (mScore == NULL)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << TTF_GetError() << std::endl;
	}

	SDL_FreeSurface(text_surface);
}

void HUD::HandleInput(const SDL_Event& event, double deltaTime) {
	int w = 64;
	int h = 20;
	SDL_QueryTexture(mScore, NULL, NULL, &w, &h);
	return;
}

void HUD::LostLife() {
	if (lives > 0)
		lives--;
}

int HUD::getLives() {
	return lives;
}

void HUD::AddScore(int scoreIncrease) {
	score = score + scoreIncrease;
}

int HUD::getScore() {
	return score;
}