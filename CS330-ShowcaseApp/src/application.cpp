#include <application.h>
#include <types.h>
#include <shader.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

Application::Application(
	std::string WindowTitle, 
	int width, 
	int height
) : _applicationName{ WindowTitle }, 
	_width{ width }, 
	_height{ height },
	_camera{ (float)_width / (float)_height, { 0.f, 5.f, 10.f}, true },
	_cameraAngleSpeed{ 0.15f, 0.15f }
{}

void Application::Run() {
	// Open the window
	if (!openWindow()) {
		return;
	}

	setupInputs();

	_running = true;

	// Arrange the elements in the window
	setupScene();

	// Run app
	while (_running){
		double currentTime = glfwGetTime();

		if (_lastFrameTime == -1.f) {
			_lastFrameTime = currentTime;
		}

		auto deltaTime = currentTime - _lastFrameTime;
		_lastFrameTime = currentTime;

		if (glfwWindowShouldClose(_window)) {
			_running = false;
			continue;
		}

		// Call function to update triangles
		update(deltaTime);
		// Call function to render triangles
		draw();
	}

	glfwTerminate();
}

bool Application::openWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(_width, _height, _applicationName.c_str(), nullptr, nullptr);

	if (!_window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, (void*)this);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);

		auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->_width = width;
		app->_height = height;

		app->_camera.SetAspectRatio((float) width / (float) height);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	return true;
}

void Application::setupInputs() {
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

		switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) {
				app->_running = false;
			}
			break;
		case GLFW_KEY_F11:
			if (action == GLFW_PRESS) {
				app->_camera.SetIsPerspective(!app->_camera.IsPerspective());
			}
			break;
		default: {}
		}
	});

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset) {
		auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
		app->incrementCameraSpeed((float)yoffset * 2);
	});
}

void Application::setupScene() {
	Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
	Path vertexShaderPath = shaderPath / "lighting.vs";
	Path fragmentShaderPath = shaderPath / "lighting.fs";
	_shader = Shader(vertexShaderPath, fragmentShaderPath);

	// Add lights
	glm::vec3 lightColor = { 1.f, 1.f, 1.f };
	float ambientIntensity = 0.2f;
	float diffuseIntensity = 0.8f;
	float specularIntensity = 0.5;
	_dirLight = DirectionalLight{
		.direction = { 0.f, -1.0f, -1.f },
		.ambient = lightColor * ambientIntensity,
		.diffuse = lightColor * diffuseIntensity,
		.specular = lightColor * specularIntensity
	};

	lightColor = { 1.f, 0.5f, 0.5f };
	PointLight light1 = {
		.position = { -4.f, 5.5f, -4.f },
		.ambient = lightColor * ambientIntensity,
		.diffuse = lightColor * diffuseIntensity,
		.specular = lightColor * specularIntensity
	};
	lightColor = { 0.5f, 0.5f, 1.0f };
	PointLight light2 = {
		.position = { 4.f, 5.5f, -4.f },
		.ambient = lightColor * ambientIntensity,
		.diffuse = lightColor * diffuseIntensity,
		.specular = lightColor * specularIntensity
	};
	_pointLights.emplace_back(light1);
	_pointLights.emplace_back(light2);

	auto plane = Object::CreatePlane();
	auto stand = Object::CreateStand();
	auto monitor = Object::CreateMonitor();
	monitor.Transform = glm::translate(monitor.Transform, { 0.f, 1.f, -0.5f });
	
	auto clock = Object::CreateClock();
	clock.Transform = glm::translate(clock.Transform, { 1.75f, 1.f, 0.2f });

	auto book = Object::CreateBook();
	book.Transform = glm::translate(book.Transform, { 3.f, 1.f, 0.f });

	auto ball = Object::CreateBall();
	ball.Transform = glm::translate(ball.Transform, { -2.5f, 1.f, 0.3f });

	auto jewelAngle = glm::radians(45.f);
	auto jewel = Object::CreateJewel();
	jewel.Transform = glm::translate(jewel.Transform, { 0.f, 1.f, 0.5 });

	auto spinAngle = glm::two_pi<float>() / 24;
	auto tiltAngle = glm::radians(45.f);
	jewel.Transform = glm::rotate(jewel.Transform, spinAngle, glm::vec3(0.f, 1.f, 0.f));
	jewel.Transform = glm::rotate(jewel.Transform, tiltAngle, glm::vec3(glm::cos(spinAngle), 0.f, glm::sin(spinAngle)));
	

	_objects.push_back(plane);
	_objects.push_back(stand);
	_objects.push_back(monitor);
	_objects.push_back(clock);
	_objects.push_back(book);
	_objects.push_back(ball);
	_objects.push_back(jewel);
}

