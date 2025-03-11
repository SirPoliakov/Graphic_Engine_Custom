#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>

VertexArray::VertexArray()
: renderer_ID(0)
{}

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
		if (i != 5)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			std::cout << "Attrib Pointers Setup:" << std::endl;
			std::cout << "glVertexAttribPointer( " << i << ", " << element.count << ", " << element.type << ", " << element.normalized << ", " << _size << ", " << (size_t)offsets[i] << " )" << std::endl;
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, _size, offsets[i]));
		}
		offset = (i + 1) * elements[0].count;
	}
}

void VertexArray::generate()
{
	GLCall(glGenVertexArrays(1, &renderer_ID));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(renderer_ID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
