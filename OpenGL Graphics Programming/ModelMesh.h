// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <types.h>
#include <glm.hpp>
#include "Shader.h"

using namespace std;

struct Vertex 
{
	glm::vec3 Position; // Position	
	glm::vec3 Normal; // Normal	
	glm::vec2 TexCoords; // TexCoords
};

struct MeshTexture 
{
	GLuint id;
	string type;
	aiString path;
};

class ModelMesh {
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<MeshTexture> textures;

	/*  Functions  */
	// Constructor
	ModelMesh(vector<Vertex> vertices, vector<GLuint> indices, vector<MeshTexture> textures);

	// Render the mesh
	void Render(glm::mat4 PVMMat, Shader* shader);
	virtual void SetShaderUniforms(glm::mat4 PVMMat, Shader* shader);

private:
	/*  Render data  */
	GLuint VAO{}, VBO{}, EBO{};

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	void setupMesh();
};
