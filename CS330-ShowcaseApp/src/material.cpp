#include "material.h"

Material::Material(
	std::shared_ptr<Texture> texture,
	glm::vec3 ambient,
	glm::vec3 diffuse,
	glm::vec3 specular
) : _texture{ texture }, _ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular }
{}

Material::Material(std::shared_ptr<Texture> texture) : Material(
	texture,
	glm::vec3 { 1.f, 1.f, 1.f },
	glm::vec3 { 1.f, 1.f, 1.f },
	glm::vec3 { 1.f, 1.f, 1.f }
)
{}

void Material::Bind(Shader shader)
{
	shader.Bind();
	_texture->Bind();
	shader.SetVec3("material.ambient", _ambient);
	shader.SetVec3("material.diffuse", _diffuse);
	shader.SetVec3("material.specular", _specular);
	shader.SetFloat("material.shininess", shininess);
}
