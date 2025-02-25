#pragma once
#include <vector>

#include "Renderer.h"

enum ImageFormat {JPG, PNG};
enum GLParameter {REPEAT, MIRRORED_REPEAT, CLAMP_TO_BORDER, CLAMP_TO_EDGE};
struct Image
{
	char const* path;
	ImageFormat format;
	GLParameter glParam;

	Image(char const* p , ImageFormat f, GLParameter glP) : path(p), format(f), glParam(glP) {}
};

class Texture
{
private:
	std::vector<unsigned int> renderer_IDs;

public:
	Texture(const std::vector<Image>& imgs);

	void setUniforms(Shader& myShader, std::string name);
	const unsigned int getID(const unsigned int i) const { return renderer_IDs[i]; }
	const void bind() const;
	const void unbind() const;
};