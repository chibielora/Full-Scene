#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <light.h>
#include <object.h>
#include <shader.h>
#include <texture.h>

class Application {
public:
	Application(std::string WindowTitle, int width, int height);
	void Run();

private:
	bool openWindow();
	void setupInputs();
	void setupScene();
	bool update(double deltaTime);
	bool draw();
	void handleInput(double deltaTime);
	void mousePositionCallback(double xpos, double ypox);
	void incrementCameraSpeed(float amount);

private:
	std::string _applicationName {};
	int _width {};
	int _height {};
	GLFWwindow* _window { nullptr };
	Shader _shader{};

	float _cameraSpeed{ 5.f };
	glm::vec2 _cameraAngleSpeed;
	Camera _camera;
	std::vector<Object> _objects;
	bool _running { false };

	double _lastFrameTime{ -1 };
	bool _firstMouse = false;
	glm::vec2 _lastMousePosition {};

	DirectionalLight _dirLight{};
	std::vector<PointLight> _pointLights {};
};
