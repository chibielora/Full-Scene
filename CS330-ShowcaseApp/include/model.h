#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <mesh.h>
#include <shader.h>
#include <material.h>

class Model {
public:
	Model(std::shared_ptr<Material> material);
	Model(std::shared_ptr<Material> material, std::vector<Mesh> meshes);
	void Draw(Shader shader, glm::mat4 transform = glm::mat4{ 1.f });
	glm::mat4 Transform { 1.f };
private:
	std::vector<Mesh> _meshes{};
	std::shared_ptr<Material> _material;
};