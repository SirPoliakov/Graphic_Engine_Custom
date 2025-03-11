#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &renderer_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &renderer_ID));
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: renderer_ID(other.renderer_ID) {
	other.renderer_ID = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other) {
            glDeleteBuffers(1, &renderer_ID);
            renderer_ID = other.renderer_ID;
            other.renderer_ID = 0;
        }
        return *this;
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &renderer_ID));
}

void VertexBuffer::populateBuffer(const void* data, unsigned int size)
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_ID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
