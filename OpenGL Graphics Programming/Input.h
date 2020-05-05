#pragma once
#include "Debug.h"
#include "Math.h"
#include <freeglut.h>

//Callback functions for glut input
namespace
{
	inline InputManager& inputManager = inputManager.getInstance();

	enum InputState
	{
		INPUT_NULL = 0, //Default key state (can be used to tell is a key has ever been pressed)
		INPUT_UP = 1,
		INPUT_DOWN = 2,
		INPUT_UP_FIRST = 3,
		INPUT_DOWN_FIRST = 4,
	};

	//Declared inputs to be handled that have an uppercase and lowercase version
	unsigned char inputs[10] = { 'w', 'a', 's', 'd', 'p', 'W', 'A', 'S', 'D', 'P' };

	

	void MouseClick(int _button, int _state, int _x, int _y)
	{
		//Convert current screen width and height mouse co-ords to 
		//move the co-ords from (0, 0) at top left, to (0, 0) at middle of screen
		//(remaps screen size mouse coords to opengl pixel coords)
		int x = (int)Math::remap(_x, 0, inputManager.WINDOW_SCREEN_WIDTH, -inputManager.GL_HSCREEN_WIDTH, inputManager.GL_HSCREEN_WIDTH);
		int y = (int)Math::remap(_y, 0, inputManager.WINDOW_SCREEN_HEIGHT, -inputManager.GL_HSCREEN_HEIGHT, inputManager.GL_HSCREEN_HEIGHT);

		//Invert y axis
		y *= -1;

		inputManager.g_mousePosDifX = x - inputManager.g_mousePosX;
		inputManager.g_mousePosDifY = y - inputManager.g_mousePosY;

		if (!inputManager.CAMERA_FREEEVIEW_MODE)
		{
			inputManager.g_mousePosX = x;
			inputManager.g_mousePosY = y;
		}
		else
		{
			glutWarpPointer((int)inputManager.WINDOW_HSCREEN_WIDTH, (int)inputManager.WINDOW_HSCREEN_HEIGHT);
			inputManager.g_mousePosX = 0;
			inputManager.g_mousePosY = 0;
		}

		inputManager.MouseState[_button] = (GLUT_DOWN == _state) ? inputManager.INPUT_DOWN_FIRST : inputManager.INPUT_UP_FIRST;
		//Debug logging
		//std::cout << "Mouse clicked on - x: " << x << " | y: " << y << std::endl;
	}

	void MousePassiveMove(int _x, int _y)
	{
		//Convert current screen width and height mouse co-ords to 
		//move the co-ords from (0, 0) at top left, to (0, 0) at middle of screen
		//(remaps screen size mouse coords to opengl pixel coords)
		int x = (int)Math::remap(_x, 0, inputManager.WINDOW_SCREEN_WIDTH, -inputManager.GL_HSCREEN_WIDTH, inputManager.GL_HSCREEN_WIDTH);
		int y = (int)Math::remap(_y, 0, inputManager.WINDOW_SCREEN_HEIGHT, -inputManager.GL_HSCREEN_HEIGHT, inputManager.GL_HSCREEN_HEIGHT);

		//Invert y axis
		y *= -1;

		std::cout << "_x = " << _x << std::endl;
		std::cout << "_y = " << _y << std::endl;

		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;

		inputManager.g_mousePosDifX = x - inputManager.g_mousePosX;
		inputManager.g_mousePosDifY = y - inputManager.g_mousePosY;

		if (!inputManager.CAMERA_FREEEVIEW_MODE)
		{
			inputManager.g_mousePosX = x;
			inputManager.g_mousePosY = y;
		}
		else
		{
			glutWarpPointer((int)inputManager.WINDOW_HSCREEN_WIDTH, (int)inputManager.WINDOW_HSCREEN_HEIGHT);
			inputManager.g_mousePosX = 0;
			inputManager.g_mousePosY = 0;
		}
		////Debug logging
		//std::cout << "Mouse moved to - x: " << x << " | y: " << y << std::endl;
		//std::cout << "Mouse change in - x: " << inputManager.g_mousePosDifX << " | y: " << inputManager.g_mousePosDifY << std::endl;
	}