bool Application::update(double deltaTime) {
	glfwPollEvents();

	handleInput(deltaTime);

	return false;
}

bool Application::draw() {
	// Clear the screen with specific color
	glClearColor(.0f, .1f, .2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera matrix to move objects in the plane
	glm::mat4 view = _camera.GetViewMatrix();
	glm::mat4 projection = _camera.GetProjectionMatrix();
	glm::vec3 viewPos = _camera.GetPosition();
	_shader.SetMat4("projection", projection);
	_shader.SetMat4("view", view);
	_shader.SetVec3("viewPos", viewPos);

	for (auto& object : _objects) {
		_shader.SetVec3("dirLight.direction", _dirLight.direction);
		_shader.SetVec3("dirLight.ambient", _dirLight.ambient);
		_shader.SetVec3("dirLight.diffuse", _dirLight.diffuse);
		_shader.SetVec3("dirLight.specular", _dirLight.specular);

		for (auto i = 0; i < _pointLights.size(); i++) {
			auto pointLight = _pointLights[i];
			std::string uniformBase = "pointLights[" + std::to_string(i) + "].";

			_shader.SetVec3(uniformBase + "position", pointLight.position);
			_shader.SetVec3(uniformBase + "ambient", pointLight.ambient);
			_shader.SetVec3(uniformBase + "diffuse", pointLight.diffuse);
			_shader.SetVec3(uniformBase + "specular", pointLight.specular);
			_shader.SetFloat(uniformBase + "constant", pointLight.constant);
			_shader.SetFloat(uniformBase + "linear", pointLight.linear);
			_shader.SetFloat(uniformBase + "quadratic", pointLight.quadratic);
		}

		object.Draw(_shader);
	}

	glfwSwapBuffers(_window);

	return false;
}

void Application::handleInput(double deltaTime) {
	float moveAmount = _cameraSpeed * (float)deltaTime;

	if (glfwGetKey(_window, GLFW_KEY_W)) {
		_camera.MoveCamera(Camera::MoveDirection::Forward, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_S)) {
		_camera.MoveCamera(Camera::MoveDirection::Backward, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_A)) {
		_camera.MoveCamera(Camera::MoveDirection::Left, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_D)) {
		_camera.MoveCamera(Camera::MoveDirection::Right, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_Q)) {
		_camera.MoveCamera(Camera::MoveDirection::Up, moveAmount);
	}
	if (glfwGetKey(_window, GLFW_KEY_E)) {
		_camera.MoveCamera(Camera::MoveDirection::Down, moveAmount);
	}

	double xpos, ypos;
	glfwGetCursorPos(_window, &xpos, &ypos);

	mousePositionCallback(xpos, ypos);
}

void Application::mousePositionCallback(double xpos, double ypos) {
	if (!_firstMouse) {
		_lastMousePosition.x = static_cast<float>(xpos);
		_lastMousePosition.y = static_cast<float>(ypos);

		_firstMouse = true;
	}
	glm::vec2 moveAmount {
		xpos - _lastMousePosition.x,
		_lastMousePosition.y - ypos
	};

	_camera.RotateBy(moveAmount.x * _cameraAngleSpeed.x, moveAmount.y * _cameraAngleSpeed.y);

	_lastMousePosition.x = static_cast<float>(xpos);
	_lastMousePosition.y = static_cast<float>(ypos);
}

void Application::incrementCameraSpeed(float amount)
{
	_cameraSpeed += amount;

	_cameraSpeed = std::clamp(_cameraSpeed, 1.f, 9.f);
}
