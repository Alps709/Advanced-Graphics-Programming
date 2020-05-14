#include "TessellationObject.h"

#include "Obj.h"

TessellationObject::TessellationObject(glm::vec3 _position, glm::vec4 _colour)
{
	m_mesh = new Mesh(Objects::quadPositions);
	m_shader = new Shader("Shaders/TessModel_0_VS.glsl", "Shaders/TessModel_1_TCS.glsl", "Shaders/TessModel_2_TES.glsl", "Shaders/TessModel_3_FS.glsl");
	m_position = _position;
	m_colour = _colour;

	//Update the stored model matrix
	UpdateModelMat();
}

TessellationObject::~TessellationObject()
{
	delete m_mesh;
	delete m_shader;
}

void TessellationObject::SetShaderUniforms(Camera& _myCamera) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;

	const float cameraDistance = glm::distance(_myCamera.GetPosition(), m_position);

	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniform4f("u_colour", m_colour);
	m_shader->SetUniform1f("u_cameraDistance", cameraDistance);
}

void TessellationObject::Render(Camera& _myCamera)
{
	///OBJECT DRAW
	//Bind the mesh that the object will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera);

	GLCall(glDisable(GL_CULL_FACE));

	//Draw the object
	GLCall(glDrawArrays(GL_PATCHES, 0, m_mesh->GetindicesCount()));

	GLCall(glEnable(GL_CULL_FACE));

	Mesh::Unbind();
	Shader::Unbind();
}