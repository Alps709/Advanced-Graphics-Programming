#include "NoiseTextureGenerator.h"

#include <iostream>

#include "FastNoise.h"

Texture* NoiseTextureGenerator::GenerateTexture()
{
	FastNoise noiseGenerator;
	noiseGenerator.SetNoiseType(FastNoise::NoiseType::PerlinFractal);
	noiseGenerator.SetFractalOctaves(4);
	noiseGenerator.SetFractalLacunarity(2.2f);

	auto pixelData = new std::vector<Pixel>();
	pixelData->resize(m_width * m_height);

	m_clock.Initialise();
	
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			//Get the height from the x,z from the Perlin noise function
			const float height = ((noiseGenerator.GetNoise(static_cast<float>(x), static_cast<float>(y)) + 1.0f) /2.0f) * 255.0f;
			pixelData->push_back(Pixel(static_cast<unsigned char>(height), static_cast<unsigned char>(height), static_cast<unsigned char>(height), 255));
		}
	}

	Texture* tex = new Texture(reinterpret_cast<unsigned char*>(pixelData), 2);

	m_clock.Process();
	std::cout << "It took " << m_clock.GetTimeElapsedMS() << " milliseconds to generate the perlin noise texture!" << std::endl;
	system("pause");

	return tex;
}
