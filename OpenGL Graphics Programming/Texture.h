#pragma once
class Texture
{
public:
	Texture() = default;
	
	//Constuctor for loading a texture from file
	Texture(const char* _filePath, unsigned short _slot);

	//Constructor for creating a texture from an array of pixel data
	Texture(unsigned char* _pixelArray, unsigned short _slot);
	
	~Texture();

	void Bind() const;
	static void Unbind();

	unsigned int GetID() const { return m_textureID; }

private:
	unsigned int m_textureID{};
	const char* m_filePath{};
	int m_width{0};
	int m_height{0};

	//Texture bind slot, the Size depends on the system, for 
	int m_slot{0};
};

