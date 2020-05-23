#pragma once
#include "TerrainMesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <detail/type_vec3.hpp>
#include <detail/type_mat4x4.hpp>

class Terrain
{
public:
	Terrain() = default;
	Terrain(unsigned int _xSize, unsigned int _zSize, glm::vec3 _position);
	virtual ~Terrain();

	//Getters
	glm::vec3 GetPosition() const { return m_position; }
	glm::vec3 GetScale() const { return m_scale; }

	//Setters
	void SetPosition(glm::vec3 _pos);
	void SetScale(glm::vec3 _scale);
	void SetTexture0(Texture* _tex);
	void SetTexture1(Texture* _tex);

	//Getters
	float GetTerrainHeight(float _worldX, float _worldZ);
	TerrainMesh* GetMesh() const { return m_mesh; }
	glm::mat4 GetModelMat() const { return m_modelMat; }
	virtual double GetRadius() const { return m_colliderRadius; };


	//Change m_position, rotation and m_scale
	void ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	void SetPRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	void UpdateModelMat();

	//Rendering stuff
	//Render is overidden by all derived classes, but can still be used for a base object
	virtual void SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode) const;
	virtual void Render(Camera& _myCamera, double _time, bool _fogRenderMode);
	
	void SetShaderUniforms(Camera& _myCamera, double _time, bool _fogRenderMode, bool _grassRenderMode) const;
	void Render(Camera& _myCamera, double _time, bool _fogRenderMode, bool _grassRenderMode) const;

	void BindTexture(unsigned int _texNum) const;

protected:
	unsigned int m_xSize;
	unsigned int m_zSize;
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	float m_rotationZ = 0.0f;
	glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
	double m_colliderRadius = 10.0f;

	glm::mat4 m_modelMat = glm::mat4(1.0f);

	TerrainMesh* m_mesh;
	Shader m_grassShader;
	Shader m_baseShader;
	Texture* m_tex0{};
	Texture* m_tex1{};
};

