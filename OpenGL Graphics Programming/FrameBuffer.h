#pragma once

class TexQuadMesh;
class Shader;

class FrameBuffer
{
public:
    FrameBuffer(unsigned int _xSize, unsigned int _ySize);
    ~FrameBuffer();

    void Prepare();
    void SetShaderUniforms(float _currentTime);
    void Render(float _currentTime);

private:
    unsigned int m_renderTexture;
    unsigned int m_frameBuffer;
    unsigned int m_RBO;

    Shader* m_shader;
    TexQuadMesh* m_mesh;
};

