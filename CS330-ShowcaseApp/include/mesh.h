#pragma once
#include <vector>
#include <types.h>
#include <glad/glad.h>

class Mesh {
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	Mesh(GLenum mode, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	static Mesh CreateBox(float width, float height, float depth, glm::vec4 color = {1.f, 1.f, 1.f, 1.f});
	static Mesh CreateCircle(float radius, uint32_t sectors, glm::vec4 color = { 1.f, 1.f, 1.f, 1.f });
	static Mesh CreateCylinder(float height, float topRadius, float bottomRadius, uint32_t sectors, glm::vec4 color = { 1.f, 1.f, 1.f, 1.f });
	static Mesh CreateCone(float height, float radius, uint32_t sectors, glm::vec4 color = { 1.f, 1.f, 1.f, 1.f }) { CreateCylinder(height, 0, radius, sectors, color); }
	static Mesh CreateSphere(float radius, uint32_t stacks, uint32_t sectors, glm::vec4 color = { 1.f, 1.f, 1.f, 1.f });

	void Draw();

	glm::mat4 Transform{ 1.f };

private:
	GLenum _mode;
	size_t _elementCount {0};
	GLuint _vertexBufferObject {};
	GLuint _shaderProgram {};
	GLuint _vertexArrayObject {};
	GLuint _elementBufferObject {};
};
