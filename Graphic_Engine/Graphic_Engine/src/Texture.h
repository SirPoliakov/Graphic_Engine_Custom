#pragma once
#include <vector>

class Shader;

enum ImageFormat {JPG, PNG};
struct Image
{
	char const* path;
	ImageFormat format;

	Image(char const* p , ImageFormat f) : path(p), format(f) {}
};

class Texture
{
private:
	std::vector<unsigned int> renderer_IDs;

public:
	Texture(const std::vector<Image>& imgs);

	void setUniforms(Shader& myShader);
	const unsigned int getID(const unsigned int i) const { return renderer_IDs[i]; }
	const void bind() const;
	const void unbind() const;
};