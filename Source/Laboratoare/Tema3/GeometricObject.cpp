#include "GeometricObject.h"

// creeaza un patrat pe XoZ
Mesh* GeoemtricObject::CreateSquare(std::string name, glm::vec3 center, float length)
{	
	float halfLength = length / 2.0f;

	std::vector<glm::vec3> vertices
	{
		glm::vec3(halfLength + center.x, center.y, halfLength + center.z),	// Top Right
		glm::vec3(halfLength + center.x, center.y, -halfLength + center.z),	// Bottom Right
		glm::vec3(-halfLength + center.x, center.y, -halfLength + center.z),	// Bottom Left
		glm::vec3(-halfLength + center.x, center.y, halfLength + center.z),	// Top Left
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0)
	};

		
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0, 1),
		glm::vec2(1, 1),
		glm::vec2(1, 0)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);
		
	return mesh;
}

// creeaza un paralelipiped dreptunghic
Mesh* GeoemtricObject::CreateRectagularCuboid(std::string name, glm::vec3 center, float length, float height, float width)
{

	float halfLength = length / 2.0;
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	float centerX = center.x;
	float centerY = center.y;
	float centerZ = center.z;

	float dimPattern = 0.5f;

	std::vector<glm::vec3> vertices
	{
		// latura fata
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), // 0
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), // 1
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), // 2
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 3

		// latura spate
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ - halfWidth), // 4
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), // 5
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ - halfWidth), // 6
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth), // 7

		// latura stanga
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), // 1 8
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), // 5 9
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 3 10
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth), // 7 11

		// latura dreapta
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ - halfWidth), // 4 12
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), // 0 13
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ - halfWidth), // 6 14
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth),  // 2 15

		// "capac"
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), // 2 16
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 3 17
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ - halfWidth), // 6 18
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth)  // 7 19
		
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0)
	};

	// coordonatele de textura
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(length / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(length / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(length / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(length / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(width / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(width / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(width / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(width / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.001f, 0),
		glm::vec2(0, 0.001f),
		glm::vec2(0.001f, 0.001f)
	};

	// indici
	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		16, 17, 19,		16, 19, 18,
		8, 11, 10,		8, 9, 11,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		15, 14, 12,		13, 15, 12
	};


	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);

	return mesh;
}

// creeaza o prisma cu baza triunghi dreptunghic
Mesh* GeoemtricObject::CreateTriangularPrism(std::string name, glm::vec3 center, float length, float height, float width)
{

	float halfLength = length / 2.0;
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	float centerX = center.x;
	float centerY = center.y;
	float centerZ = center.z;

	float dimPattern = 0.5f;

	std::vector<glm::vec3> vertices
	{
		// baza de jos
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), // 0
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), // 1
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), // 2
		
		// baza de sus
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), // 3
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 4
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth), // 5

		// latura fata
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), // 0 6
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), // 1 7
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), // 3 8
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 4 9

		// latura dreapta
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ + halfWidth), // 1 10
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), // 2 11
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ + halfWidth), // 4 12
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth), // 5 13

		// latura spate
		glm::vec3(centerX - halfLength, centerY - halfHeight, centerZ + halfWidth), // 0 14
		glm::vec3(centerX + halfLength, centerY - halfHeight, centerZ - halfWidth), // 2 15
		glm::vec3(centerX - halfLength, centerY + halfHeight, centerZ + halfWidth), // 3 16
		glm::vec3(centerX + halfLength, centerY + halfHeight, centerZ - halfWidth)  // 5 17
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0)
	};

	// coordonatele de textura
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.01f, 0),
		glm::vec2(0, 0.01f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.01f, 0),
		glm::vec2(0, 0.01f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(length / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(length / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(width / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(width / dimPattern, height / dimPattern),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(std::sqrt(length * length + width * width) / dimPattern, 0),
		glm::vec2(0, height / dimPattern),
		glm::vec2(std::sqrt(length * length + width * width) / dimPattern, height / dimPattern)
	};

	// indicii
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,		7, 9, 8,
		10, 11, 12,		11, 13, 12,
		14, 15, 16,		15, 17, 16
	};


	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);

	return mesh;
}

