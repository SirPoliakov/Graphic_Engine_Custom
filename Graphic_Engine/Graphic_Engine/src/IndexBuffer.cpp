#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int _count) : count(_count)
{
	GLCall(glGenBuffers(1, &renderer_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer() : renderer_ID(0), count(0)
{}


IndexBuffer::~IndexBuffer()
{
	std::cout << "Destroying EBO: " << renderer_ID << std::endl;
	GLCall(glDeleteBuffers(1, &renderer_ID));
}

void IndexBuffer::populateIndex(const unsigned int* data, unsigned int _count)
{
	count = _count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::generate()
{
	GLCall(glGenBuffers(1, &renderer_ID));
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}