#include "GeometryObject.h"

#include "Obj.h"

GeometryObject::GeometryObject(glm::vec3 _position, glm::vec4 _colour)
{
	m_mesh = new Mesh(Objects::vertexPoint);
	m_shader = new Shader("Shaders/GeoModel_0_VS.glsl", "Shaders/GeoModel_1_GS.glsl", "Shaders/GeoModel_2_FS.glsl");
	m_position = _position;
	m_colour = _colour;

	//Update the stored model matrix
	UpdateModelMat();
}

GeometryObject::~GeometryObject()
{
	delete m_mesh;
	delete m_shader;
}

void GeometryObject::SetShaderUniforms(Camera& _myCamera) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniform4f("u_colour", m_colour);
}

void GeometryObject::Render(Camera& _myCamera)
{
	///OBJECT DRAW
	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera);

	GLCall(glDisable(GL_CULL_FACE));
	
	//Draw the object
	GLCall(glDrawArrays(GL_POINTS, 0, 1));

	GLCall(glEnable(GL_CULL_FACE));
	
	Mesh::Unbind();
	Shader::Unbind();
}
