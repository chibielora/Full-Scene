#pragma once
#include <glm/glm.hpp>

struct DirectionalLight {
	glm::vec3 direction { 0.f, -1.0f, 0.f };

	glm::vec3 ambient { 0.1f, 0.1f, 0.1f };
	glm::vec3 diffuse { 0.8f, 0.8f, 0.8f };
	glm::vec3 specular { 0.5f, 0.5f, 0.5f };
};

struct PointLight {
	glm::vec3 position;
	glm::vec3 ambient { 0.05f, 0.05f, 0.05f };
	glm::vec3 diffuse { 0.8f, 0.8f, 0.8f };
	glm::vec3 specular { 1.0f, 1.0f, 1.0f };
	float constant{ 1.0f };
	float linear{ 0.09f };
	float quadratic{ 0.032f };
};
