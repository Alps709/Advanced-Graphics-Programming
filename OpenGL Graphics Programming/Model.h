#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ModelMesh.h"
#include "Camera.h"
#include "Shader.h"

class Model
{
public:
	
	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	Model() = default;
	Model(std::string path, Shader* shader);

	//Getters
	glm::vec3 GetPosition() const { return m_position; }

	//Setters
	void SetPosition(glm::vec3 _pos);

	//Change m_position, rotation and m_scale
	void ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	void SetPRS(float _translateX, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ);
	
	void UpdateModelMat();

	// Draws the model, and thus all its meshes
	void Render(Camera& _camera);

	/*  Model Data  */
	glm::vec3 m_position{ 0.0f, 0.0f, 0.0f };
	float m_rotationY = 0.0f;
	glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
	double m_colliderRadius = 10.0f;

private:
	
	glm::mat4 m_modelMat = glm::mat4(1.0f);

	Shader* m_shader;

	vector<ModelMesh> meshes;
	string directory;
	vector<MeshTexture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

	/*  Functions   */
	// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);

	ModelMesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	
	GLint TextureFromFile(const char* path, string directory);
	
};

