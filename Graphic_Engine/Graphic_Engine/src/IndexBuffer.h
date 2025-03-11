#pragma once

class IndexBuffer
{
private:

	unsigned int renderer_ID;
	unsigned int count;

public:

	//COnstructors
	IndexBuffer(const unsigned int* data, unsigned int _count);
	IndexBuffer();

	//Move Operations
	IndexBuffer(IndexBuffer&& other) noexcept;
	IndexBuffer& operator=(IndexBuffer&& other) noexcept;

	//Deleted Copies
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;

	//Destructor
	~IndexBuffer();

	unsigned int getCount() const { return count; }
	void populateIndex(const unsigned int* data, unsigned int _count);
	void bind() const;
	void unbind() const;
};