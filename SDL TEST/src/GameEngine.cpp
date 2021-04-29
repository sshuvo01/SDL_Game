#include "GameEngine.h"
#include <algorithm>

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

	m_Window = SDL_CreateWindow("Call of Monsters",
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

void GameEngine::ProcessBuffer()
{
	if (m_GameObjectsBuffer.size() == 0) return;
	m_GameObjects.insert(m_GameObjects.end(), m_GameObjectsBuffer.begin(), m_GameObjectsBuffer.end());
	for (GameObject* go : m_GameObjectsBuffer)
	{
		go->Init(this);
	}
	m_GameObjectsBuffer.clear();
	// delete the gameobjects in the list
	for (GameObject* goDelete : m_GameObjectDeleteBuffer)
	{
		auto iter = std::find(m_GameObjects.begin(), m_GameObjects.end(), goDelete);
		if (iter != m_GameObjects.end())
		{
			delete *iter;
			m_GameObjects.erase(iter);
		}
	}
	m_GameObjectDeleteBuffer.clear();
}

void GameEngine::Run()
{
	double frameDuration = 1000.00 / (double)m_MaxFPS;
	double frameStartTime;
	double elapsedtime;
	std::cout << "max fps: " << m_MaxFPS << std::endl;
	Init();

	while (m_GameRunning)
	{
		frameStartTime = SDL_GetTicks();
		HandleEvents();
		UpdateMechanics();
		Render();
		//std::cout << "Number of GO: " << m_GameObjects.size() << "\n";
		elapsedtime =  SDL_GetTicks() - frameStartTime;
		/*limit the FPS*/
		if (elapsedtime < (Uint32) frameDuration)
		{
			SDL_Delay(frameDuration - elapsedtime);
		}
		m_DeltaTime = frameStartTime - SDL_GetTicks();
		// end of a frame
		ProcessBuffer();
	} // end of while
}

void GameEngine::AddGameObject(GameObject * go)
{
	m_GameObjects.push_back(go);
}

void GameEngine::AddGameObjectBuffer(GameObject * go)
{
	m_GameObjectsBuffer.push_back(go);
}

void GameEngine::DeleteGameObjectBuffer(GameObject * go)
{
	m_GameObjectDeleteBuffer.push_back(go);
}