	void MouseMove(int _x, int _y)
	{
		//Convert current screen width and height mouse co-ords to 
		//move the co-ords from (0, 0) at top left, to (0, 0) at middle of screen
		//(remaps screen size mouse coords to opengl pixel coords)
		int x = (int)Math::remap(_x, 0, inputManager.WINDOW_SCREEN_WIDTH, -inputManager.GL_HSCREEN_WIDTH, inputManager.GL_HSCREEN_WIDTH);
		int y = (int)Math::remap(_y, 0, inputManager.WINDOW_SCREEN_HEIGHT, -inputManager.GL_HSCREEN_HEIGHT, inputManager.GL_HSCREEN_HEIGHT);

		//Invert y axis
		y *= -1;

		std::cout << "_x = " << _x << std::endl;
		std::cout << "_y = " << _y << std::endl;

		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;

		inputManager.g_mousePosDifX = x - inputManager.g_mousePosX;
		inputManager.g_mousePosDifY = y - inputManager.g_mousePosY;

		if (!inputManager.CAMERA_FREEEVIEW_MODE)
		{
			inputManager.g_mousePosX = x;
			inputManager.g_mousePosY = y;
		}
		else
		{
			glutWarpPointer((int)inputManager.WINDOW_HSCREEN_WIDTH, (int)inputManager.WINDOW_HSCREEN_HEIGHT);
			inputManager.g_mousePosX = 0;
			inputManager.g_mousePosY = 0;
		}
		//Debug logging
		//std::cout << "Mouse clicked on - x: " << _x << " | y: " << _y << std::endl;
		//std::cout << "Mouse change in - x: " << g_mousePosDifX << " | y: " << g_mousePosDifY << std::endl;
	}

	void KeyBoardUp(unsigned char _key, int _x, int _y)
	{
		const int tempState = inputManager.KeyState[_key];

		//Find offset of the corresponding uppercase or lowercase key
		const int offset = (_key < 97) ? 32 : -32;

		//If the key is down
		if (tempState != inputManager.INPUT_UP && tempState != inputManager.INPUT_UP_FIRST)
		{
			//Loop through the currently handled input keys
			for (unsigned char input : inputs)
			{
				//If the key is declared to be handled
				if (_key == input)
				{
					//Set the the corresponding uppercase or lowercase key aswell
					inputManager.KeyState[_key + offset] = inputManager.INPUT_UP_FIRST;
					break;
				}
			}
			//Continue to change keystate as normal
			inputManager.KeyState[_key] = inputManager.INPUT_UP_FIRST;
		}
	}

	void KeyBoardDown(unsigned char _key, int _x, int _y)
	{
		const int tempState = inputManager.KeyState[_key];
		const int offset = (_key < 97) ? 32 : -32;

		//Key is up
		if (tempState != inputManager.INPUT_DOWN && tempState != inputManager.INPUT_DOWN_FIRST)
		{
			for (unsigned char input : inputs)
			{
				if (_key == input)
				{
					inputManager.KeyState[_key + offset] = inputManager.INPUT_DOWN_FIRST;
					break;
				}
			}
			inputManager.KeyState[_key] = inputManager.INPUT_DOWN_FIRST;
		}
	}

	//Special key up function
	void SpecialKeyBoardUp(int _key, int _x, int _y)
	{
		const int tempState = inputManager.SpecialKeyState[_key];

		if (tempState != inputManager.INPUT_UP && tempState != inputManager.INPUT_UP_FIRST)
		{
			inputManager.SpecialKeyState[_key] = inputManager.INPUT_UP_FIRST;
		}
	}

	//Special key down function
	void SpecialKeyBoardDown(int _key, int _x, int _y)
	{
		const int tempState = inputManager.SpecialKeyState[_key];

		if (tempState != inputManager.INPUT_DOWN && tempState != inputManager.INPUT_DOWN_FIRST)
		{
			inputManager.SpecialKeyState[_key] = inputManager.INPUT_DOWN_FIRST;
		}
	}

	void WindowResize(int _x, int _y)
	{
		inputManager.WINDOW_SCREEN_WIDTH = _x;
		inputManager.WINDOW_SCREEN_HEIGHT = _y;
		inputManager.WINDOW_HSCREEN_HEIGHT = inputManager.WINDOW_SCREEN_HEIGHT / 2;
		inputManager.WINDOW_HSCREEN_WIDTH = inputManager.WINDOW_SCREEN_WIDTH / 2;

		glViewport((GLsizei)0, (GLsizei)0, (GLsizei)inputManager.WINDOW_SCREEN_WIDTH, (GLsizei)inputManager.WINDOW_SCREEN_HEIGHT);
		glScissor(0, (GLsizei)(inputManager.WINDOW_SCREEN_HEIGHT * 0.1f), (GLsizei)inputManager.WINDOW_SCREEN_WIDTH, (GLsizei)(inputManager.WINDOW_SCREEN_HEIGHT * 0.8f));
	}
}
