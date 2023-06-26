#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <algorithm>

Camera::Camera(float aspectRatio, glm::vec3 initialPosition, bool isPerspective) : 
	_aspectRatio{ aspectRatio }, 
	_position{ initialPosition },
	_isPerspective{ isPerspective }
{ 
	recalculateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 view = glm::lookAt(_position, _position + _lookVector, _upVector);
	return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (_isPerspective) {
		return glm::perspective(glm::radians(_fov), _aspectRatio, _nearClip, _farClip);
	}
	
	return glm::ortho(-_aspectRatio, _aspectRatio, -1.f, 1.f, _nearClip, _farClip);
}

void Camera::MoveCamera(MoveDirection direction, float moveAmount)
{
	glm::vec3 moveDirection {};
	switch (direction) {
	case MoveDirection::Forward:
		moveDirection = _lookVector;
		break;
	case MoveDirection::Backward:
		moveDirection = -_lookVector;
		break;
	case MoveDirection::Left:
		moveDirection = glm::normalize(glm::cross(_upVector, _lookVector));
		break;
	case MoveDirection::Right:
		moveDirection = -glm::normalize(glm::cross(_upVector, _lookVector));
		break;
	case MoveDirection::Up:
		moveDirection = glm::vec3{ 0.f, 1.f, 0.f };
		break;
	case MoveDirection::Down:
		moveDirection = glm::vec3{ 0.f, -1.f, 0.f };
		break;
	}

	_position += moveDirection * moveAmount;
}

void Camera::RotateBy(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;

	_pitch = std::clamp(_pitch, -89.f, 89.f);

	recalculateVectors();
}

void Camera::recalculateVectors()
{
	_lookVector = glm::normalize(
		glm::vec3{
			glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch)),
			glm::sin(glm::radians(_pitch)),
			glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch))
		}
	);

	auto rightDirection = glm::normalize(glm::cross(_lookVector, glm::vec3(0.f, 1.f, 0.f)));
	_upVector = glm::normalize(glm::cross(rightDirection, _lookVector));
}


