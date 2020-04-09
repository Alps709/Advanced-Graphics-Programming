#include "CubeMap.h"
#include <SOIL.h>
#include "Math.h"
#include "Obj.h"

void SetVertexAttributes();
void AddVAOBuffer(const VertexBufferInfo _info);



void SetVertexAttributes()
{
	//Create layout and populate it with the vertex attribute information
	VertexBufferInfo vbInfo;

	//3 m_position floats
	vbInfo.Push<float>(3);

	//4 colour floats
	vbInfo.Push<float>(3);

	//2 texture co-ord floats
	vbInfo.Push<float>(2);

	AddVAOBuffer(vbInfo);
}

void AddVAOBuffer(const VertexBufferInfo _info)
{
	const auto& indices = _info.Getindices();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < indices.size(); ++i)
	{
		const auto element = indices[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, (element.normalised ? GL_TRUE : GL_FALSE), _info.GetStride(), reinterpret_cast<const void*>(offset)));
		offset += element.count * VBElementInfo::GetTypeSize(element.type);
	}
}



void CubeMap::Initialise()
{
	if (m_shader == nullptr)
	{
		m_shader = new Shader("Shaders/CubeMapVS.glsl", "Shaders/CubeMapFS.glsl");
	}
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);

	//MESH
	//Generate vao
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glBindVertexArray(m_vaoID));

	//Generate vbo
	GLCall(glGenBuffers(1, &m_vboID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, Objects::verticesCubeMap.size() * sizeof(float), static_cast<const void*>(Objects::verticesCubeMap.data()), GL_STATIC_DRAW));

	//Generate ibo
	GLCall(glGenBuffers(1, &m_iboID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Objects::indicesCubeMap.size() * sizeof(unsigned int), static_cast<const void*>(Objects::indicesCubeMap.data()), GL_STATIC_DRAW));

	SetVertexAttributes();
	m_indicesCount = Objects::indicesCubeMap.size();


	//TEXTURE
	//Construct cubemap textures
	GLCall(glGenTextures(1, &m_texID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));

	std::vector<std::string> textureNames{ "right.jpg", "left.jpg" , "top.jpg", "bottom.jpg", "back.jpg", "front.jpg" };

	int width, height;
	unsigned char* image;
	for (int i = 0; i < 6; ++i)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(textureNames[i]);

		image = SOIL_load_image(fullPathName.c_str(), &width, &height, nullptr, SOIL_LOAD_RGBA);

		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image));
		SOIL_free_image_data(image);
	}

	GLCall(glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GLCall(glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void CubeMap::ChangePRS(float _translateX, float _translateY, float _translateZ, float _rotationAngle, float _scaleX, float _scaleY, float _scaleZ)
{
	m_position += glm::vec3(_translateX, _translateY, _translateZ);

	//Add new rotation and cap it to 360
	m_rotationZ += _rotationAngle;
	m_rotationZ = fmod(m_rotationZ, 360.0f);

	m_scale += glm::vec3(_scaleX, _scaleY, _scaleZ);

	//Update the stored model matrix
	UpdateModelMat();
}

void CubeMap::UpdateModelMat()
{
	//Update the stored model matrix
	m_modelMat = Math::Create2DModelMatrix(m_position.x, m_position.y, m_position.z, m_rotationZ, m_scale.x, m_scale.y, m_scale.z);
}

void CubeMap::SetShaderUniforms(Camera& _myCamera, bool _fogRenderMode) const
{
	//Prepare renderer (eg. create PVM matrix etc.)
	glm::mat4 pvmMat = _myCamera.GetProjView() * m_modelMat;
	glm::mat4 modelMat = m_modelMat;
	glm::vec3 camPos = _myCamera.GetPosition();

	//Set object specific uniforms
	m_shader->SetUniform1i("u_cubeSampler", 0);
	m_shader->SetUniformMat4f("u_PVM", pvmMat);
	m_shader->SetUniformMat4f("u_modelMat", modelMat);
	m_shader->SetUniform3f("u_camPos", camPos);
	m_shader->SetUniform1i("u_fogRenderMode", _fogRenderMode);
}

void CubeMap::Render(Camera& _myCamera, bool _fogRenderMode)
{
	//Bind the mesh that all the model will use
	m_shader->Bind();

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	SetShaderUniforms(_myCamera, _fogRenderMode);

	//Prepare the object for drawing
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID));

	//Draw the object
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, static_cast<void *>(0)));
	GLCall(glBindVertexArray(0));

	Shader::Unbind();
}