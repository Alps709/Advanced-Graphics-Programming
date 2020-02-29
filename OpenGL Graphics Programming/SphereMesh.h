#pragma once

#include <glew.h>
#include <freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Mesh.h"

class SphereMesh : public Mesh
{
public:
	SphereMesh();
	~SphereMesh();
private:
	int DrawType;
};

