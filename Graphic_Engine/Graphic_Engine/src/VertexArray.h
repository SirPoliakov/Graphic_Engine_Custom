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

	//Move Operations
	VertexArray(VertexArray&& other) noexcept;
	VertexArray& operator=(VertexArray&& other) noexcept;

	//Delete copy related operations
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

	//Destructor
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout, unsigned int _size, std::vector<void*>& offsets);
	unsigned int getID() { return renderer_ID; }
	void bind() const;
	void unbind() const;
};