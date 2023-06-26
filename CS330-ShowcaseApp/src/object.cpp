#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <material.h>
#include <model.h>
#include <object.h>
#include <shader.h>

Object::Object(std::vector<Model> models) : _models{ models } {
}

void Object::Draw(Shader shader) {
	for (auto model : _models) {
		model.Draw(shader, Transform);
	}
}

Object Object::CreatePlane()
{
	std::vector<Model> models {};
	glm::vec4 color = { 0.3f, 0.3f, 0.3f, 1.f };
	glm::vec3 normal = { 0.f, 1.f, 0.f };
	std::vector<Vertex> vertices {
		{
			.Position = { -50.f, 0.f, 50.f },
			.Color = color,
			.Normal = normal,
			.Uv = { 0.f, 0.f }
		},
		{
			.Position = { 50.f, 0.f, 50.f},
			.Color = color,
			.Normal = normal,
			.Uv = { 1.f, 0.f }
		},
		{
			.Position = { 50.f, 0.f, -50.f},
			.Color = color,
			.Normal = normal,
			.Uv = { 1.f, 1.f }
		},
		{
			.Position = { -50.f, 0.f, -50.f},
			.Color = color,
			.Normal = normal,
			.Uv = { 0.f, 1.f }
		}
	};
	std::vector<uint32_t> indices {
		0, 1, 2,
		0, 2, 3
	};
	Mesh mesh{ vertices, indices };
	auto texture = std::make_shared<Texture>(Texture::texturePath / "plane.png");
	auto material = std::make_shared<Material>(texture);
	material->shininess = 2.f;
	Model plane{ material, { mesh } };
	models.push_back(plane);

	return Object(models);
}

Object Object::CreateStand() {
	std::vector<Model> models {};

	float width = 8.5f;

	Mesh topMesh = Mesh::CreateBox(width, 0.1f, 3.f);
	topMesh.Transform = glm::translate(topMesh.Transform, { 0.f, 0.9f, 0.f });
	Mesh leftMesh = Mesh::CreateBox(0.1f, 0.9f, 3.f);
	leftMesh.Transform = glm::translate(leftMesh.Transform, { -width / 2 + 0.05f, 0.f, 0.f });
	Mesh rightMesh = Mesh::CreateBox(0.1f, 0.9f, 3.f);
	rightMesh.Transform = glm::translate(rightMesh.Transform, { width / 2 - 0.05f, 0.f, 0.f });
	auto texture = std::make_shared<Texture>(Texture::texturePath / "cloudy.png");
	auto material = std::make_shared<Material>(texture);

	Model model{ material, { topMesh, leftMesh, rightMesh } };
	models.push_back(model);

	return Object(models);
}

Object Object::CreateMonitor() {
	std::vector<Model> models {};

	glm::vec4 frameColor { 0.15f, 0.15f, 0.15f, 1.f };
	Mesh frameBase = Mesh::CreateCylinder(0.2f, 1.0f, 1.8f, 10, frameColor);
	frameBase.Transform = glm::scale(frameBase.Transform, { 1.f, 1.f, 0.5f });
	Mesh frameBaseTop = Mesh::CreateCircle(1.0f, 10, frameColor);
	frameBaseTop.Transform = glm::scale(frameBaseTop.Transform, { 1.f, 1.f, 0.5f });
	frameBaseTop.Transform = glm::translate(frameBaseTop.Transform, { 0.f, 0.2f, 0.f });
	Mesh frameArm = Mesh::CreateBox(0.75f, 3.f, 0.2f, frameColor);
	frameArm.Transform = glm::translate(frameArm.Transform, { 0.f, 0.2f, 0.f });
	Mesh frameScreen = Mesh::CreateBox(6.7f, 4.f, 0.2f, frameColor);
	frameScreen.Transform = glm::translate(frameScreen.Transform, { 0.f, 0.5f, 0.2f });

	auto frameTexture = std::make_shared<Texture>(Texture::texturePath / "glossy.jpg");
	auto frameMaterial = std::make_shared<Material>(frameTexture);
	frameMaterial->shininess = 400.f;

	glm::vec4 screenColor = { 1.f, 1.f, 1.f, 1.f };
	glm::vec3 normal = { 0.f, 0.f, 1.f };
	std::vector<Vertex> screenVertices {
		{
			.Position = { -3.25f, 0.f, 0.f },
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 0.f, 0.f }
		},
		{
			.Position = { 3.25f, 0.f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 1.f, 0.f }
		},
		{
			.Position = { 3.25f, 3.8f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 1.f, 1.f }
		},
		{
			.Position = { -3.25f, 3.8f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 0.f, 1.f }
		}
	};
	std::vector<uint32_t> screenIndices {
		0, 1, 2,
		0, 2, 3
	};
	Mesh screenMesh{ screenVertices, screenIndices };
	auto minecraftTexture = std::make_shared<Texture>(Texture::texturePath / "minecraft.jpg");
	auto screenMaterial = std::make_shared<Material>(minecraftTexture);
	Model screen{ screenMaterial, { screenMesh } };
	screen.Transform = glm::translate(screen.Transform, { 0.f, 0.6f, 0.301f });
	Model frame{ frameMaterial, { frameBase, frameBaseTop, frameArm, frameScreen } };

	models.push_back(frame);
	models.push_back(screen);

	return Object(models);
}

