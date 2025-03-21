#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	bool normalized;

	VertexBufferElement(const unsigned int& t, const unsigned int& c, const bool& norm) 
		: count(c), type(t), normalized(norm) {}

	static unsigned int getSizeOfType(unsigned int type)
	{
		
		if (type == GL_FLOAT) return 4;
		else if (type == GL_UNSIGNED_INT) return 4;
		else if (type == GL_BYTE) return 1;
		else return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements = {};
	unsigned int stride;

public:
	VertexBufferLayout()
		: stride(0) {}


	void push(unsigned int count)
	{
		elements.push_back(VertexBufferElement(GL_FLOAT, count, false));
		stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	inline const std::vector<VertexBufferElement> getElements() const { return elements; }
	inline unsigned int getStride() const { return stride; }
};