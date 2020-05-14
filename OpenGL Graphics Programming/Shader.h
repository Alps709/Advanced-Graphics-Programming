#pragma once
#include <string>
#include <mat4x4.hpp>
#include "ShaderLoader.h"

class Shader
{
public:
	Shader();
	Shader(const char* _vertexSrc, const char* _fragmentSrc);
	Shader(const char* _vertexSrc, const char* _geometrySrc, const char* _fragmentSrc);
	Shader(const char* _vertexSrc, const char* _tesselationControlSrc, const char* _tesselationEvaluationSrc, const char* _fragmentSrc);
	~Shader() = default;

	void Bind() const;
	static void Unbind();

	void CleanUp() const;

	void SetUniform1f(const std::string& _name, float _v1) const;
	void SetUniform3f(const std::string& _name, float _v1, float _v2, float _v3) const;
	void SetUniform3f(const std::string& _name, glm::vec3 _vec3f) const;
	void SetUniform4f(const std::string& _name, glm::vec4 _vec4f) const;

	void SetUniform1i(const std::string& _name, int _v1) const;

	void SetUniformMat4f(const std::string& _name, glm::mat4& _matrix) const;

	int GetUniformLocation(const std::string& _name) const;

private:
	unsigned int m_programID{};

	std::string m_VSFile;
	std::string m_TCSFile;
	std::string m_TESFile;
	std::string m_GSFile;
	std::string m_FSFile;
};

