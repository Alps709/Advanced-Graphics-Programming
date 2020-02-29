#include "SnekPart.h"



SnekPart::SnekPart(SphereMesh* _sphereMesh, Shader* _shader, glm::vec3 _position) : Object(_sphereMesh, _shader,  _position)
{
}

void SnekPart::Render(Camera& _myCamera)
{
	//Bind the mesh that all the models will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	BindTexture(0);

	//Set object specific uniforms
	SetShaderUniforms(_myCamera);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void *>(0)));

	Mesh::Unbind();
}

void SnekPart::SetShaderUniforms(Camera& _myCamera) const
{
	//Prepare renderer (eg. clear buffer, create PVM matrix etc.)
	glm::mat4 projViewMat = _myCamera.GetProjView();

	glm::mat4 pvmMat = projViewMat * m_modelMat;

	//Set object specific uniforms
	m_shader->SetUniform1i("u_tex", 0);
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniformMat4f("u_modelMat", const_cast<glm::mat4&>(m_modelMat));
	m_shader->SetUniform3f("u_camPos", _myCamera.GetPosition());
}
