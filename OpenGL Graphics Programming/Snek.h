#pragma once

#include "SnekPart.h"
#include "Boid.h"
#include "TextLabel.h"

#include <vector>
#include "InputManager.h"

enum GameState;

namespace FMOD {
	class System;
	class Sound;
}

class Snek
{
public:
	Snek(std::vector<Boid>* _boidObjects, TextLabel* _scoreText, FMOD::System* _audioSystem, FMOD::Sound* _yeatSound, FMOD::Sound* _shoopSound, unsigned _snekStartSize = 50);
	~Snek();

	void Render(Camera& _camera);
	void Process(GameState& _gameState, unsigned& _score, double _deltaTime);
	void ProcessInput();

private:

	InputManager& inputManager = InputManager::getInstance();
	CClock m_snekClock;

	std::vector<SnekPart> m_snekObjects;
	std::vector<Boid>* m_boidObjects;

	TextLabel* m_scoreText;
	FMOD::System* m_audioSystem;
	FMOD::Sound* m_yeatSound;
	FMOD::Sound* m_shoopSound;

	SphereMesh* m_snekMesh = nullptr;
	Shader* m_snekShader = nullptr;
	Texture* m_snekTexture = nullptr;

	//The spacing (in pixels) the snake can move at a time
	int m_snekSpeed = 5;

	glm::vec2 m_movement{ 0.0f, 0.0f };
};

