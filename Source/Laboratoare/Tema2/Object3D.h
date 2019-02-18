#pragma once

#include <string>

#include <vector>
#include <string>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <include/glm.h>

namespace Object3D
{
	enum class viewPlane {
		XY,
		XZ,
		YZ
	};

	Mesh* CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);
	Mesh* CreateRectagularCuboid(const char *name, glm::vec3 center, float length, float height, float width, glm::vec3 color);
	Mesh* CreateHalfCircle(const char *name, glm::vec3 center, float radius, glm::vec3 color, bool up, bool reversed);
	Mesh* CreateQuarterCircle(const char *name, glm::vec3 center, float radius, glm::vec3 color, Object3D::viewPlane plane, bool reversed, bool rotated);
}