#pragma once
#include "GameObject.h"
#include "Particle.h"
#include "Texture.h"
#include <cstdlib>
#include <algorithm>

class ParticleEmitter : public GameObject  
{
public:
	ParticleEmitter(int maxParticle, const std::string& filepath);
	~ParticleEmitter();

	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter(const ParticleEmitter&&) = delete;
	ParticleEmitter& operator=(const ParticleEmitter&) = delete;
	ParticleEmitter&& operator=(const ParticleEmitter&&) = delete;

	void Emit(const Vector2& position);
	void Init(GameEngine* ge) override;
	void Update(double deltaTime) override;
	void Render() override;
	void HandleInput(const SDL_Event& event, double deltaTime) override;
private:
	enum class State
	{
		IDLE, PLAYING, STOPPED
	};
	const int		m_MaxParticle;
	Particle*		m_Particles;
	State			m_State = State::IDLE;
	std::string		m_TextureFilepath;
	Texture			m_ParticleTexture;
	/*write some private functions here*/
	int GetRand(int range, bool positiveOnly = true) const;
};

