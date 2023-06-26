#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <model.h>
#include <shader.h>

class Object {
public:
	Object(std::vector<Model> models);
	void Update(float deltaTime) {};
	void Draw(Shader shader);

	static Object CreatePlane();
	static Object CreateStand();
	static Object CreateBook();
	static Object CreateClock();
	static Object CreateJewel();
	static Object CreateBall();
	static Object CreateMonitor();
public:
	glm::mat4 Transform{ 1.f };
private:
	std::vector<Model> _models{};
};