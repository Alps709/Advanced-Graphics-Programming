#pragma once
#include "Terrain.h"

class WaterTerrain : public Terrain
{
public:

	WaterTerrain(unsigned int _xSize, unsigned int _zSize, glm::vec3 _position, Texture* _terrainTexture, Texture* _noiseTexture);

	void SetShaderUniforms(Camera& _myCamera, double _time) const override;
	void Render(Camera& _myCamera, double _time) override;
};

