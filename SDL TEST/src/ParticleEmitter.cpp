#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int maxParticle, const std::string& filepath)
	:m_MaxParticle(maxParticle), m_State(State::IDLE), m_TextureFilepath(filepath)
{
	m_Particles = new Particle[m_MaxParticle];
}

ParticleEmitter::~ParticleEmitter()
{
	if (m_Particles) delete[] m_Particles;
}

void ParticleEmitter::Init(GameEngine * ge)
{
	m_ParticleTexture.LoadTexture(m_TextureFilepath, ge->GetRenderer());
	for (int i = 0; i < m_MaxParticle; i++)
	{
		m_Particles[i].SetTexture(&m_ParticleTexture);
	}
}

void ParticleEmitter::Update(double deltaTime)
{
	if (m_State != State::PLAYING) return;
	for (int i = 0; i < m_MaxParticle; i++)
	{
		//Vector2 gravity(0.0, 9.8 * 100.0 / 3600.0);
		m_Particles[i].Update(); 
	}
}

void ParticleEmitter::Render()
{
	if (m_State != State::PLAYING) return;
	for (int i = 0; i < m_MaxParticle; i++)
	{
		m_Particles[i].Render();
	}
	bool allDead = true;
	for (int i = 0; i < m_MaxParticle; i++)
	{
		if (m_Particles[i].IsAlive())
		{
			allDead = false;
			break;
		}
	}
	if (allDead)
	{
		m_State = State::IDLE; // can be played again
	}
}

void ParticleEmitter::HandleInput(const SDL_Event & event, double deltaTime)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		if (event.type == SDL_KEYDOWN)
		{
			//std::cout << "Pressed w\n";
			//Vector2 particleSpawnPos = Vector2(200, 200);
			//Emit(particleSpawnPos);
			break;
		}
		if (event.type == SDL_KEYUP)
		{

			break;
		}
		break;
	case SDLK_d:
		if (event.type == SDL_KEYDOWN)
		{
			
			break;
		}
		if (event.type == SDL_KEYUP)
		{
			
			break;
		}
		break;
	case SDLK_a:
		if (event.type == SDL_KEYDOWN)
		{
			
			break;
		}
		if (event.type == SDL_KEYUP)
		{
			break;
		}
		break;
	default:
		break;
	}
}

int ParticleEmitter::GetRand(int range, bool positiveOnly) const
{
	int randomN = rand() % (range * 2 + 1); // 0 to range*2
	if (!positiveOnly) randomN -= range;
	return randomN;
}

void ParticleEmitter::Emit(const Vector2 & position)
{
	if (m_State != State::IDLE) return;

	for (int i = 0; i < m_MaxParticle; i++)
	{
		Vector2 randomVelocity(GetRand(3, false), GetRand(3, false));

		m_Particles[i].Init(GetRand(10), position, randomVelocity, GetRand(18));
	}
	m_State = State::PLAYING;
}