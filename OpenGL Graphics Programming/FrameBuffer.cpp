#include "FrameBuffer.h"

#include "Debug.h"
#include "Shader.h"
#include "TexQuadMesh.h"
#include "Obj.h"
#include <iostream>

FrameBuffer::FrameBuffer(unsigned _xSize, unsigned _ySize)
{
	m_shader = new Shader("Shaders/DefaultFrameBuffer_0_VS.glsl", "Shaders/DefaultFrameBuffer_1_FS.glsl");
	m_mesh = new TexQuadMesh(Objects::screenQuadPositions, Objects::indicesQuad);

	//Create frame buffer
	GLCall(glGenFramebuffers(1, &m_frameBuffer));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer));

	//Create the texture to render onto
	GLCall(glGenTextures(1, &m_renderTexture));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_renderTexture));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _xSize, _ySize, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//Attach the texture to the frame buffer
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, //Target buffer 
		                   GL_COLOR_ATTACHMENT0,  //Attachment, could be //GL_DEPTH_ATTACHMENT or //GL_STENCIL_ATTACHMENT 
		                   GL_TEXTURE_2D,         //Texture target type
		                   m_renderTexture,       //Texture 
		                   0));                   //Level

	// Create render buffer Object
	GLCall(glGenRenderbuffers(1, &m_RBO));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER,     //Must declare it this
		                  GL_DEPTH24_STENCIL8, //use as depth - stencil buffer 
		                  _xSize, _ySize));     //viewport width and height
	//Unbind it after allocating the memory for it
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

	// Attach m_RBO to the depth and stencil attachment of the frame buffer
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, //target 
							  GL_DEPTH_STENCIL_ATTACHMENT, //attachment 
							  GL_RENDERBUFFER, //renderbufferTarget 
							  m_RBO)); // render buffer

	if (GLCall(glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		system("pause");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_frameBuffer);
	delete m_mesh;
}

void FrameBuffer::Prepare()
{
	//Bind the frame buffer so things can be rendered to it
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	glClearColor(1, 1, 1, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
}

void FrameBuffer::SetShaderUniforms()
{
	//Set object specific uniforms
	m_shader->SetUniform1i("u_renderTex", 0);
	
}

void FrameBuffer::Render()
{
	m_mesh->Bind();
	m_shader->Bind();

	SetShaderUniforms();

	// Bind Default framebuffer 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	m_mesh->Bind();

	glDisable(GL_DEPTH_TEST); //screenspace quad so depth is not required

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_renderTexture);
	
	glDrawElements(GL_TRIANGLES, m_mesh->GetindicesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
}
