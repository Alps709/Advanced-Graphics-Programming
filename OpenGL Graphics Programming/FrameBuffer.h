#pragma once

class Mesh;
class Shader;

class FrameBuffer
{
public:
    FrameBuffer(unsigned int _xSize, unsigned int _ySize);
    ~FrameBuffer();

    void Prepare();
    void SetShaderUniforms(double _currentTime);
    void Render(double _currentTime);

private:
    unsigned int m_renderTexture;
    unsigned int m_frameBuffer;
    unsigned int m_RBO;

    Shader* m_shader;
    Mesh* m_mesh;
};

