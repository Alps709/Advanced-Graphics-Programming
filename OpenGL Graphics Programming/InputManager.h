#pragma once

class InputManager
{

public:
	static InputManager& getInstance()
	{
		static InputManager instance; // Guaranteed to be destroyed.
		return instance;
	}
	
	void Update();

	enum InputState
	{
		INPUT_NULL = 0,
		INPUT_UP = 1,
		INPUT_DOWN = 2,
		INPUT_UP_FIRST = 3,
		INPUT_DOWN_FIRST = 4,
	};

	double g_mousePosX = 0;
	double g_mousePosY = 0;
	double g_mousePosDifX = 0;
	double g_mousePosDifY = 0;

	bool CAMERA_FREEEVIEW_MODE = false;

	//Game window size
	double GL_SCREEN_WIDTH = 1280.0f;
	double GL_SCREEN_HEIGHT = 720.0f;
	double GL_HSCREEN_WIDTH = GL_SCREEN_WIDTH / 2.0f;
	double GL_HSCREEN_HEIGHT = GL_SCREEN_HEIGHT / 2.0f;

	//True window size (set in the windowResize function callback)
	double WINDOW_SCREEN_WIDTH = GL_SCREEN_WIDTH;
	double WINDOW_SCREEN_HEIGHT = GL_SCREEN_HEIGHT;
	double WINDOW_HSCREEN_WIDTH = GL_HSCREEN_WIDTH;
	double WINDOW_HSCREEN_HEIGHT = GL_HSCREEN_HEIGHT;

	//Mouse Input
	InputState MouseState[3];

	//Keyboard input
	InputState KeyState[255];
	InputState SpecialKeyState[255];

private:
	InputManager() {}                  

public:
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;
};

