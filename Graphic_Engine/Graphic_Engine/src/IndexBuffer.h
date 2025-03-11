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

	unsigned int getID() { return renderer_ID; }

	//Destructor
	~IndexBuffer();

	unsigned int getCount() const { return count; }
	void populateIndex(const unsigned int* data, unsigned int _count);
	void generate();
	void bind() const;
	void unbind() const;
};