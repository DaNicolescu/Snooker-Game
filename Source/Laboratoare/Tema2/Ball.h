#pragma once

#include <string>
#include <Component/SimpleScene.h>

class Ball {
public:
	Ball(glm::vec3 center, float radius, glm::vec3 color, std::string colorName) :
		center(center),
		radius(radius),
		color(color),
		colorName(colorName)
	{
		initialCenter = center;
		moveVector = glm::vec3(0, 0, 0);
		frameMove = glm::vec3(0, 0, 0);

		inPocket = false;
	}
	~Ball();

	bool inPocket;
	glm::vec3 color;
	std::string colorName;
	glm::vec3 initialCenter;
	glm::vec3 center;
	glm::vec3 moveVector;
	glm::vec3 frameMove;
	float radius;
	float speed;
private:

};