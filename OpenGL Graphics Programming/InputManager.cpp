#include "InputManager.h"

#define GLUT_KEY_SHIFT_L 0x0070

void InputManager::Update()
{
	//Set pressed down first keys to the next state
	for (auto& key : KeyState)
	{
		if(key == INPUT_DOWN_FIRST)
		{
			key = INPUT_DOWN;
			continue;
		}
		if (key == INPUT_UP_FIRST)
		{
			key = INPUT_UP;
		}
	}
	
	//Left shift key
	if (SpecialKeyState[GLUT_KEY_SHIFT_L] ==  INPUT_DOWN_FIRST)
	{
		//The key is has now been processed for a frame, so set it to the appropriate state
		 SpecialKeyState[GLUT_KEY_SHIFT_L] =  INPUT_DOWN;
	}

	//Mouse Input
	if ( MouseState[0] ==  INPUT_DOWN_FIRST)
	{	//Left click

		 MouseState[0] =  INPUT_DOWN;
	}
	if ( MouseState[2] ==  INPUT_DOWN_FIRST)
	{	//Right click

		 MouseState[2] =  INPUT_DOWN;
	}

	//Mouse Input
	if (MouseState[0] == INPUT_UP_FIRST)
	{	//Left click

		MouseState[0] = INPUT_UP;
	}
	if (MouseState[2] == INPUT_UP_FIRST)
	{	//Right click

		MouseState[2] = INPUT_UP;
	}
}
