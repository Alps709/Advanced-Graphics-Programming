#include "GameManager.h"
#include "Obj.h"

#include <fmod.h>
#include "Input.h"


GameManager::GameManager()
{
	//Start clock
	m_clock.Initialise();

	//Start audio system
	//AudioInitialise();

	//Create defaut shader
	m_defaultShader = new Shader();
	m_sphereShader = new Shader("Shaders/SphereVS.glsl", "Shaders/SphereFS.glsl");
	m_sphereRimLightShader = new Shader("Shaders/SphereRimLightVS.glsl", "Shaders/SphereRimLightFS.glsl");
	m_sphereCubeMapReflectShader = new Shader("Shaders/CubeMapReflectVS.glsl", "Shaders/CubeMapReflectFS.glsl");

	//Create Cube map
	m_CubeMap.Initialise();
	m_CubeMap.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 200000.0f, 200000.0f, 200000.f);

	//Set background mesh and texture
	//m_backgroundMesh = new Mesh(Objects::verticesBackground, Objects::indicesBackground);
	m_grassTexture = new Texture("Resources/Textures/Grass.png", 0);
	m_noiseTexture = new Texture("Resources/Textures/perlin_noise.png", 1);

	//Terrain
	m_grassTerrain = new Terrain(128, 128, glm::vec3(0.0f), m_grassTexture);
	m_waterTerrain = new WaterTerrain(128, 128, glm::vec3(0.0f), m_grassTexture, m_noiseTexture);

	m_cube = new Cube(glm::vec3(70.0f, 5.0f, 70.0f), m_grassTexture);

	//Create the text objects
	m_fpsText = new TextLabel("FPS: ", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.HSCREEN_WIDTH + 20.0f, inputManager.HSCREEN_HEIGHT * 0.5f));
	m_menuTitleText = new TextLabel("Graphics showcase!", "Resources/Fonts/kirbyss.ttf", glm::vec2(-625, 160), glm::vec3(0.0f, 1.0f, 1.0f), 2.0f);
	m_menuInstructText = new TextLabel("Press enter to continue", "Resources/Fonts/kirbyss.ttf", glm::vec2(-600, -200), glm::vec3(0.0f, 1.0f, 1.0f), 2.0f);

	//Create the camera
	//Set freeview to false at the start
	m_camera = new Camera(false);
}


GameManager::~GameManager()
{
	//Delete all the heap allocated objects and clean up others
	m_yeatSound->release();
	m_audioSystem->release();
	delete m_sphereShader;
	delete m_sphereRimLightShader;
	delete m_sphereCubeMapReflectShader;
	delete m_tankModelShader;
	delete m_fpsText;
	delete m_overText;
	delete m_overScoreText;
	delete m_menuTitleText;
	delete m_menuInstructText;
	delete m_timeText;
	delete m_grassTexture;
	delete m_noiseTexture;
	delete m_defaultShader;
	delete m_camera;
	delete m_grassTerrain;
	delete m_waterTerrain;
	delete m_cube;
}

void GameManager::AudioInitialise()
{
	FMOD_RESULT result;
	//Initialise the m_audioSystem
	result = FMOD::System_Create(&m_audioSystem);
	if (result != FMOD_OK)
	{
		std::cout << "Audio system failed to initialise!";
		return;
	}

	result = m_audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		std::cout << "Audio system failed to initialise!";
	}
	else
	{
		result = m_audioSystem->createSound("Resources/Audio/yeat.wav", FMOD_DEFAULT, 0, &m_yeatSound);
		if (result != FMOD_OK)
		{
			std::cout << "Failed to load sound: yeat.wav" << std::endl;
		}

		result = m_audioSystem->createSound("Resources/Audio/shoop.wav", FMOD_DEFAULT, 0, &m_shoopSound);
		if (result != FMOD_OK)
		{
			std::cout << "Failed to load sound: shoop.wav" << std::endl;
		}

		//Create background music
		result = m_audioSystem->createSound("Resources/Audio/Jet Set Run.mp3", FMOD_LOOP_NORMAL, 0, &m_trackBackground);
		if (result != FMOD_OK)
		{
			std::cout << "Failed to load sound: Jet Set Run.mp3" << std::endl;
		}
		else
		{
			//Created sound
			//Start playing background music
			const FMOD_RESULT play = m_audioSystem->playSound(m_trackBackground, 0, false, 0);
			if (play != FMOD_OK)
			{
				std::cout << "Failed to play background track: You Say Run.mp3" << std::endl;
			}
		}
	}
}

void GameManager::ProcessInput()
{
	//Enter key is pressed
	if (inputManager.KeyState[13] == INPUT_DOWN || inputManager.KeyState[13] == INPUT_DOWN_FIRST)
	{
		//Start game from menu by pressing the enter key
		if (m_gameState == GAME_MENU)
		{
			//Set game state to play
			m_gameState = GAME_PLAY;
		}
	}

	//'O' key is pressed
	if (inputManager.KeyState['o'] == INPUT_DOWN_FIRST || inputManager.KeyState['O'] == INPUT_DOWN_FIRST)
	{
		//Turn wireframe mode on/off
		m_WireframeRenderMode = !m_WireframeRenderMode;

		if (m_WireframeRenderMode)
		{
			GLCall(glPolygonMode(GL_FRONT, GL_LINE));
		}
		else
		{
			GLCall(glPolygonMode(GL_FRONT, GL_FILL));
		}
	}

	//'O' key is pressed
	if (inputManager.KeyState['i'] == INPUT_DOWN_FIRST || inputManager.KeyState['I'] == INPUT_DOWN_FIRST)
	{
		//Turn fog render mode on/off
		m_FogRenderMode = !m_FogRenderMode;
	}

	//Mouse Input
	if (inputManager.MouseState[0] == INPUT_DOWN_FIRST)
	{	//Left click

	}
}

void GameManager::Update()
{
	//Update clock
	m_clock.Process();
	double deltaTime = m_clock.GetDeltaTick();

	//Calculate the current FPS based on the delta time
	std::string tempText = "FPS: ";

	int fps = int(1000.0 / deltaTime);
	tempText = tempText + std::to_string(fps);
	
	m_fpsText->SetText(tempText);

	m_camera->ProcessInput(deltaTime);
	ProcessInput();

	//Update game play state here
	if (m_gameState == GAME_PLAY)
	{

	}

	//Update sounds
	m_audioSystem->update();

	//Update key states with new input
	inputManager.Update();

	//Tell glut to call the render function again
	glutPostRedisplay();
}

void GameManager::Render()
{
	//Clear the screen before every frame
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	//Draw CubeMap
	m_CubeMap.Render(*m_camera, m_FogRenderMode);

	m_grassTerrain->Render(*m_camera, m_clock.GetTimeElapsedMS(), m_FogRenderMode);

	//Render game menu non transparent here
	if (m_gameState == GAME_MENU)
	{
		
	}
	//Render game play state non-transparent here
	else if (m_gameState == GAME_PLAY)
	{
		m_cube->Render(*m_camera, m_FogRenderMode);
	}

	///Render transparent objects last

	//Transparent water terrain
	m_waterTerrain->Render(*m_camera, m_clock.GetTimeElapsedMS(), m_FogRenderMode);

	//transparent text
	if (m_gameState == GAME_MENU)
	{
		m_menuTitleText->Render();
		m_menuInstructText->Render();
	}
	else if (m_gameState == GAME_PLAY)
	{
		m_fpsText->Render();
	}

	glutSwapBuffers();
	u_frameNum++;
}