#pragma once
#include <include/glm.h>
#include <include/math.h>
#include "Tema2Camera.h"

#include <iostream>

Tema2Camera::Tema2Camera(glm::mat4 projectionMatrix)
{
	positionWhiteBall();
	distanceToTarget = 0.4;
	isTracking = false;
	this->projectionMatrix = projectionMatrix;
}

Tema2Camera::Tema2Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up, glm::mat4 projectionMatrix)
{
	Set(position, center, up);
	distanceToTarget = 0.4;
	isTracking = false;
	this->projectionMatrix = projectionMatrix;
}

Tema2Camera::~Tema2Camera()
{ }


void Tema2Camera::positionWhiteBall()
{
	position = glm::vec3(2.8, 3.5, 1);
	forward = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(1, 0, 0);
	RotateFirstPerson_OX(-0.85);
	RotateFirstPerson_OY(1.1);
	TranslateForward(2);

	isTracking = false;
}

void Tema2Camera::trackWhiteBall(Ball* whiteBall)
{
	position = glm::vec3(whiteBall->center.x + distanceToTarget, whiteBall->center.y + 0.1, whiteBall->center.z);
	forward = glm::vec3(-1, 0, 0);
	up = glm::vec3(0, 1, 0);
	right = glm::vec3(0, 0, 1);

	RotateThirdPerson_OY(0.2);
	RotateThirdPerson_OX(0.9);

	isTracking = true;
}

void Tema2Camera::viewShot() 
{
	position = glm::vec3(0, 3, 0);
	forward = glm::vec3(0, -1, 0);
	up = glm::vec3(0, 0, 1);
	right = glm::vec3(1, 0, 0);

	isTracking = false;
}

// Update camera
void Tema2Camera::Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
{
	this->position = position;
	forward = glm::normalize(center - position);
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward);
}

void Tema2Camera::MoveForward(float distance)
{
	glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	// movement will keep the camera at the same height always
	// Example: If you rotate up/down your head and walk forward you will still keep the same relative distance (height) to the ground!
	// Translate the camera using the DIR vector computed from forward
}

void Tema2Camera::TranslateForward(float distance)
{
	// TODO : Translate the camera using the "forward" vector
	position += glm::normalize(forward) * distance;
}

void Tema2Camera::TranslateUpword(float distance)
{
	// TODO : Translate the camera using the up vector
	position += glm::normalize(up) * distance;
}

void Tema2Camera::TranslateRight(float distance)
{
	// TODO
	// Translate the camera using the "right" vector
	// Usually translation using camera "right' is not very useful because if the camera is rotated around the "forward" vector 
	// translation over the right direction will have an undesired effect; the camera will get closer or farther from the ground
	// Using the projected right vector (onto the ground plane) makes more sense because we will keep the same distance from the ground plane
	position += glm::normalize(right) * distance;
}

void Tema2Camera::RotateFirstPerson_OX(float angle)
{
	// TODO
	// Compute the new "forward" and "up" vectors
	// Attention! Don't forget to normalize the vectors
	// Use glm::rotate()
	forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1, 0, 0)) * glm::vec4(forward, 1)));
	up = glm::cross(right, forward);
}

void Tema2Camera::RotateFirstPerson_OY(float angle)
{
	// TODO
	// Compute the new "forward", "up" and "right" vectors
	// Don't forget to normalize the vectors
	// Use glm::rotate()
	forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
	up = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(up, 1)));
	right = glm::cross(forward, up);
}

void Tema2Camera::RotateFirstPerson_OZ(float angle)
{
	// TODO
	// Compute the new Right and Up, Forward stays the same
	// Don't forget to normalize the vectors
	right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::vec4(right, 1)));
	up = glm::cross(right, forward);
}

void Tema2Camera::RotateThirdPerson_OX(float angle)
{
	// TODO
	// Rotate the camera in Third Person mode - OX axis
	// Use distanceToTarget as translation distance
	TranslateForward(distanceToTarget);
	RotateFirstPerson_OX(angle);
	TranslateForward(-distanceToTarget);
}

void Tema2Camera::RotateThirdPerson_OY(float angle)
{
	// TODO
	// Rotate the camera in Third Person mode - OY axis
	TranslateForward(distanceToTarget);
	RotateFirstPerson_OY(angle);
	TranslateForward(-distanceToTarget);
}

void Tema2Camera::RotateThirdPerson_OZ(float angle)
{
	// TODO
	// Rotate the camera in Third Person mode - OZ axis
	TranslateForward(distanceToTarget);
	RotateFirstPerson_OZ(angle);
	TranslateForward(-distanceToTarget);
}

glm::mat4 Tema2Camera::GetViewMatrix()
{
	// Returns the View Matrix
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Tema2Camera::GetProjectionMatrix()
{
	return this->projectionMatrix;
}

glm::vec3 Tema2Camera::GetTargetPosition()
{
	return position + forward * distanceToTarget;
}

glm::vec3 Tema2Camera::getCameraPosition() {
	return this->position;
}
