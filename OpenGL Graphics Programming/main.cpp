#include "Debug.h" //Includes glew, so include this first
#include <freeglut.h>
#include <iostream>
#include <fmod.hpp>

#include "TextLabel.h"

#include "Utils.h"
#include "GameManager.h"
#include "Input.h"

GameManager* myGameManager = nullptr;
InputManager& myInputManager = InputManager::getInstance();

void Render();
void Update();

void ProcessInput();

void SetGlobalGLSettings();

int main(int argc, char ** argv)
{
	//Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize((int)inputManager.SCREEN_WIDTH, (int)inputManager.SCREEN_HEIGHT);
	glutCreateWindow("The Snek Game - By Anton Le Prevost-Smith");

	//Print openGL version
	std::cout << "Currently using OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	//Set up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		//If glew setup failed then application will not run graphics correctly
		std::cout << "Glew Initialization Failed. Aborting Application." << std::endl;
		system("pause");
		return 0;
	}

	SetGlobalGLSettings();

	myGameManager = new GameManager();
	
	//KeyBoard input function callbacks
	glutKeyboardFunc(::KeyBoardDown);
	glutKeyboardUpFunc(::KeyBoardUp);
	glutSpecialFunc(::SpecialKeyBoardDown);
	glutSpecialUpFunc(::SpecialKeyBoardUp);

	//Mouse input function callbacks
	glutMouseFunc(::MouseClick);
	glutMotionFunc(::MouseMove);
	glutPassiveMotionFunc(::MousePassiveMove);

	//Screen resize callback
	glutReshapeFunc(::WindowResize);

	//Update and render function callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutMainLoop();

	delete myGameManager;
	return 0;
}

void Render()
{
	myGameManager->Render();
	GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}

void Update()
{
	myGameManager->Update();
}

void SetGlobalGLSettings()
{
	///Set global settings

	//Disable the cursor for the first person camera
	glutWarpPointer(0, 0);
	myInputManager.g_mousePosX = 0;
	myInputManager.g_mousePosY = 0;
	glutSetCursor(GLUT_CURSOR_NONE);

	//Cull the back faces of objects (only do so for 3D)
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	//Normals are calculated counter clockwise
	GLCall(glFrontFace(GL_CCW));

	//Setup alpha blending
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	//Allows the m_program to continue executing after the glutMainLoop()
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Enable depth test (only do so for 3D)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Sets the clear colour when calling glClear()
	GLCall(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));
}