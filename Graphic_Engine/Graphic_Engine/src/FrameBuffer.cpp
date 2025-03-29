#include "FrameBuffer.h"
#include <GLFW/glfw3.h>
#include "GLCalls.h"
#include <glm/glm.hpp>
#include <iostream>


FrameBuffer::FrameBuffer(GLsizei _w, GLsizei _h)		
: SCR_WIDTH(_w), SCR_HEIGHT(_h){
	GLCall(glGenFramebuffers(1, &frameBuffer_ID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_ID));

	GLCall(glGenTextures(1, &textureColorBuffer_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, textureColorBuffer_ID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer_ID, 0));

	GLCall(glGenRenderbuffers(1, &renderBuffer_ID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer_ID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT)); // use a single renderbuffer object for both a depth AND stencil buffer.
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer_ID)); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	unbind();
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &frameBuffer_ID));
	GLCall(glDeleteFramebuffers(1,&renderBuffer_ID));
}

void FrameBuffer::bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_ID));
}

void FrameBuffer::bindTexture()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, textureColorBuffer_ID));
}

void FrameBuffer::unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

