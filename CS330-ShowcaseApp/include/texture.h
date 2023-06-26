#pragma once
#include <filesystem>
#include <glad/glad.h>

class Texture {
public:
	Texture(const std::filesystem::path& path);
	void Bind();

	static const std::filesystem::path texturePath;
private:
	GLuint _textureHandle;
};