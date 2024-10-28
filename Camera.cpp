#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
	
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	yaw = yaw + 180.0f;
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}

glm::mat4
Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void 
Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SenceY;
	Yaw -= deltaX * SenceX;
	updateCameraVectors();
}

void Camera::UpdateCameraPos() {
	Position += Forward * speedZ * 0.005f;
	Position += Right * speedX * 0.005f;
	Position += Up * speedY * 0.005f;
}

void 
Camera::updateCameraVectors(){
	// calculate the new Front vector
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}
