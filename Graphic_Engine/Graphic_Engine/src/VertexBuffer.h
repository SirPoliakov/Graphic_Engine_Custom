#pragma once

class VertexBuffer
{
private:

	unsigned int renderer_ID;

public:

	//Constructors
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();

	unsigned int getID() { return renderer_ID; }

	//Destructor
	~VertexBuffer();

	void populateBuffer(const void* data, unsigned int size);
	void generate();
	void bind() const;
	void unbind() const;
};