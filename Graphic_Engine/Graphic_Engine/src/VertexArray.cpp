#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &renderer_ID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &renderer_ID))
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout, unsigned int _size, std::vector<void*>& offsets)
{
	bind();
	vb.bind();
	const auto& elements = vbLayout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, _size, offsets[i]));
		GLCall(glEnableVertexAttribArray(i));

		offset = (i + 1) * elements[0].count;
	}
}


void VertexArray::bind() const
{
	GLCall(glBindVertexArray(renderer_ID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
