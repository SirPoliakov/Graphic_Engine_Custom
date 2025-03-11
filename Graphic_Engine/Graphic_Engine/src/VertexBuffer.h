#pragma once

class VertexBuffer
{
private:

	unsigned int renderer_ID;

public:

	//Constructors
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();

	//Move Operations
	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	//Deleted Copies
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	//Destructor
	~VertexBuffer();

	void populateBuffer(const void* data, unsigned int size);
	void bind() const;
	void unbind() const;
};