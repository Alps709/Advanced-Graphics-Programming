#pragma once
#include "clock.h"
#include "MousePicker.h"
#include "TextLabel.h"
#include "Texture.h"
#include "Object.h"
#include "CubeMap.h"
#include "Model.h"
#include "Terrain.h"
#include "WaterTerrain.h"

#include <fmod.hpp>

class Cube;

enum GameState
{
	GAME_MENU = 0,
	GAME_PLAY = 1,
	GAME_OVER = 2,
};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void AudioInitialise();
	void ProcessInput();

	void Update();
	void Render();

	void FindCurrentIntersectedObject();


	inline static GameState m_gameState = GAME_MENU;

private:
	InputManager& inputManager = InputManager::getInstance();
	
	//Game variables
	unsigned int m_gameScore = 0;
	
	//Clock
	CClock m_clock;

	//Mouse picker
	MousePicker m_mousePicker;

	//Camera
	Camera* m_camera = nullptr;

	//Cube map
	CubeMap& m_CubeMap = CubeMap::getInstance();

	//Terrain
	Terrain* m_grassTerrain = nullptr;
	WaterTerrain* m_waterTerrain = nullptr;

	//The current object in the world that's being intersected by the mouse
	Object* m_currentIntersected = nullptr;

	///Objects
	Cube* m_cube = nullptr;
	Cube* m_cube1 = nullptr;
	Cube* m_cube2 = nullptr;

	//Game terrain textures
	Texture* m_grassTexture = nullptr;
	Texture* m_noiseTexture = nullptr;

	//Shaders
	Shader* m_defaultShader = nullptr;
	Shader* m_sphereShader = nullptr;
	Shader* m_sphereRimLightShader = nullptr;
	Shader* m_sphereCubeMapReflectShader = nullptr;
	Shader* m_tankModelShader = nullptr;

	//Text
	TextLabel* m_menuTitleText = nullptr;
	TextLabel* m_menuInstructText = nullptr;
	TextLabel* m_overText = nullptr;
	TextLabel* m_overScoreText = nullptr;
	TextLabel* m_fpsText = nullptr;
	TextLabel* m_timeText = nullptr;

	//Audio
	inline static FMOD::System* m_audioSystem = nullptr;
	inline static FMOD::Sound* m_yeatSound = nullptr;
	inline static FMOD::Sound* m_shoopSound = nullptr;
	inline static FMOD::Sound* m_trackBackground = nullptr;

	//Uniforms
	GLfloat u_currentTime = 0;
	int u_frameNum = 0;

	//Debug stuff
	bool m_FogRenderMode = true;
	bool m_WireframeRenderMode = false;
};

