#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &renderer_ID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &renderer_ID))
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout)
{
	bind();
	vb.bind();
	const auto& elements = vbLayout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));

		//if ((unsigned int)5126 == GL_FLOAT) std::cout << "FLOAT" << std::endl;
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vbLayout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
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
