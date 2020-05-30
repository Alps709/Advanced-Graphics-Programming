#pragma once
#include <vector>

#include "Texture.h"
#include "clock.h"


struct Pixel
{
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0;

	Pixel() = default;

	Pixel(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	bool operator==(const Pixel& other) const
	{
		return (r == other.r
			&& g == other.g
			&& b == other.b
			&& a == other.a);
	}
};

class NoiseTextureGenerator
{
public:
	NoiseTextureGenerator() = default;

	Texture* GenerateTexture();

private:
	const int m_width = 4096;
	const int m_height = 4096;

	CClock m_clock;
};

