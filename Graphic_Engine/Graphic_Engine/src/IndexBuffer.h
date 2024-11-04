#pragma once
#include "Renderer.h"

class IndexBuffer
{
private:

	unsigned int renderer_ID;
	unsigned int count;

public:

	IndexBuffer(const unsigned int* data, unsigned int _count);
	~IndexBuffer();

	void bind();
	void unbind();
};