Object Object::CreateClock() {
	std::vector<Model> models {};
	glm::vec4 color { 0.4f, 0.4f, 0.4f, 1.f };
	float width = 0.75f;
	float height = 0.85f;
	float depth = 0.3f;
	auto tiltAngle = glm::radians(-15.f);
	Mesh clockMesh = Mesh::CreateBox(width, height, depth, color);
	clockMesh.Transform = glm::translate(clockMesh.Transform, { 0.f, -depth * glm::sin(tiltAngle) / 2, depth * glm::cos(tiltAngle) / 2});
	clockMesh.Transform = glm::rotate(clockMesh.Transform, tiltAngle, glm::vec3( 1, 0, 0 ));

	Mesh supportMesh = Mesh::CreateBox(width * 0.4f, height / 2, 0.01f, color);
	supportMesh.Transform = glm::translate(supportMesh.Transform, { 0.f, 0.f, -depth * 3 * glm::cos(tiltAngle) / 4 });
	supportMesh.Transform = glm::rotate(supportMesh.Transform, -tiltAngle, glm::vec3(1, 0, 0));

	auto texture = std::make_shared<Texture>(Texture::texturePath / "glossy.jpg");
	auto material = std::make_shared<Material>(texture);
	material->shininess = 16.f;

	glm::vec4 screenColor = { 1.f, 1.f, 1.f, 1.f };
	glm::vec3 normal = { 0.f, 0.f, 1.f };
	std::vector<Vertex> screenVertices {
		{
			.Position = { -width / 2 + 0.05f, 0.f, 0.f },
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 0.f, 0.f }
		},
		{
			.Position = { width / 2 - 0.05f, 0.f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 1.f, 0.f }
		},
		{
			.Position = { width / 2 - 0.05f, height - 0.1f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 1.f, 1.f }
		},
		{
			.Position = { -width / 2 + 0.05f, height - 0.1f, 0.f},
			.Color = screenColor,
			.Normal = normal,
			.Uv = { 0.f, 1.f }
		}
	};
	std::vector<uint32_t> screenIndices {
		0, 1, 2,
		0, 2, 3
	};
	Mesh screenMesh{ screenVertices, screenIndices };
	auto screenTexture = std::make_shared<Texture>(Texture::texturePath / "clock.jpg");
	auto screenMaterial = std::make_shared<Material>(screenTexture);
	screenMaterial->shininess = 128.f;
	Model base{ material, { clockMesh, supportMesh } };
	Model screen{ screenMaterial, { screenMesh } };
	// Couldn't figure out the math. Approximated needed translation
	screen.Transform = glm::translate(screen.Transform, { 0.f, 0.125f, depth - 0.005f });
	screen.Transform = glm::rotate(screen.Transform, tiltAngle, glm::vec3(1, 0, 0));

	models.push_back(base);
	models.push_back(screen);

	return Object(models);
}

Object Object::CreateBook() {
	std::vector<Model> models {};

	Mesh mesh = Mesh::CreateBox(1.5f, 0.1f, 2.5f);

	auto texture = std::make_shared<Texture>(Texture::texturePath / "book.png");
	auto material = std::make_shared<Material>(texture);

	Model model{ material, { mesh } };

	models.push_back(model);

	return Object(models);
}

Object Object::CreateBall() {
	std::vector<Model> models {};
	float radius = 0.35f;

	Mesh mesh = Mesh::CreateSphere(radius, 16, 32, {1.f, 0.2f, 0.8f, 1.f});
	mesh.Transform = glm::translate(mesh.Transform, { 0.f, radius, 0.f });
	mesh.Transform = glm::rotate(mesh.Transform, 1.07f, glm::vec3{ 1, 1, 1});
	auto texture = std::make_shared<Texture>(Texture::texturePath / "fuzz.jpg");
	auto material = std::make_shared<Material>(
		texture,
		glm::vec3 { 1.f, 1.f, 1.f },
		glm::vec3 { 0.8f, 0.8f, 0.8f },
		glm::vec3 { 0.5f, 0.5f, 0.5f }
	);
	material->shininess = 2.f;
	Model model{ material, { mesh } };

	models.push_back(model);

	return Object(models);
}

Object Object::CreateJewel() {

	std::vector<Model> models {};

	auto color = glm::vec4{ 0.2f, 0.2f, 0.5f, 1.f };
	Mesh jewelLowerMesh = Mesh::CreateCylinder(0.5f, 0.5f, 0.f, 12, color);
	jewelLowerMesh.Transform = glm::translate(jewelLowerMesh.Transform, glm::vec3(0.f, -0.5f, 0.f));
	Mesh jewelUpperMesh = Mesh::CreateCylinder(0.2f, 0.3f, 0.5f, 12, color);
	Mesh jewelTopMesh = Mesh::CreateCircle(0.3f, 12, color);
	jewelTopMesh.Transform = glm::translate(jewelTopMesh.Transform, glm::vec3(0.f, 0.2f, 0.f));
	auto glossyTexture = std::make_shared<Texture>(Texture::texturePath / "glossy-transparent.png");
	auto glossyMaterial = std::make_shared<Material>(glossyTexture);
	glossyMaterial->shininess = 128.f;

	Model jewel{ glossyMaterial, std::vector<Mesh> { jewelLowerMesh, jewelUpperMesh, jewelTopMesh } };
	jewel.Transform = glm::translate(jewel.Transform, { 0.f, 0.5f, 0.f });
	models.push_back(jewel);

	return Object(models);
}