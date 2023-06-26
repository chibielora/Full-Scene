#include <model.h>
#include <glm/glm.hpp>

Model::Model(std::shared_ptr<Material> material) : _material { material }
{
}

Model::Model(std::shared_ptr<Material> material, std::vector<Mesh> meshes) : _material{ material }, _meshes{ meshes }
{
}

void Model::Draw(Shader shader, glm::mat4 transform)
{
	_material->Bind(shader);

	for (auto mesh : _meshes) {
		auto modelMat = transform * Transform * mesh.Transform;
		shader.SetMat4("model", modelMat);
		mesh.Draw();
	}
}