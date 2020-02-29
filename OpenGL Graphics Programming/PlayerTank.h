#pragma once
#include "Model.h"
#include "Boid.h"
#include "TextLabel.h"
#include "InputManager.h"
#include <vector>

enum GameState;

namespace FMOD {
	class System;
	class Sound;
}

class PlayerTank : public Model
{
public:
	PlayerTank() = default;
	PlayerTank(std::string path, Shader* shader, std::vector<Boid>* _boidObjects, TextLabel* _scoreText, FMOD::System* _audioSystem, FMOD::Sound* _shootSound, FMOD::Sound* _shoopSound);
	~PlayerTank() = default;;

	void Update(unsigned int& _score, float _deltaTime);
	void ProcessInput(float _deltaTime);
	void LookAtMouse();

	InputManager* inputManager;

	std::vector<Boid>* m_boidObjects;

	TextLabel* m_scoreText;
	FMOD::System* m_audioSystem;
	FMOD::Sound* m_yeatSound;
	FMOD::Sound* m_shoopSound;

	float m_collisionRadius = 50.0f;
};

