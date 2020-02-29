#pragma once
#include <iostream>
#include "glm.hpp"

namespace Utils
{
	//Remaps a value from one number range to another (used to remap mouse co-ord from world space to screen space)
	static double remap(double _value, double _oldMin, double _oldMax, double _newMin, double _newMax)
	{
		if(_oldMin == _oldMax)
		{
			std::cout << "\nError: Remap input value range is zero!\n";
			return 0;
		}

		if (_newMin == _newMax)
		{
			std::cout << "\nError: Remap output value range is zero!\n";
			return 0;
		}

		//Check for reversed input range
		bool reversedInput = false;
		const double oldMin = glm::min(_oldMin, _oldMax);
		const double oldMax = glm::max(_oldMin, _oldMax);
		if(oldMin != _oldMin)
		{
			reversedInput = true;
		}

		//Check for reversed output range
		bool reversedOutput = false;
		const double newMin = glm::min(_newMin, _newMax);
		const double newMax = glm::max(_newMin, _newMax);
		if (newMin != _newMin)
		{
			reversedOutput = true;
		}

		double portion = (_value - oldMin) * (newMax - newMin) / (oldMax - oldMin);
		if(reversedInput)
		{
			portion = (oldMin - _value) * (newMax - newMin) / (oldMax - oldMin);
		}

		return (reversedOutput) ? (newMax - portion) : (portion + newMin);
	}
}