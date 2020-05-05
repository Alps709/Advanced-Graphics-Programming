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

	int g_mousePosX = 0;
	int g_mousePosY = 0;
	int g_mousePosDifX = 0;
	int g_mousePosDifY = 0;

	bool CAMERA_FREEEVIEW_MODE = false;

	//Game window size
	double GL_SCREEN_WIDTH = 1280.0;
	double GL_SCREEN_HEIGHT = 720.0;
	double GL_HSCREEN_WIDTH = GL_SCREEN_WIDTH / 2.0;
	double GL_HSCREEN_HEIGHT = GL_SCREEN_HEIGHT / 2.0;

	//True window size (set in the windowResize function callback)
	int WINDOW_SCREEN_WIDTH = (int)GL_SCREEN_WIDTH;
	int WINDOW_SCREEN_HEIGHT = (int)GL_SCREEN_HEIGHT;
	int WINDOW_HSCREEN_WIDTH = (int)GL_HSCREEN_WIDTH;
	int WINDOW_HSCREEN_HEIGHT = (int)GL_HSCREEN_HEIGHT;

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

