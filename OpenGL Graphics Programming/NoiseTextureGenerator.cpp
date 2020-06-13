#include "NoiseTextureGenerator.h"

#include <iostream>

#include "FastNoise.h"

NoiseTextureGenerator::~NoiseTextureGenerator()
{
	delete m_tex;
	delete m_pixelData;
}

Texture* NoiseTextureGenerator::GenerateTexture()
{
	m_clock.Initialise();
	
	FastNoise noiseGenerator;
	noiseGenerator.SetSeed(static_cast<int>(m_clock.GetCurrentTime()));
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(5);
	noiseGenerator.SetFractalLacunarity(2.2f);
	noiseGenerator.SetFrequency(2);

	m_pixelData = new std::vector<float>();
	m_pixelData->resize(m_width * m_height);

	

#pragma omp parallel for
	for (int z = 0; z < m_height; z++)
	{
		float height;
		for (int x = 0; x < m_width; x++)
		{
			//Get the height from the x,z from the Perlin noise function
			//Mult by -1 to inverse the noise, divide x and y by the width and height so the noise is from a range of 0 - 1
			height = noiseGenerator.GetNoise(static_cast<float>(x)/m_width, static_cast<float>(z)/ m_height) * -1.0f;
			(*m_pixelData)[z * m_width + x] = height;
		}
	}

	m_tex = new Texture(m_pixelData->data(), 1);

	m_clock.Process();
	std::cout << "It took " << m_clock.GetTimeElapsedMS() << " milliseconds to generate the Perlin noise height map texture!" << std::endl;

	return m_tex;
}
