#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	enum class MoveDirection {
		Forward,
		Backward,
		Left,
		Right,
		Up,
		Down
	};
	Camera(
		float aspectRatio,
		glm::vec3 initialPosition,
		bool isPerspective = true
	);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition() { return _position; }

	void SetAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; }
	bool IsPerspective() const { return _isPerspective;  }
	void SetIsPerspective(bool isPerspective) { _isPerspective = isPerspective;  }
	void MoveCamera(MoveDirection direction, float moveAmount);
	void RotateBy(float yaw, float pitch);
private:
	void recalculateVectors();
private:
	bool _isPerspective { true };

	glm::vec3 _position{};
	glm::vec3 _lookVector {};
	glm::vec3 _upVector { 0.f, 1.f, 0.f };

	float _yaw{ -90.f };
	float _pitch{ 0.f };
	
	float _fov{ 75.f };
	float _aspectRatio{ 1.f };
	float _nearClip{ 0.1f };
	float _farClip{ 100.f };
};