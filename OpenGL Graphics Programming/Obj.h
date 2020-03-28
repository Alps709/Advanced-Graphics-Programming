#pragma once
#include <vector>
#include "Input.h"

namespace Objects
{
	//Scrolling texture
	static std::vector<float> verticesBoid =
	{
		///Bottom right quad
		//Position			     //Colour			        //Texture co-ords
		-5.0f, -5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f,    //Bottom left
		-5.0f,  5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    //Top left
		 5.0f,  5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f,    //Top right
		 5.0f, -5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,    //Bottom right
	};

	static std::vector<unsigned int> indicesBoid =
	{
		//First quad							
		0, 2, 1,
		0, 3, 2,
	};

	//2D Background texture
	static std::vector<float> verticesBackground =
	{
		///Bottom right quad
		//Position															 //Colour			       //Texture co-ords
		-inputManager.HSCREEN_WIDTH, 0.0f, -inputManager.HSCREEN_HEIGHT,	 1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 10.0f,    //Bottom left
		-inputManager.HSCREEN_WIDTH, 0.0f,  inputManager.HSCREEN_HEIGHT,	 1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,    //Top left
		 inputManager.HSCREEN_WIDTH, 0.0f,  inputManager.HSCREEN_HEIGHT,	 1.0f, 1.0f, 1.0f, 1.0f,   10.0f, 0.0f,    //Top right
		 inputManager.HSCREEN_WIDTH, 0.0f, -inputManager.HSCREEN_HEIGHT,	 1.0f, 1.0f, 1.0f, 1.0f,   10.0f, 10.0f,    //Bottom right
	};

	static std::vector<unsigned int> indicesBackground =
	{
		//First quad							
		0, 2, 1,
		0, 3, 2,
	};

	//Cube Map vertices
	static std::vector<float> verticesCubeMap =
	{
		//Position              //Normal                //TexCoords
		-0.5f,   0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f,   0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f,  -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f,   0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

		 0.5f,   0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f,  -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,   0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,   0.5f,  0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,

		-0.5f,  -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	};

	//Cube map indices
	static std::vector<GLuint>indicesCubeMap =
	{
		0, 2, 1,
		0, 3, 2,

		7, 5, 6,
		7, 4, 5,

		8, 10, 9,
		8, 11, 10,

		12, 14, 13,
		12, 15, 14,

		16, 18, 17,
		16, 19, 18,

		20, 22, 21,
		20, 23, 22,
	};
}
