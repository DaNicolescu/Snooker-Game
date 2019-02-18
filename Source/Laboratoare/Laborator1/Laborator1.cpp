#include "Laborator1.h"

#include <vector>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
	this->idx = 0;
	this->idxc = 0;
	this->size = 3;
	this->objs = new std::string[this->size];

	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 1;

	this->colors[0] = 1;
	this->colors[1] = 0;
	this->colors[2] = 0;
	this->colors[3] = 0;
	this->colors[4] = 1;
	this->colors[5] = 0;
	this->colors[6] = 0;
	this->colors[7] = 0;
	this->colors[8] = 1;

	this->x = 0;
	this->y = 1.95f;
	this->z = 0;
}

Laborator1::~Laborator1()
{
	delete[] this->objs;
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
		this->objs[0] = "box";

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
		this->objs[1] = "teapot";

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;
		this->objs[2] = "sphere";
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(this->colors[idxc], this->colors[idxc + 1], this->colors[idxc + 2], this->a);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(0, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["box"], glm::vec3(0, 1.1f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["box"], glm::vec3(0, 1.7f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["teapot"], glm::vec3(this->x , this->y, this->z), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["teapot"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// RenderMesh(meshes["box"], glm::vec3(0, 0, 0), glm::vec3(0.5f));
	RenderMesh(meshes[this->objs[this->idx]], glm::vec3(2, 0.5f, 0), glm::vec3(0.5f));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		this->z -= 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		this->z += 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		this->x -= 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		this->x += 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_Q)) {
		this->y -= 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_E)) {
		this->y += 2 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_R)) {
		// *this->rr * cos(this->alpha * std::PI / 180);
		this->alpha = (this->alpha + 1) % 360;
		this->x += deltaTime * cos(this->alpha * 3.14f / 180);
		this->y += deltaTime * sin(this->alpha * 3.14f / 180);
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_ESCAPE) {
		exit(1);
	}
	// add key press event
	if (key == GLFW_KEY_F) {
		idx = (idx + 1) % 3;
	}

	if (key == GLFW_KEY_M) {
		idxc = (idxc + 3) % 9;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
