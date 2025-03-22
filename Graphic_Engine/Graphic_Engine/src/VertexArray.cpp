#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &renderer_ID));
	GLCall(glBindVertexArray(renderer_ID));
}

VertexArray::~VertexArray()
{
	std::cout << "Destroying VAO: " << renderer_ID << std::endl;
	GLCall(glDeleteVertexArrays(1, &renderer_ID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout, unsigned int _size, std::vector<void*>& offsets)
{
	const auto& elements = vbLayout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		//std::cout << "glVertexAttribPointer( " << i << " , " << element.count << " , " << element.type << " , " << element.normalized << " , " << _size << " , " << offsets[i] << " )" << std::endl;
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, _size, offsets[i]));
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
