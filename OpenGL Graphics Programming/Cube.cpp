#include "Cube.h"
#include "Obj.h"

Cube::Cube(glm::vec3 _position, Texture* _texture)
{
	m_mesh = new Mesh(Objects::verticesCube, Objects::indicesCube);
	m_shader = new Shader("Shaders/Cube1VS.glsl", "Shaders/Cube1FS.glsl");
	m_position = _position;
	m_tex0 = _texture;


	//Update the stored model matrix
	UpdateModelMat();
}

void Cube::SetShaderUniforms(Camera& _myCamera, bool _fogRenderMode) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	glm::mat4 modelMat = m_modelMat;
	glm::vec3 camPos = _myCamera.GetPosition();

	//Set object specific uniforms
	m_shader->SetUniform1i("u_grassTex", 0);
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniformMat4f("u_modelMat", modelMat);
	m_shader->SetUniform3f("u_camPos", camPos);
	m_shader->SetUniform1i("u_fogRenderMode", _fogRenderMode);
}

void Cube::Render(Camera& _myCamera, bool _fogRenderMode)
{
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //stPass, dpFail, bothPass 
	
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF); //enable writing to stencil buffer

	this->SetPRS(70, 5, 70, 0.0f, 1.0f, 1.0f, 1.0f);
	this->UpdateModelMat();

	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, true);

	//Bind grass texture
	BindTexture(0);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	Mesh::Unbind();
	Shader::Unbind();

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00); //disable writing to stencil buffer
	
	this->SetPRS(70, 5, 70, 0.0f, 2.0f, 2.0f, 2.0f);
	this->UpdateModelMat();

	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, false);

	//Bind grass texture
	BindTexture(0);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	Mesh::Unbind();
	Shader::Unbind();

	//disable writing to stencil mask
	//glStencilMask(0x00);
	glStencilMask(~0);
	GLCall(glClear(GL_STENCIL_BUFFER_BIT));
	glDisable(GL_STENCIL_TEST);
}