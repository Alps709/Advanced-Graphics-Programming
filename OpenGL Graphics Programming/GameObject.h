#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <detail/type_vec3.hpp>
#include <detail/type_mat4x4.hpp>



class GameObject
{
public:
	GameObject() = default;
	GameObject(Mesh* _mesh, Shader* _shader, glm::vec3 _position);
	virtual ~GameObject() = default;

	//Getter
	glm::vec3 GetPosition() const { return m_position; }
	float GetRotationAngle() const { return m_rotationY; }
	glm::vec3 GetScale() const { return m_scale; }
	Mesh* GetMesh() const { return m_mesh; }
	glm::mat4 GetModelMat() const { return m_modelMat; }
	virtual double GetRadius() const { return m_colliderRadius; };

	//Setters
	void SetPosition(glm::vec3 _pos);
	void SetTexture0(Texture* _tex);
	void SetTexture1(Texture* _tex);

	


	//Change m_position, rotation and m_scale
	void ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	void SetPRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	void UpdateModelMat();
	
	//Rendering stuff
	//Render is overidden by all derived classes, but can still be used for a base object
	virtual void SetShaderUniforms(Camera& _myCamera) const;
	virtual void Render(Camera& _myCamera);

	void BindTexture(unsigned int _texNum) const;

protected:
	glm::vec3 m_position{0.0f, 0.0f, 0.0f};
	float m_rotationY = 0.0f;
	glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
	double m_colliderRadius = 1.0f;

	glm::mat4 m_modelMat = glm::mat4(1.0f);

	Mesh* m_mesh;
	Shader* m_shader;
	Texture* m_tex0{};
	Texture* m_tex1{};
};