// creeaza un cilindru cu numOfFaces fete
Mesh* GeoemtricObject::CreateCylinder(std::string name, glm::vec3 center, float length, float width, float height, int numOfFaces)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	float halfHeight = height / 2.0f;
	float halfLength = length / 2.0f;
	float halfWidth = width / 2.0f;

	float perimeter = 2 * M_PI * std::sqrt((length * length + width * width) / 2.0f);
	float dimPattern = 0.25f;

	vertices.push_back(glm::vec3(center.x, center.y + halfHeight, center.z));

	// baza de sus
	for (int i = 0; i < numOfFaces + 1; i++) {
		vertices.push_back(glm::vec3(center.x + halfLength * cos(i * 360 / (float)numOfFaces * M_PI / 180),
			center.y + halfHeight, center.z + halfWidth * sin(i * 360 / (float)numOfFaces * M_PI / 180)));
	}
	// fetele
	for (int i = 0; i < numOfFaces + 1; i++) {
		// partea de jos
		vertices.push_back(glm::vec3(center.x + halfLength * cos(i * 360 / (float)numOfFaces * M_PI / 180),
			center.y - halfHeight, center.z + halfWidth * sin(i * 360 / (float)numOfFaces * M_PI / 180)));
		i++;
		vertices.push_back(glm::vec3(center.x + halfLength * cos(i * 360 / (float)numOfFaces * M_PI / 180),
			center.y - halfHeight, center.z + halfWidth * sin(i * 360 / (float)numOfFaces * M_PI / 180)));
		--i;
		// partea de sus
		vertices.push_back(glm::vec3(center.x + halfLength * cos(i * 360 / (float)numOfFaces * M_PI / 180),
			center.y + halfHeight, center.z + halfWidth * sin(i * 360 / (float)numOfFaces * M_PI / 180)));
		i++;
		vertices.push_back(glm::vec3(center.x + halfLength * cos(i * 360 / (float)numOfFaces * M_PI / 180),
			center.y + halfHeight, center.z + halfWidth * sin(i * 360 / (float)numOfFaces * M_PI / 180)));
		--i;
	}

	std::vector<unsigned short> indices;

	// baza de sus
	for (int i = 0; i < numOfFaces; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}
	// fetele
	int k = numOfFaces + 2;
	for (int i = 0; i < numOfFaces; i++) {
		indices.push_back(k);
		indices.push_back(k + 1);
		indices.push_back(k + 2);

		indices.push_back(k + 1);
		indices.push_back(k + 3);
		indices.push_back(k + 2);

		k += 4;
	}

	for (int i = 0; i < vertices.size(); i++) {
		normals.push_back(glm::vec3(0, 1, 0));
	}

	textureCoords.push_back(glm::vec2(0.5f, 0.5f));

	for (int i = 0; i < numOfFaces + 1; i++) {
		textureCoords.push_back(glm::vec2(0.5f, 0.5f));
	}

	for (int i = 0; i < numOfFaces + 1; i++) {
		textureCoords.push_back(
			glm::vec2(i / (float)(numOfFaces + 1) * perimeter / (float)(numOfFaces * dimPattern), 0));
		textureCoords.push_back(
			glm::vec2((i + 1) / (float)(numOfFaces + 1) * perimeter / (float)(numOfFaces * dimPattern), 0));
		textureCoords.push_back(
			glm::vec2(i / (float)(numOfFaces + 1) * perimeter / (float)(numOfFaces * dimPattern), 
				height / (float)(dimPattern)));
		textureCoords.push_back(
			glm::vec2((i + 1) / (float)(numOfFaces + 1) * perimeter / (float)(numOfFaces * dimPattern), 
				height / (float)(dimPattern)));
	}

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);

	return mesh;
}