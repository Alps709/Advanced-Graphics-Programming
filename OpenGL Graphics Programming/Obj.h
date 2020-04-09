#pragma once
#include <vector>
#include "Input.h"

//Hold the vertices and indices for basic shapes
namespace Objects
{
	//Scrolling texture
	static std::vector<float> verticesBoid =
	{
		///Quad
		//Position			     //Colour			        //Texture co-ords
		-5.0f, -5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 1.0f,    //Bottom left
		-5.0f,  5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    //Top left
		 5.0f,  5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f,    //Top right
		 5.0f, -5.0f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,    //Bottom right
	};

	static std::vector<unsigned int> indicesBoid =
	{
		//Quad	indices						
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

	//Cube Map vertices
	static std::vector<float> verticesCube =
	{
		//Position              //Colour                    //TexCoords
		-0.5f,   0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
		 0.5f,   0.5f,  0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    0.0f, 0.0f, 1.0f, 1.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		-0.5f,  -0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		-0.5f,   0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    1.0f, 0.0f,

		 0.5f,   0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		 0.5f,  -0.5f,  0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    1.0f, 0.0f, 0.0f, 0.0f,    1.0f, 0.0f,

		-0.5f,   0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		-0.5f,   0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		 0.5f,   0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		 0.5f,   0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    1.0f, 0.0f,

		-0.5f,  -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		 0.5f,  -0.5f, -0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
		 0.5f,  -0.5f,  0.5f,    0.0f, 1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
	};

	//Cube map indices
	static std::vector<GLuint>indicesCube =
	{
		0, 1, 2,
		0, 2, 3,

		7, 6, 5,
		7, 5, 4,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,
	};

	//Cube map indices (just a copy of the cube indices but with the opposite winding order so the normals calculate inwards)
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
