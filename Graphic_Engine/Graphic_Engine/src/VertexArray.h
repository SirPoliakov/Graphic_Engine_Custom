#pragma once
#include <vector>
class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int renderer_ID;
public:

	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout, unsigned int _size, std::vector<void*>& offsets);

	void bind() const;
	void unbind() const;
};