#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int renderer_ID;
public:

	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout);

	void bind() const;
	void unbind() const;
};