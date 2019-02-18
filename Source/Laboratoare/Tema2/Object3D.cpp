#include "Object3D.h"

Mesh* Object3D::CreateRectagularCuboid(const char *name, glm::vec3 center, float length, float height, float width, glm::vec3 color) {
	Mesh* mesh;
	
	float halfLength = length / 2.0;
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	float centerX = center.x;
	float centerY = center.y;
	float centerZ = center.z;
	
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), color),
		VertexFormat(glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), color),
		VertexFormat(glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), color),
		VertexFormat(glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), color),
		VertexFormat(glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ - halfWidth), color),
		VertexFormat(glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), color),
		VertexFormat(glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ - halfWidth), color),
		VertexFormat(glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};

	mesh = Object3D::CreateMesh(name, vertices, indices);
	mesh->center = center;
	mesh->length = length;
	mesh->width = width;
	mesh->height = height;
	
	return mesh;
}

Mesh* Object3D::CreateHalfCircle(const char *name, glm::vec3 center, float radius, glm::vec3 color, bool up, bool reversed) {
	Mesh* mesh;
	std::vector<VertexFormat> vertices;
	int direction = 1;

	if (reversed) {
		direction = -1;
	}

	vertices.push_back(VertexFormat(center, color));
	for (int i = 0; i < 181; i++) {
		if (!up) {
			vertices.push_back(VertexFormat(glm::vec3(center.x + radius * cos(i * M_PI / 180),
				center.y, center.z + direction * (radius * sin(i * M_PI / 180))), color));
		}
		else {
			vertices.push_back(VertexFormat(glm::vec3(center.x + radius * cos(i * M_PI / 180),
				center.y + direction * (radius * sin(i * M_PI / 180)), center.z), color));
		}
	}

	std::vector<unsigned short> indices;

	for (int i = 0; i < 180; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	mesh = Object3D::CreateMesh(name, vertices, indices);
	mesh->center = center;
	mesh->radius = radius;

	return mesh;
}

Mesh* Object3D::CreateQuarterCircle(const char *name, glm::vec3 center, float radius, 
	glm::vec3 color, Object3D::viewPlane plane, bool reversed, bool rotated) {
	Mesh* mesh;
	std::vector<VertexFormat> vertices;
	int direction1 = 1;
	int direction2 = 1;

	if (reversed) {
		direction1 = -1;
	}

	if (rotated) {
		direction2 = -1;
	}

	vertices.push_back(VertexFormat(center, color));
	for (int i = 0; i < 91; i++) {
		switch (plane) {
		case Object3D::viewPlane::XY:
			vertices.push_back(VertexFormat(glm::vec3(center.x + direction1 * radius * cos(i * M_PI / 180),
				center.y + radius * sin(i * M_PI / 180), center.z), color));
			break;
		case Object3D::viewPlane::XZ:
			vertices.push_back(VertexFormat(glm::vec3(center.x + direction2 * radius * cos(i * M_PI / 180),
				center.y, center.z + direction1 * (radius * sin(i * M_PI / 180))), color));
			break;
		case Object3D::viewPlane::YZ:
			vertices.push_back(VertexFormat(glm::vec3(center.x, center.y + radius * cos(i * M_PI / 180), 
				center.z + direction1 * (radius * sin(i * M_PI / 180))), color));
			break;
		}
	}

	std::vector<unsigned short> indices;

	for (int i = 0; i < 90; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	mesh = Object3D::CreateMesh(name, vertices, indices);
	mesh->center = center;
	mesh->radius = radius;

	return mesh;
}

Mesh* Object3D::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	Mesh* mesh;

	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object

	mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}
