#include "Cube.h"
#include "Obj.h"

Cube::Cube(glm::vec3 _position, Texture* _texture, glm::vec4 _colour, bool _useStencil)
{
	m_mesh = new Mesh(Objects::verticesCube, Objects::indicesCube);
	m_shader = new Shader("Shaders/Cube_0_VS.glsl", "Shaders/Cube_1_FS.glsl");
	m_position = _position;
	m_tex0 = _texture;
	m_colour = _colour;
	m_useStencil = _useStencil;

	//Update the stored model matrix
	UpdateModelMat();
}

Cube::~Cube()
{
	delete m_mesh;
	delete m_shader;
}

void Cube::SetShaderUniforms(Camera& _myCamera, bool _fogRenderMode, bool _stencilOutline) const
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
	m_shader->SetUniform3f("u_cubeColour", glm::vec3(m_colour));
	m_shader->SetUniform1i("u_fogRenderMode", _fogRenderMode);
	m_shader->SetUniform1i("u_stencilOutline", _stencilOutline);
}

void Cube::Render(Camera& _myCamera, bool _fogRenderMode)
{
	if (m_useStencil)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //stPass, dpFail, bothPass 

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF); //enable writing to stencil buffer
	}

	
	///OBJECT DRAW
	//Bind the mesh that all the model will use
	m_mesh->Bind();
	m_shader->Bind();

	//Prepare the object for drawing
	SetShaderUniforms(_myCamera, _fogRenderMode, false);

	//Bind grass texture
	BindTexture(0);

	//Draw the object
	GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

	Mesh::Unbind();
	Shader::Unbind();

	if (m_useStencil)
	{
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(~0); //disable writing to stencil buffer


		///STENCIL OUTLINE DRAW
		//Scale the object up to use as an outline
		this->SetPRS(m_position.x, m_position.y, m_position.z, m_rotationZ, 1.2f, 1.2f, 1.2f);

		//Bind the mesh that all the model will use
		m_mesh->Bind();
		m_shader->Bind();

		//Prepare the object for drawing
		SetShaderUniforms(_myCamera, _fogRenderMode, true);

		//Bind grass texture
		BindTexture(0);

		//Draw the object
		GLCall(glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, static_cast<void*>(0)));

		Mesh::Unbind();
		Shader::Unbind();

		//disable writing to stencil mask
		glStencilMask(~0);
		glDisable(GL_STENCIL_TEST);

		//Scale it back down for the next render call its size
		this->SetPRS(m_position.x, m_position.y, m_position.z, m_rotationZ, 1.0f, 1.0f, 1.0f);
	}
}