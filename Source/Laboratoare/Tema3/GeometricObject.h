#pragma once

#include <string>
#include <vector>
#include <string>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <include/glm.h>

namespace GeoemtricObject
{
	Mesh* CreateSquare(std::string name, glm::vec3 center, float length);
	Mesh* CreateRectagularCuboid(std::string name, glm::vec3 center, float length, float height, float width);
	Mesh* CreateTriangularPrism(std::string name, glm::vec3 center, float length, float height, float width);
	Mesh* CreateCylinder(std::string name, glm::vec3 center, float length, float width, float height, int numOfFaces);
}