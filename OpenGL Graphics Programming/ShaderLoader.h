#pragma once

// Dependency Includes
#include "Debug.h"


// Library Includes
#include <memory>
#include <iostream>
#include <string>
#include <map>

static std::unique_ptr<std::map<GLuint, std::string>> m_shaderMap = std::make_unique<std::map <GLuint, std::string>>();

class ShaderLoader
{
public:
	static ShaderLoader& GetInstance()
	{
		//Instantiated on first use, and found again from the static pool on later calls
		static ShaderLoader instance; 
		return instance;
	}

	static GLuint CreateProgram(const char* _vertexShaderFilename, const char* _fragmentShaderFilename);
	static GLuint CreateProgram(const char* _vertexShaderFilename, const char* _geometryShaderFilename, const char* _fragmentShaderFilename);

private:
	ShaderLoader() = default;

	//Make sure these two don't do anything so you can't get any copies of the singleton
	ShaderLoader(ShaderLoader const&) = delete;
	void operator=(ShaderLoader const&) = delete;
	
	static GLuint CreateShader(GLenum _shaderType, const char* _shaderName);
	static std::string ReadShaderFile(const char * _filename);
	static void PrintErrorDetails(bool _isShader, GLuint _id, const char* _name);
};
