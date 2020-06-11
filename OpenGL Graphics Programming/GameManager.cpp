#include "GameManager.h"
#include "Obj.h"
#include "Cube.h"
#include "Input.h"
#include "Terrain.h"
#include "WaterTerrain.h"
#include "GeometryObject.h"
#include "TessellationObject.h"
#include "FrameBuffer.h"
#include <fmod.h>

glm::vec3 tempVec{};
bool RaySphereIntersection(const GameObject& _object, const Camera& _camera, glm::vec3 _rayDir, glm::vec3& _intersectionPoint);
bool RayAABBIntersection(const GameObject& _object, const Camera& _camera, glm::vec3 _rayDir, glm::vec3& _intersectionPoint);


GameManager::GameManager()
{
	//Start clock
	m_clock.Initialise();

	//Start audio system
	//AudioInitialise();

	//Create defaut shader
	m_defaultShader = new Shader();

	//Create Cube map
	m_CubeMap.Initialise();
	m_CubeMap.ChangePRS(0.0f, 0.0f, 0.0f, 0.0f, 200000.0f, 200000.0f, 200000.f);

	//Set background mesh and texture
	m_grassTexture = new Texture("Resources/Textures/Grass.png", 0);
	m_noiseTexture = new Texture("Resources/Textures/perlin_noise.png", 2);

	//Terrain
	m_grassTerrain = new Terrain(128, 128, glm::vec3(0.0f), true);
	m_waterTerrain = new WaterTerrain(128, 128, glm::vec3(0.0f), m_noiseTexture);

	m_geometryObject = new GeometryObject(glm::vec3(70.0f, 10.0f, 64.0f), glm::vec4(0.5f, 0.0f, 0.7f, 1.0f));
	m_tesselationObject = new TessellationObject(glm::vec3(70.0f, 12.0f, 64.0f), glm::vec4(0.5f, 0.0f, 0.7f, 1.0f));

	m_frameBuffer = new FrameBuffer(static_cast<int>(inputManager.GL_SCREEN_WIDTH), static_cast<int>(inputManager.GL_SCREEN_HEIGHT));
	
	m_cube  = new Cube(glm::vec3(70.0f, m_grassTerrain->GetTerrainHeight(70.0f, 64.0f) + 0.5f, 64.0f), m_grassTexture, glm::vec4(0.1f, 0.1f, 0.7f, 1.0f), true);
	m_cube1 = new Cube(glm::vec3(70.0f, 10.0f, 60.0f), m_grassTexture, glm::vec4(0.7f, 0.1f, 0.1f, 1.0f), false);
	m_cube2 = new Cube(glm::vec3(70.0f, 10.0f, 68.0f), m_grassTexture, glm::vec4(0.1f, 0.4f, 0.1f, 1.0f), false);

	//Create the text objects
	glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_fpsText                = new TextLabel("FPS: ", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.5f));
	m_toggleOptionsText      = new TextLabel("Toggle options: ", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f), colour, 0.5f);
	m_frameBufferInfoText    = new TextLabel("p - Framebuffer", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f * 2.0f), colour, 0.5f);
	m_wireFrameInfoText      = new TextLabel("o - Wireframe mode", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f * 3.0f), colour, 0.5f);
	m_fogInfoText            = new TextLabel("i - Fog render mode", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f * 4.0f), colour, 0.5f);
	m_geomertryGrassInfoText = new TextLabel("u - Geometry shader grass", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f * 5.0f), colour, 0.5f);
	m_thirdPersonInfoText    = new TextLabel("m - Third person mode (use WASD to move)", "Resources/Fonts/arial.ttf", glm::vec2(-inputManager.GL_HSCREEN_WIDTH + 20.0f, inputManager.GL_HSCREEN_HEIGHT * 0.25f - 50.0f * 6.0f), colour, 0.5f);
	m_menuTitleText          = new TextLabel("Graphics showcase!", "Resources/Fonts/arial.ttf", glm::vec2(-625, 160), glm::vec3(0.0f, 1.0f, 1.0f), 2.0f);
	m_menuInstructText       = new TextLabel("Press enter to continue", "Resources/Fonts/arial.ttf", glm::vec2(-600, -200), glm::vec3(0.0f, 1.0f, 1.0f), 1.5f);

	//Create the camera
	//Set freeview to false at the start
	m_camera = new Camera(false);
	m_camera->SetThirdPersonGameObject(m_cube);

	m_particleSystem = ParticleSystem(glm::vec3(70.0f, 10.0f, 64.0f), 5.0f);
	m_particleSystemCS = ParticleSystemCS(glm::vec3(70.0f, 10.0f, 64.0f), 5.0f);
}


