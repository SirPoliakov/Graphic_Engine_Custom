#pragma once

class IndexBuffer
{
private:

	unsigned int renderer_ID;
	unsigned int count;

public:

	IndexBuffer(const unsigned int* data, unsigned int _count);
	~IndexBuffer();

	unsigned int getCount() const { return count; }
	void bind() const;
	void unbind() const;
};