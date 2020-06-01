#include "NoiseTextureGenerator.h"

#include <iostream>

#include "FastNoise.h"

Texture* NoiseTextureGenerator::GenerateTexture()
{
	FastNoise noiseGenerator;
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(5);
	noiseGenerator.SetFractalLacunarity(2.2f);
	noiseGenerator.SetFrequency(1);

	m_pixelData = new std::vector<float>();
	m_pixelData->resize(m_width * m_height);

	m_clock.Initialise();

#pragma omp parallel for
	for (int z = 0; z < m_height; z++)
	{
		float height;
		for (int x = 0; x < m_width; x++)
		{
			//Get the height from the x,z from the Perlin noise function
			//Mult by -1 to inverse the noise, then + 1.0f / 2.0f to bring range from 0 - 1, then mult by 255 to being range from 0 - 255;
			height = noiseGenerator.GetNoise(static_cast<float>(x)/4096.0f, static_cast<float>(z)/4096.0f) * -1.0f;
			(*m_pixelData)[z * m_width + x] = height;
		}
	}

	Texture* tex = new Texture(reinterpret_cast<unsigned char*>(m_pixelData->data()), 2);

	m_clock.Process();
	std::cout << "It took " << m_clock.GetTimeElapsedMS() << " milliseconds to generate the perlin noise texture!" << std::endl;
	system("pause");

	return tex;
}
