#include <texture.h>
#include <stb_image.h>
#include <iostream>
#include <filesystem>

Texture::Texture(const std::filesystem::path& path)
{
	stbi_set_flip_vertically_on_load(true);
	auto texturePath = path.string();

	int width, height, numChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &numChannels, STBI_rgb_alpha);

	glGenTextures(1, &_textureHandle);
	glBindTexture(GL_TEXTURE_2D, _textureHandle);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load texture at path: " << path << std::endl;
	}

	stbi_image_free(data);
}

const std::filesystem::path Texture::texturePath = { std::filesystem::current_path() / "assets" / "textures" };

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureHandle);
}