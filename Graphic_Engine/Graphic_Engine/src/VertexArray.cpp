#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &renderer_ID));
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: renderer_ID(other.renderer_ID)
{
	other.renderer_ID = 0; //Prevent deletion from moved object
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
	if (this != &other)
	{
		GLCall(glDeleteVertexArrays(1, &renderer_ID));
		renderer_ID = other.renderer_ID;
		other.renderer_ID = 0;
	}
	return *this;
}

VertexArray::~VertexArray()
{
	//std::cout << "Destroying VAO: " << renderer_ID << std::endl;
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
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, _size, offsets[i]));
		}
		else
		{
			GLCall(glEnableVertexAttribArray(5));
			GLCall(glVertexAttribIPointer(5, 4, GL_INT, _size, offsets[5]));
		}

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
