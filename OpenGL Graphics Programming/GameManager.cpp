#include "GameManager.h"
#include "Obj.h"
#include "Renderer.h"

#include <fmod.h>
#include "Input.h"


GameManager::GameManager()
{
	//Start clock
	m_clock.Initialise();

	//Start audio system
	AudioInitialise();

	//Create defaut shader
	m_defaultShader = new Shader();
	m_sphereShader = new Shader("Shaders/SphereVS.glsl", "Shaders/SphereFS.glsl");
	m_sphereRimLightShader = new Shader("Shaders/SphereRimLightVS.glsl", "Shaders/SphereRimLightFS.glsl");
	m_sphereCubeMapReflectShader = new Shader("Shaders/CubeMapReflectVS.glsl", "Shaders/CubeMapReflectFS.glsl");
	m_tankModelShader = new Shader("Shaders/TankModelVS.glsl", "Shaders/TankModelFS.glsl");

	//Create Cube map
	m_CubeMap.Initialise();
	m_CubeMap.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 200000.0f, 200000.0f, 200000.f);

	//Set sphere mesh and texture
	m_sphereMesh = new SphereMesh();
	m_sphereTexture = new Texture("Resources/Textures/Grass.png", 0);

	//Create 1 background object
	m_sphereObject = Object(m_sphereMesh, m_defaultShader, glm::vec3(0.0f, 0.0f, 0.0f));
	m_sphereObject.SetTexture0(m_sphereTexture);

	//Set boid mesh and texture
	m_boidMesh = new Mesh(Objects::verticesBoid, Objects::indicesBoid);
	m_boidTexture = new Texture("Resources/Textures/Grass.png", 0);

	//Set background mesh and texture
	/*m_backgroundMesh = new Mesh(Objects::verticesBackground, Objects::indicesBackground);
	m_backgroundTexture = new Texture("Resources/Textures/Grass.png", 0);*/

	//Create 1 background object
	/*m_backgroundObject = Object(m_backgroundMesh, m_defaultShader, glm::vec3(0.0f, 0.0f, -1000.0f));
	m_backgroundObject.SetTexture0(m_backgroundTexture);
	m_backgroundObject.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 0.0f);*/

	//Create random generator for boid positions
	std::random_device dev;
	std::mt19937 rng(dev());
	const std::uniform_real_distribution<double> randXPos(-inputManager.HSCREEN_WIDTH + 50, inputManager.HSCREEN_WIDTH - 50);
	const std::uniform_real_distribution<double> randYPos(-inputManager.HSCREEN_HEIGHT + 50, inputManager.HSCREEN_HEIGHT - 50);

	//Create the text objects
	m_scoreText = new TextLabel("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.HSCREEN_WIDTH + 20.0f, inputManager.HSCREEN_HEIGHT - 40.0f));
	m_menuTitleText = new TextLabel("The Tenk Game!", "Resources/Fonts/kirbyss.ttf", glm::vec2(-625, 200), glm::vec3(0.0f, 1.0f, 1.0f), 2.8f);
	m_menuInstructText = new TextLabel("Press enter to play", "Resources/Fonts/kirbyss.ttf", glm::vec2(-600, -200), glm::vec3(0.0f, 1.0f, 1.0f), 2.0f);
	m_overText = new TextLabel("Game Over!", "Resources/Fonts/kirbyss.ttf", glm::vec2(-625, 200), glm::vec3(1.0f, 0.0f, 0.0f), 4);
	m_overScoreText = new TextLabel("Your final score is: ", "Resources/Fonts/arial.ttf", glm::vec2(-600, -200), glm::vec3(1.0f, 0.0f, 0.0f), 1.5f);

	//Initialise tank model
	myTank = PlayerTank("Resources/Models/Tank/Tank.obj", m_tankModelShader, &m_boidObjects, m_scoreText, m_audioSystem, m_yeatSound, m_shoopSound);
	myTank.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f);

	//Create the camera
	//Pass in false to say it is not using an orthographic view initially (it will then use a perspective view projection)
	m_camera = new Camera(false);
}


