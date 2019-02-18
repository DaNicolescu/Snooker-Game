#define _USE_MATH_DEFINES
#include "Object2D.h"

#include <Core/Engine.h>
#include <math.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	// coordonate omogene
	square->center = glm::vec3(corner.x + length / 2.0f, corner.y + length / 2.0, 1);
	square->bottomLeftCorner = glm::vec3(corner.x, corner.y, 1);
	square->side = length;

	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	} else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	// coordonate omogene
	rectangle->center = glm::vec3(corner.x + width / 2.0f, corner.y + height / 2.0, 1);
	rectangle->bottomLeftCorner = glm::vec3(corner.x, corner.y, 1);

	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	} else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);

	return rectangle;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(center, color));
	for (int i = 0; i < 360; i++) {
		vertices.push_back(VertexFormat(glm::vec3(center.x + radius * cos(i * M_PI / 180), center.y + radius * sin(i * M_PI / 180), 0), color));
	}

	std::vector<unsigned short> indices;

	for (int i = 0; i < 359; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	indices.push_back(0);
	indices.push_back(360);
	indices.push_back(1);

	Mesh* circle = new Mesh(name);
	// coordonate omogene
	circle->center = center;
	circle->radius = radius;

	circle->InitFromData(vertices, indices);

	return circle;
}