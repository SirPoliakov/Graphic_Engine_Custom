#pragma once
#include <GL/glew.h>

class FrameBuffer
{
private:
	GLsizei SCR_WIDTH;
	GLsizei SCR_HEIGHT;

	unsigned int frameBuffer_ID;
	unsigned int textureColorBuffer_ID;
	unsigned int renderBuffer_ID;

public:
	FrameBuffer(GLsizei _w = 1600, GLsizei _h = 900);
	~FrameBuffer();

	void bind();
	void bindTexture();
	void unbind();
};