GameManager::~GameManager()
{
	//Delete all the heap allocated objects and clean up others
	m_yeatSound->release();
	m_audioSystem->release();
	delete m_sphereMesh;
	delete m_sphereTexture;
	delete m_sphereShader;
	delete m_sphereRimLightShader;
	delete m_sphereCubeMapReflectShader;
	delete m_tankModelShader;
	delete m_scoreText;
	delete m_overText;
	delete m_overScoreText;
	delete m_menuTitleText;
	delete m_menuInstructText;
	delete m_timeText;
	delete m_boidMesh;
	delete m_boidTexture;
	delete m_backgroundMesh;
	delete m_backgroundTexture;
	delete m_defaultShader;
	delete m_camera;
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

	//Mouse Input
	if (inputManager.MouseState[0] == INPUT_DOWN_FIRST || inputManager.MouseState[0] == INPUT_DOWN_FIRST)
	{	//Left click
		//Create 1 bullet sphere
		float frustumLeftSide = 4200;
		float frustumRightSide = -4200;
		float frustumTopSide = 2340;
		float frustumBottomSide = -2340;

		float z = (int)(Utils::remap(inputManager.g_mousePosX, -inputManager.HSCREEN_WIDTH, inputManager.HSCREEN_WIDTH, frustumLeftSide, frustumRightSide));
		float x = (int)(Utils::remap(inputManager.g_mousePosY, -inputManager.HSCREEN_HEIGHT, inputManager.HSCREEN_HEIGHT, frustumBottomSide, frustumTopSide));

		glm::vec3 bulletSeekPos = (glm::vec3(-x, 0.0f, z) - glm::vec3(myTank.GetPosition().x, 0.0f, myTank.GetPosition().z)) * 50.0f;

		Bullet myTempObject = Bullet(m_sphereMesh, m_sphereRimLightShader, myTank.m_position, bulletSeekPos);
		myTempObject.SetTexture0(m_sphereTexture);
		myTempObject.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f);
		m_bulletObjects.push_back(myTempObject);
	}
}

//Do substance abuse here
void GameManager::ProcessBoids()
{
	m_boidSpawnTimer += m_clock.GetDeltaTick();

	//Spawn a boid every 1000 milliseconds
	if (m_boidSpawnTimer > 250)
	{
		//Reset timer
		m_boidSpawnTimer = 0.0;

		//Create random generator for boid positions
		std::random_device dev;
		std::mt19937 rng(dev());
		const std::uniform_real_distribution<double> randXPos(-2300, 2300);
		const std::uniform_real_distribution<double> randZPos(-4000, 4000);

		//Create 1 boid model
		Boid myTempObject = Boid(m_sphereMesh, m_sphereCubeMapReflectShader, glm::vec3(randXPos(rng), 0.0f, randZPos(rng)));
		myTempObject.SetTexture0(m_boidTexture);
		myTempObject.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f);
		m_boidObjects.push_back(myTempObject);
	}

	//Process the movement (seek behaviour) of all the boids
	for (auto boidIt = m_boidObjects.begin(); boidIt != m_boidObjects.end(); ++boidIt)
	{
		boidIt->Process(myTank.GetPosition(), m_clock.GetDeltaTick());
	}

	//Find all bullets that have existed for 5 seconds and erase them from the vector
	for (auto bulletIt = m_bulletObjects.begin(); bulletIt != m_bulletObjects.end();)
	{
		if (bulletIt->GetTimeAlive() > 5.0)
		{
			//Bullet has been alive for more than 5 seconds
			bulletIt = m_bulletObjects.erase(bulletIt);
		}
		else
		{
			bulletIt->Process(m_clock.GetDeltaTick());
			++bulletIt;
		}
	}

	//Find all bullets that are colliding with boids, and delete those boids
	for (auto bulletIt = m_bulletObjects.begin(); bulletIt != m_bulletObjects.end(); ++bulletIt)
	{
		for (auto boidIt = m_boidObjects.begin(); boidIt != m_boidObjects.end();)
		{
			//Find the distance between the boid and the bullet
			float distance = glm::length(bulletIt->GetPosition() - boidIt->GetPosition()) - (bulletIt->GetRadius() + boidIt->GetRadius());

			if (distance <= 0.0)
			{
				//This boid is colliding with the bullet
				//So delete the boid
				boidIt = m_boidObjects.erase(boidIt);
				++m_gameScore;

				std::string tempText = "Score: ";
				tempText.append(std::to_string(m_gameScore));
				m_scoreText->SetText(tempText);
			}
			else
			{
				++boidIt;
			}
		}
	}
}

void GameManager::Update()
{
	//Update clock
	m_clock.Process();
	m_camera->ProcessInput();
	ProcessInput();

	if (m_gameState == GAME_PLAY)
	{
		if (!inputManager.CAMERA_FREEEVIEW_MODE)
		{
			myTank.Update(m_gameScore, m_clock.GetDeltaTick());

			//Process boid spawning and despawning
			ProcessBoids();
		}
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
	Renderer::Clear();

	//Draw CubeMap
	m_CubeMap.Render(*m_camera);

	myTank.Render(*m_camera);

	if (m_gameState == GAME_MENU)
	{
		m_menuTitleText->Render();
		m_menuInstructText->Render();
	}
	else if (m_gameState == GAME_PLAY)
	{
		//Render boids
		for (auto& boid : m_boidObjects)
		{
			boid.Render(*m_camera);
		}

		//Render boids
		for (auto& bullets : m_bulletObjects)
		{
			bullets.Render(*m_camera);
		}

		m_scoreText->Render();
	}
	else if (m_gameState == GAME_OVER)
	{
		std::string tempText = "Your final score is: ";
		tempText = tempText + std::to_string(m_gameScore);

		m_overScoreText->SetText(tempText);
		m_overText->Render();
		m_overScoreText->Render();
	}

	glutSwapBuffers();
	u_frameNum++;
}