GameManager::~GameManager()
{
	//Delete all the heap allocated objects and clean up others
	delete m_fpsText;
	delete m_menuTitleText;
	delete m_menuInstructText;
	delete m_grassTexture;
	delete m_noiseTexture;
	delete m_defaultShader;
	delete m_geometryModelShader;
	delete m_camera;
	delete m_grassTerrain;
	delete m_waterTerrain;
	delete m_cube;
	delete m_cube1;
	delete m_cube2;
	delete m_geometryObject;
	delete m_tesselationObject;
	delete m_frameBuffer;
	delete m_toggleOptionsText;
	delete m_frameBufferInfoText;
	delete m_wireFrameInfoText;
	delete m_fogInfoText;
	delete m_geomertryGrassInfoText;
	delete m_thirdPersonInfoText;
}		   

void GameManager::ProcessInput()
{
	float deltaTime = static_cast<float>(m_clock.GetDeltaTick());
	
	//Enter key is pressed
	if (inputManager.KeyState[13] == INPUT_DOWN || inputManager.KeyState[13] == INPUT_DOWN_FIRST)
	{
		//Start game from menu by pressing the enter key
		if (m_gameState == GAME_MENU)
		{
			//Set game state to play
			m_gameState = GAME_PLAY;

			m_camera->SetFreeView(true);
		}
	}

	if (m_camera->GetThirdPersonMode())
	{
		//Move the camera forward with the w button
		if (inputManager.KeyState['w'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['w'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['W'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['W'] == inputManager.INPUT_DOWN)
		{
			//move along the x axis
			auto tempPos = m_cube->GetPosition();
			auto deltaX = 0.01f;
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x + deltaX, tempPos.z);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y / 2.0f) - tempPos.y;
			m_cube->ChangePRS(deltaX * deltaTime, deltaYPos, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		//Move the camera to the left with the a button
		if (inputManager.KeyState['a'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['a'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['A'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['A'] == inputManager.INPUT_DOWN)
		{
			//move along z axis
			auto tempPos = m_cube->GetPosition();
			auto deltaZ = -0.01f;
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x, tempPos.z + deltaZ);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y / 2.0f) - tempPos.y;
			m_cube->ChangePRS(0.0f, deltaYPos, deltaZ * deltaTime, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		//Move the camera backwards with the s button
		if (inputManager.KeyState['s'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['s'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['S'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['S'] == inputManager.INPUT_DOWN)
		{
			//move along the x axis
			auto tempPos = m_cube->GetPosition();
			auto deltaX = -0.01f;
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x + deltaX, tempPos.z);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y / 2.0f) - tempPos.y;
			m_cube->ChangePRS(deltaX * deltaTime, deltaYPos, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		//Move the camera to the right witht the d button
		if (inputManager.KeyState['d'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['d'] == inputManager.INPUT_DOWN ||
			inputManager.KeyState['D'] == inputManager.INPUT_DOWN_FIRST || inputManager.KeyState['D'] == inputManager.INPUT_DOWN)
		{
			///move along z axis
			auto tempPos = m_cube->GetPosition();
			auto deltaZ = 0.01f;
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x, tempPos.z + deltaZ);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y / 2.0f) - tempPos.y;
			m_cube->ChangePRS(0.0f, deltaYPos, deltaZ * deltaTime, 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	//'R' key is pressed
	if (inputManager.KeyState['r'] == INPUT_DOWN_FIRST || inputManager.KeyState['R'] == INPUT_DOWN_FIRST)
	{
		//Reset the things
		Reset();
	}

	//'U' key is pressed
	if (inputManager.KeyState['u'] == INPUT_DOWN_FIRST || inputManager.KeyState['U'] == INPUT_DOWN_FIRST)
	{
		m_terrainGrassShaderMode = !m_terrainGrassShaderMode;
	}

	//'U' key is pressed
	if (inputManager.KeyState['y'] == INPUT_DOWN_FIRST || inputManager.KeyState['Y'] == INPUT_DOWN_FIRST)
	{
		m_particleComputerShaderMode = !m_particleComputerShaderMode;
	}

	//'P' key is pressed
	if (inputManager.KeyState['p'] == INPUT_DOWN_FIRST || inputManager.KeyState['P'] == INPUT_DOWN_FIRST)
	{
		m_postProcessingMode = !m_postProcessingMode;
	}

	//'O' key is pressed
	if (inputManager.KeyState['o'] == INPUT_DOWN_FIRST || inputManager.KeyState['O'] == INPUT_DOWN_FIRST)
	{
		//Turn wireframe mode on/off
		m_WireframeRenderMode = !m_WireframeRenderMode;

		if (m_WireframeRenderMode)
		{
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		else
		{
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
	}

	//'I' key is pressed
	if (inputManager.KeyState['i'] == INPUT_DOWN_FIRST || inputManager.KeyState['I'] == INPUT_DOWN_FIRST)
	{
		//Turn fog render mode on/off
		m_FogRenderMode = !m_FogRenderMode;
	}

	//Mouse Input
	if (inputManager.MouseState[0] == INPUT_DOWN)
	{	//Left click

		if (m_currentIntersected == m_cube1)
		{
			auto tempPos = m_cube->GetPosition();
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x, tempPos.z);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y/2.0f) - tempPos.y;
			m_cube->ChangePRS(0.01f * deltaTime, deltaYPos, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		else if (m_currentIntersected == m_cube2)
		{
			auto tempPos = m_cube->GetPosition();
			auto terrainHeight = m_grassTerrain->GetTerrainHeight(tempPos.x, tempPos.z);
			float deltaYPos = terrainHeight + (m_cube->GetScale().y / 2.0f) - tempPos.y;
			m_cube->ChangePRS(-0.01f * deltaTime, deltaYPos, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
}

void GameManager::Update()
{
	//Update clock
	m_clock.Process();
	const double deltaTime = m_clock.GetDeltaTick();

	//Calculate the current FPS based on the delta time
	std::string tempText = "FPS: ";

	const int fps = static_cast<int>(1000.0 / deltaTime);
	tempText = tempText + std::to_string(fps);
	
	m_fpsText->SetText(tempText);

	m_camera->ProcessInput(deltaTime);

	m_mousePicker.UpdateRay(*m_camera);
	
	FindCurrentIntersectedObject();

	ProcessInput();

	if (m_currentIntersected)
	{
		dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = true;
	}

	//Update game play state here
	if (m_gameState == GAME_PLAY)
	{
		if(m_particleComputerShaderMode)
		{
			m_particleSystemCS.Update((float)deltaTime);
		}
		else
		{
			m_particleSystem.Update(*m_camera, (float)deltaTime);
		}
		
	}

	//Update key states with new input for the frame after this one
	inputManager.Update();

	inputManager.g_mousePosDifX = 0;
	inputManager.g_mousePosDifY = 0;

	//Tell glut to call the render function again
	glutPostRedisplay();
}

void GameManager::Render()
{
	const double deltaTime = m_clock.GetDeltaTick();
	//Clear the screen before every frame
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	if(m_postProcessingMode)
	{
		m_frameBuffer->Prepare();
	}
	
	//Draw CubeMap
	m_CubeMap.Render(*m_camera, m_FogRenderMode);

	m_grassTerrain->Render(*m_camera, m_clock.GetTimeElapsedMS(), m_FogRenderMode, m_terrainGrassShaderMode);

	m_cube->Render(*m_camera, m_FogRenderMode);
	m_cube1->Render(*m_camera, m_FogRenderMode);
	m_cube2->Render(*m_camera, m_FogRenderMode);

	m_geometryObject->Render(*m_camera);
	m_tesselationObject->Render(*m_camera);

	//Render game menu non transparent here
	if (m_gameState == GAME_MENU)
	{
		
	}
	//Render game play state non-transparent here
	else if (m_gameState == GAME_PLAY)
	{
		
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
		if(m_particleComputerShaderMode)
		{
			m_particleSystemCS.Render(*m_camera);
		}
		else
		{
			m_particleSystem.Render(*m_camera);
		}
	
		m_fpsText->Render();
		m_toggleOptionsText->Render();
		m_frameBufferInfoText->Render();
		m_wireFrameInfoText->Render();
		m_fogInfoText->Render();
		m_geomertryGrassInfoText->Render();
		m_thirdPersonInfoText->Render();
	}

	if (m_postProcessingMode)
	{
		m_frameBuffer->Render(static_cast<float>(m_clock.GetTimeElapsedS()));
	}

	//Draw crosshair
	glBegin(GL_LINES);
	glVertex2f(-0.045f, 0.0f);
	glVertex2f( 0.045f, 0.0f);
	glVertex2f( 0.0f, 0.08f);
	glVertex2f( 0.0f,-0.08f);
	glEnd();

	glutSwapBuffers();
	u_frameNum++;
}

void GameManager::FindCurrentIntersectedObject()
{
	//Check what object we intersected with first
	glm::vec3 intersectionPoint1;
	glm::vec3 intersectionPoint2;

	bool intersected1 = false;
	bool intersected2 = false;

	//Move the cube along the -x axis if we are clicking on cube1
	intersected1 = RayAABBIntersection(*m_cube1, *m_camera, m_mousePicker.GetRay(), intersectionPoint1);

	//Move the cube along the +x axis if we are clicking on cube2
	intersected2 = RayAABBIntersection(*m_cube2, *m_camera, m_mousePicker.GetRay(), intersectionPoint2);

	//Calculate which cube to move based on which intersection point is closest
	if (intersected1 && intersected2)
	{
		float intersectionDistance1 = glm::length(intersectionPoint1 - m_camera->GetPosition());
		float intersectionDistance2 = glm::length(intersectionPoint2 - m_camera->GetPosition());

		if (intersectionDistance1 < intersectionDistance2)
		{
			if (m_currentIntersected)
			{
				dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = false;
			}
			m_currentIntersected = m_cube1;
			return;
		}
		else
		{
			if (m_currentIntersected)
			{
				dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = false;
			}
			m_currentIntersected = m_cube2;
			return;
		}
	}
	else if (intersected1)
	{
		if (m_currentIntersected)
		{
			dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = false;
		}
		m_currentIntersected = m_cube1;
		return;
	}
	else if (intersected2)
	{
		if (m_currentIntersected)
		{
			dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = false;
		}
		m_currentIntersected = m_cube2;
		return;
	}


	if (m_currentIntersected)
	{
		dynamic_cast<Cube*>(m_currentIntersected)->m_useStencil = false;
	}
	m_currentIntersected = nullptr;
}

void GameManager::Reset()
{
	//Reset camera
	m_camera->ResetView();
	m_camera->SetFreeView(false);
	m_camera->SetPosition(glm::vec3( 64.0f, 10.0f, 64.0f ));
	
	//Reset the position of the cubes
	m_cube->SetPosition (glm::vec3(70.0f, 10.0f, 64.0f));
	m_cube1->SetPosition(glm::vec3(70.0f, 10.0f, 60.0f));
	m_cube2->SetPosition(glm::vec3(70.0f, 10.0f, 68.0f));

	//Set it to main menu mode
	m_gameState = GameState::GAME_MENU;

	//Turn fog on
	m_FogRenderMode = true;

	//Turn wireframe mode off
	m_WireframeRenderMode = false;
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

bool RaySphereIntersection(const GameObject& _object, const Camera& _camera, glm::vec3 _rayDir, glm::vec3& _intersectionPoint)
{
	float radius = (float)_object.GetRadius();
	glm::vec3 rayOrigin = _camera.GetPosition();
	glm::vec3 sphereCenter = _object.GetPosition();
	glm::vec3 cameraToSphere = sphereCenter - _camera.GetPosition();

	//Distance along the ray that is the closest point to the sphere origin
	float t = glm::dot(cameraToSphere, _rayDir);
	//The point in space where the ray is closest to the sphere origin
	glm::vec3 p = rayOrigin + _rayDir * t;

	float y = glm::length(sphereCenter - p);

	if (y < radius)
	{
		//The y is less than the radius so we collided with the sphere!

		//This code finds the distance along the ray where the two intersections are
		//t1 is the closest intersection, t2 is the furtherest intersection
		float x = sqrt(radius * radius - y * y);

		//If the distance to the first intersection is greater or equal to 0 then we hit this intersection first
		if (t-x >= 0)
		{
			_intersectionPoint = rayOrigin + _rayDir * (t - x);
			return true;
		}
		//If the distance to the second intersection point is greater or equal to 0 then we hit this intersection first
		else if (t + x >= 0)
		{
			_intersectionPoint = rayOrigin + _rayDir * (t + x);
			return true;
		}
		//If the distance to the second intersection point is less than 0 then the intersection is behind us and we did not intersect
	}
	//The distance to the closest point on the ray was larger than the sphere radius
	//So there is no intersection
	return false;
}

bool RayAABBIntersection(const GameObject& _object, const Camera& _camera, glm::vec3 _rayDir, glm::vec3& _intersectionPoint)
{
	glm::vec3 rayOrigin = _camera.GetPosition();
	glm::vec3 objScale = _object.GetScale() / 2.0f;

	//Left bottom point of the object AABB
	glm::vec3 lb = glm::vec3(-objScale.x, -objScale.y, -objScale.z);
	lb += _object.GetPosition();

	//Right top point of the object AABB
	glm::vec3 rt = glm::vec3(objScale.x, objScale.y, objScale.z);
	rt += _object.GetPosition();

	//Precalcualte for optimization
	glm::vec3 dirfrac = 1.0f / _rayDir;

	//t is the distance until intersection
	float t;
	float t1 = (lb.x - rayOrigin.x) * dirfrac.x;
	float t2 = (rt.x - rayOrigin.x) * dirfrac.x;
	float t3 = (lb.y - rayOrigin.y) * dirfrac.y;
	float t4 = (rt.y - rayOrigin.y) * dirfrac.y;
	float t5 = (lb.z - rayOrigin.z) * dirfrac.z;
	float t6 = (rt.z - rayOrigin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	_intersectionPoint = rayOrigin + _rayDir * t;
	return true;
}
