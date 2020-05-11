#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube() = default;
	Cube(glm::vec3 _position, Texture* _texture, glm::vec4 _colour, bool _useStencil = false);
	~Cube();

	void SetShaderUniforms(Camera& _myCamera, bool _fogRenderMode, bool _stencilOutline) const;
	void Render(Camera& _myCamera, bool _fogRenderMode);

	glm::vec4 m_colour;
	bool m_useStencil = false;
};

