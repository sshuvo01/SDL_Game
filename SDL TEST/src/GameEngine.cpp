#include "GameEngine.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, unsigned int maxFPS)
	: m_ScreenWidth(width), m_ScreenHeight(height), m_MaxFPS(maxFPS)
{
	m_GameRunning = true;
	m_DeltaTime = 0.0;
	bool ret = InitWindow();
	assert(ret); 
}

GameEngine::~GameEngine()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);

	IMG_Quit();
	SDL_Quit();
}

bool GameEngine::InitWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	//Enable gpu_enhanced textures
	IMG_Init(IMG_INIT_PNG);

	m_Window = SDL_CreateWindow("Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_ScreenWidth,
		m_ScreenHeight, 0);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

	return true;
}

void GameEngine::Init()
{
	for (GameObject* go : m_GameObjects)
	{
		go->Init(this);
	}
}

void GameEngine::HandleEvents()
{
	/*pop one event from the queue*/
	int ret =  SDL_PollEvent(&m_GameEvent);
	if (ret != 1) return;
	SDL_Event temp = m_GameEvent;
	
	// delta time?
	for (GameObject* go : m_GameObjects)
	{
		go->HandleInput(temp, m_DeltaTime); // pass the delta time
	}
}

void GameEngine::UpdateMechanics()
{
	// delta time?
	for (GameObject* go : m_GameObjects)
	{
		go->Update(m_DeltaTime); // pass the delta time
	}
}

void GameEngine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 180, 180, 180, 255);
	SDL_RenderClear(m_Renderer);
	for (GameObject* go : m_GameObjects)
	{
		go->Render();
	}
	SDL_RenderPresent(m_Renderer);
}

void GameEngine::Run()
{
	double frameDuration = 1.00 / (double)m_MaxFPS;
	double frameStartTime;
	double elapsedtime;

	Init();

	while (m_GameRunning)
	{
		frameStartTime = SDL_GetTicks();
		HandleEvents();
		UpdateMechanics();
		Render();
		elapsedtime = frameStartTime - SDL_GetTicks();
		/*limit the FPS*/
		if (elapsedtime < frameDuration)
		{
			SDL_Delay(frameDuration - elapsedtime);
		}
		m_DeltaTime = frameStartTime - SDL_GetTicks();
	} // end of while
}

void GameEngine::AddGameObject(GameObject * go)
{
	m_GameObjects.push_back(go);
}
