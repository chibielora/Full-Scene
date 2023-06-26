#pragma once

#include <glm/glm.hpp>
#include <shader.h>
#include <texture.h>

class Material {
public:
	Material(
		std::shared_ptr<Texture> texture,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular
	);
	Material(
		std::shared_ptr<Texture> texture
	);
	void Bind(Shader shader);
public:
	float shininess{ 32.f };
private:
	std::shared_ptr<Texture> _texture;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
};