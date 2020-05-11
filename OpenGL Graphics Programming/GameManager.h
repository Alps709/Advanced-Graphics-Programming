#pragma once
#include "clock.h"
#include "MousePicker.h"
#include "TextLabel.h"
#include "Texture.h"
#include "GameObject.h"
#include "CubeMap.h"
#include "Model.h"
#include "Terrain.h"
#include "WaterTerrain.h"

#include <fmod.hpp>

#include "GeometryObject.h"

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

	void ProcessInput();

	void Update();
	void Render();

	void FindCurrentIntersectedObject();

	void Reset();

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


	///Objects

	//Cube map
	CubeMap& m_CubeMap = CubeMap::getInstance();

	//Terrain
	Terrain* m_grassTerrain = nullptr;
	WaterTerrain* m_waterTerrain = nullptr;

	//Cubes with stencils
	Cube* m_cube = nullptr;
	Cube* m_cube1 = nullptr;
	Cube* m_cube2 = nullptr;

	//Geometry shader model
	GeometryObject* m_geometryObject = nullptr;

	//The current object in the world that's being intersected by the mouse
	GameObject* m_currentIntersected = nullptr;
	

	//Game terrain textures
	Texture* m_grassTexture = nullptr;
	Texture* m_noiseTexture = nullptr;

	//Shaders
	Shader* m_defaultShader = nullptr;
	Shader* m_geometryModelShader = nullptr;

	//Text
	TextLabel* m_menuTitleText = nullptr;
	TextLabel* m_menuInstructText = nullptr;
	TextLabel* m_fpsText = nullptr;

	//Uniforms
	GLfloat u_currentTime = 0;
	int u_frameNum = 0;

	//Debug stuff
	bool m_FogRenderMode = true;
	bool m_WireframeRenderMode = false;
};

