#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int _count) : count(_count)
{
	GLCall(glGenBuffers(1, &renderer_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer() : count(0)
{
	GLCall(glGenBuffers(1, &renderer_ID));
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
: renderer_ID(other.renderer_ID){
	this->count = other.count;
	other.renderer_ID = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
	if (this != &other) {
		glDeleteBuffers(1, &renderer_ID);
		renderer_ID = other.renderer_ID;
		count = other.count;
		other.renderer_ID = 0;
	}
	return *this;
}


IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &renderer_ID));
}

void IndexBuffer::populateIndex(const unsigned int* data, unsigned int _count)
{
	count = _count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_ID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}