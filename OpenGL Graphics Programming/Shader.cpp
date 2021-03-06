#include "Shader.h"
#include "Debug.h"

#include <vector>
#include <freeglut.h>
#include <mat4x4.hpp>
#include <detail/_vectorize.hpp>

Shader::Shader()
{
	m_programID = ShaderLoader::CreateProgram("Shaders/Default_0_VS.glsl", "Shaders/Default_1_FS.glsl");
}

Shader::Shader(const char* _computeSrc)
{
	m_programID = ShaderLoader::CreateProgram(_computeSrc);
}

Shader::Shader(const char* _vertexSrc, const char* _fragmentSrc)
{
	m_VSFile = _vertexSrc;
	m_FSFile = _fragmentSrc;
	m_programID = ShaderLoader::CreateProgram(_vertexSrc, _fragmentSrc);
}

Shader::Shader(const char* _vertexSrc, const char* _geometrySrc, const char* _fragmentSrc)
{
	m_VSFile = _vertexSrc;
	m_GSFile = _geometrySrc;
	m_FSFile = _fragmentSrc;
	m_programID = ShaderLoader::CreateProgram(_vertexSrc, _geometrySrc, _fragmentSrc);
}

Shader::Shader(const char* _vertexSrc, const char* _tesselationControlSrc, const char* _tesselationEvaluationSrc, const char* _fragmentSrc)
{
	m_VSFile = _vertexSrc;
	m_TCSFile = _tesselationControlSrc;
	m_TESFile = _tesselationEvaluationSrc;
	m_FSFile = _fragmentSrc;
	m_programID = ShaderLoader::CreateProgram(_vertexSrc, _tesselationControlSrc, _tesselationEvaluationSrc, _fragmentSrc);
}

Shader::Shader(const char* _vertexSrc, const char* _tessellationControlSrc, const char* _tesselationEvaluationSrc,
	           const char* _geometrySrc, const char* _fragmentSrc)
{
	m_VSFile = _vertexSrc;
	m_TCSFile = _tessellationControlSrc;
	m_TESFile = _tesselationEvaluationSrc;
	m_GSFile = _geometrySrc;
	m_FSFile = _fragmentSrc;
	m_programID = ShaderLoader::CreateProgram(_vertexSrc, _tessellationControlSrc, _tesselationEvaluationSrc, _geometrySrc, _fragmentSrc);
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_programID));
}

void Shader::Unbind()
{
	GLCall(glUseProgram(0));
}

void Shader::CleanUp() const
{
	Unbind();
	glDeleteProgram(m_programID);
	m_shaderMap->erase(m_programID);
}

void Shader::SetUniform1f(const std::string& _name, float _v1) const
{
	GLCall(glUniform1f(GetUniformLocation(_name), _v1));
}

void Shader::SetUniform3f(const std::string& _name, float _v1, float _v2, float _v3) const
{
	GLCall(glUniform3f(GetUniformLocation(_name), _v1, _v2, _v3));
}

void Shader::SetUniform3f(const std::string& _name, glm::vec3 _vec3f) const
{
	GLCall(glUniform3f(GetUniformLocation(_name), _vec3f.x, _vec3f.y, _vec3f.z));
}

void Shader::SetUniform4f(const std::string& _name, glm::vec4 _vec4f) const
{
	GLCall(glUniform4f(GetUniformLocation(_name), _vec4f.x, _vec4f.y, _vec4f.z, _vec4f.w));
}

void Shader::SetUniform1i(const std::string& _name, int _v1) const
{
	GLCall(glUniform1i(GetUniformLocation(_name), _v1));
}

void Shader::SetUniformMat4f(const std::string& _name, glm::mat4& _matrix) const
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(_name), 1, GL_FALSE, &_matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& _name) const
{
	int uniformLocation = glGetUniformLocation(m_programID, _name.c_str());

	if(uniformLocation == -1)
	{
		std::cout << "Warning: " << m_VSFile << " or "  << m_GSFile  << " or " << m_FSFile << " has a problem!\n";
		std::cout << "Warning! Couldn't find uniform: " << _name << std::endl;
		system("pause");
	}

	return uniformLocation;
}
