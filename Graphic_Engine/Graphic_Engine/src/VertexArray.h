#pragma once
#include <vector>
class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int renderer_ID;
public:

	//Constructor
	VertexArray();

	//Destructor
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout, unsigned int _size, std::vector<void*>& offsets);
	unsigned int getID() { return renderer_ID; }
	void generate();
	void bind() const;
	void unbind() const;
};