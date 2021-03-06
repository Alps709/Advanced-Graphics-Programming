#pragma once
#include "clock.h"
#include "MousePicker.h"
#include "TextLabel.h"
#include "Texture.h"
#include "GameObject.h"
#include "CubeMap.h"
#include "Model.h"

#include <fmod.hpp>

#include "ParticleSystem.h"
#include "ParticleSystemCS.h"

class Cube;
class GeometryObject;
class TessellationObject;
class Terrain;
class WaterTerrain;
class FrameBuffer;

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

	//Particle system
	ParticleSystem* m_particleSystem;
	ParticleSystemCS* m_particleSystemCS;

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

	//Tesselation shader model
	TessellationObject* m_tesselationObject = nullptr;

	//Frame buffer
	FrameBuffer* m_frameBuffer = nullptr;

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
	TextLabel* m_toggleOptionsText = nullptr;
	TextLabel* m_particleSystemInfoText = nullptr;
	TextLabel* m_wireFrameInfoText = nullptr;
	TextLabel* m_fogInfoText = nullptr;
	TextLabel* m_geomertryGrassInfoText = nullptr;
	TextLabel* m_thirdPersonInfoText = nullptr;
	TextLabel* m_animatedWaterInfoText = nullptr;

	//Uniforms
	GLfloat u_currentTime = 0;
	int u_frameNum = 0;

	//Debug stuff
	bool m_FogRenderMode = true;
	bool m_WireframeRenderMode = false;
	bool m_postProcessingMode = false;
	bool m_terrainGrassShaderMode = false;
	bool m_particleComputerShaderMode = false;
	bool m_animatedWaterMode = true;
};

