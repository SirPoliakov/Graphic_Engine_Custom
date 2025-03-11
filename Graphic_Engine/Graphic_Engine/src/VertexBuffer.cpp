#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &renderer_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer() : renderer_ID(0)
{}

VertexBuffer::~VertexBuffer()
{
	std::cout << "Destroying VBO: " << renderer_ID << std::endl;
	GLCall(glDeleteBuffers(1, &renderer_ID));
}

void VertexBuffer::populateBuffer(const void* data, unsigned int size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::generate()
{
	GLCall(glGenBuffers(1, &renderer_ID));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
