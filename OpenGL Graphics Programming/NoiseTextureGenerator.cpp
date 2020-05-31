#include "NoiseTextureGenerator.h"

#include <iostream>

#include "FastNoise.h"

Texture* NoiseTextureGenerator::GenerateTexture()
{
	FastNoise noiseGenerator;
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(4);
	noiseGenerator.SetFractalLacunarity(2.2f);

	m_pixelData = new std::vector<Pixel>();
	m_pixelData->resize(m_width * m_height);

	m_clock.Initialise();

#pragma omp parallel for
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			//Get the height from the x,z from the Perlin noise function
			const float height = (noiseGenerator.GetNoise(static_cast<float>(x), static_cast<float>(y)) + 1.0f) /2.0f * 255.0f;
			const auto temp = static_cast<unsigned char>(height);
			(*m_pixelData)[y * m_width + x] = Pixel(temp, temp, temp, 1);
		}
	}

	Texture* tex = new Texture(reinterpret_cast<unsigned char*>(m_pixelData->data()), 2);

	m_clock.Process();
	std::cout << "It took " << m_clock.GetTimeElapsedMS() << " milliseconds to generate the perlin noise texture!" << std::endl;
	system("pause");

	return tex;
}
