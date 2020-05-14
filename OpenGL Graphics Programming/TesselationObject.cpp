#include "TesselationObject.h"

#include "Obj.h"

TesselationObject::TesselationObject(glm::vec3 _position, glm::vec4 _colour)
{
	m_mesh = new Mesh(Objects::quadPositions);
	m_shader = new Shader("Shaders/TessModel_0_VS.glsl", "Shaders/TessModel_1_GS.glsl", "Shaders/TessModel_2_FS.glsl");
	m_position = _position;
	m_colour = _colour;

	//Update the stored model matrix
	UpdateModelMat();
}

TesselationObject::~TesselationObject()
{
	delete m_mesh;
	delete m_shader;
}

void TesselationObject::SetShaderUniforms(Camera& _myCamera) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniform4f("u_colour", m_colour);
}

void TesselationObject::Render(Camera& _myCamera)
{
	///OBJECT DRAW
	//Bind the mesh that the object will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera);

	GLCall(glDisable(GL_CULL_FACE));

	//Draw the object
	GLCall(glDrawArrays(GL_POINTS, 0, m_mesh->GetindicesCount()));

	GLCall(glEnable(GL_CULL_FACE));

	Mesh::Unbind();
	Shader::Unbind();
}