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
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_BYTE: return 1;
		}
		ASSERT(false)
			return 0;
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

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back(VertexBufferElement(GL_FLOAT, count, false));
		stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count, false));
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, false));
		stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> getElements() const { return elements; }
	inline unsigned int getStride() const { return stride; }
};