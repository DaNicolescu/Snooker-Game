#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// incarcare texturi

	// cladiri
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building.jpg").c_str(), GL_REPEAT);
		mapTextures["building1"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building.png").c_str(), GL_REPEAT);
		mapTextures["building2"] = texture;
	}
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "building2.png").c_str(), GL_REPEAT);
		mapTextures["building3"] = texture;
	}
	// gazon
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass.jpg").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}
	// drum
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "road.jpg").c_str(), GL_REPEAT);
		mapTextures["road"] = texture;
	}
	// intersectie
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "intersection.jpg").c_str(), GL_REPEAT);
		mapTextures["intersection"] = texture;
	}

	// shader
	{
		Shader *shader = new Shader("Shader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// creeaza harta de 50X50
	createMap(50);
	// genereaza drumuri
	createRoads();
	viewMap();
	// creeaza si asaza cladiri in scena
	createAndPlaceBuildings();
	viewMap();

	// doua patrate folosite pentru a randa gazonul, drumul si intersectiile
	this->roadTile = GeoemtricObject::CreateSquare("road", glm::vec3(0, 0.1f, 0), 1);
	this->grassTile = GeoemtricObject::CreateSquare("road", glm::vec3(0, 0.1f, 0), 1);
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

// creeaza harta
void Tema3::createMap(int size)
{
	this->mapSize = size;

	this->map = new int*[size];

	for (int i = 0; i < size; i++) {
		this->map[i] = new int[size]();
	}
}

// creeaza drumuri
void Tema3::createRoads()
{
	int maxDistance = 7;
	int distance = 0;

	srand(time(NULL));

	// generare drumuri pe linii
	for (int i = 1; i < this->mapSize - 1; i++) {
		// random, sau daca distanta intre doua drumuri e
		// mai mare decat maxDistance
		if (rand() % 100 < 10 || distance > maxDistance) {
			distance = 0;

			for (int j = 0; j < this->mapSize; j++) {
				this->map[i][j]++;
			}
		}
		distance++;
	}

	distance = 0;

	// genereare linii pe coloane
	for (int j = 1; j < this->mapSize - 1; j++) {
		if (rand() % 100 < 10 || distance > maxDistance) {
			distance = 0;

			for (int i = 0; i < this->mapSize; i++) {
				this->map[i][j]++;
			}
		}
		distance++;
	}
}

// randeaza gazonul folosind harta
void Tema3::renderGrass()
{
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			// daca nu se afla o bucata de drum, sau intersectie
			if (this->map[i][j] != 1 && this->map[i][j] != 2) {
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, 
					glm::vec3(-this->mapSize / 2.0f + i, 0, -this->mapSize / 2.0f + j));
				RenderSimpleMesh(this->grassTile, shaders["Shader"], modelMatrix, mapTextures["grass"]);
			}
		}
	}	
}

// randeaza drumul folosind harta
void Tema3::renderRoads()
{
	// randeaza drumurile pe linii si intersectiile
	for (int i = 1; i < this->mapSize - 1; i++) {
		if (this->map[i][0] == 1) {
			for (int j = 0; j < this->mapSize; j++) {
				// daca este o bucata de drum
				if (this->map[i][j] == 1) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, 
						glm::vec3(-this->mapSize / 2.0f + i, 0, -this->mapSize / 2.0f + j));
					RenderSimpleMesh(this->roadTile, shaders["Shader"], modelMatrix, mapTextures["road"]);
				}
				// daca este o bucata de intersectie
				else if (this->map[i][j] == 2) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, 
						glm::vec3(-this->mapSize / 2.0f + i, 0, -this->mapSize / 2.0f + j));
					RenderSimpleMesh(this->roadTile, shaders["Shader"], modelMatrix, mapTextures["intersection"]);
				}
			}
		}
	}

	// randeaza liniile pe coloane
	for (int j = 1; j < this->mapSize - 1; j++) {
		if (this->map[0][j] == 1) {
			for (int i = 0; i < this->mapSize; i++) {
				if (this->map[i][j] == 1) {
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, 
						glm::vec3(-this->mapSize / 2.0f + i, 0, -this->mapSize / 2.0f + j));
					// bucata de drum trebuie rotita la 90 de grade din cauza texturii
					modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
					RenderSimpleMesh(this->roadTile, shaders["Shader"], modelMatrix, mapTextures["road"]);
				}
			}
		}
	}

}

// creeaza o cladire random de dimensiuni length, width, height, pozitionata in center
Mesh* Tema3::createBuilding(glm::vec3 center, float length, float width, float height)
{
	int buildingType = rand() % 10;

	if (buildingType < 4) {
		// ultimul parametru este pentru numarul de fete
		return GeoemtricObject::CreateCylinder("building", center, length, width, height, 3 + rand() % 36);
	}
	else if (buildingType < 8) {
		return GeoemtricObject::CreateRectagularCuboid("building", center, length, height, width);
	}
	else {
		return GeoemtricObject::CreateTriangularPrism("building", center, length, height, width);
	}
}

// intoarce random o textura pentru cladiri
Texture2D* Tema3::chooseTexture()
{
	int textureType = rand() % 3;

	if (textureType == 0) {
		return this->mapTextures["building1"];
	}
	else if (textureType == 1) {
		return this->mapTextures["building2"];
	}
	else {
		return this->mapTextures["building3"];
	}
}

// creeaza si plaseaza cladiri in scena
void Tema3::createAndPlaceBuildings()
{
	Mesh* building = NULL;
	int i, j;
	int length, width, height;
	glm::vec3 center;

	srand(time(NULL));

	// generare pe drumurile de pe linii
	for (i = 1; i < this->mapSize - 1; i++) {
		j = 0;
		// daca se afla pe un drum
		if (this->map[i][j] == 1) {
			// generare cladiri aflate pe o singura parte a drumului
			while (j < this->mapSize - 1) {
				height = 5 + rand() % 6;
				center = glm::vec3(-this->mapSize / 2.0f, height / 2.0f, -this->mapSize / 2.0f);

				// verifica daca exista spatiu pentru o cladire de 2X2
				if (this->map[i - 1][j] == 0 && this->map[i - 1][j + 1] == 0 
					&& ((i > 1 && this->map[i - 2][j] == 0 && this->map[i - 2][j + 1] == 0) || i == 1)) {
					width = 2;
					length = 2;
					center.z += 0.5f;
					this->map[i - 1][j] = 3;
					this->map[i - 1][j + 1] = 3;
					if (i > 1) {
						this->map[i - 2][j] = 3;
						this->map[i - 2][j + 1] = 3;
					}
					// incearca random sa mareasca dimensiunile
					if (this->map[i - 1][j + 2] == 0 && rand() % 100 < 50 
						&& ((i > 1 && this->map[i - 2][j + 2] == 0) || i == 1)) {
						width++;
						center.z += 0.5f;
						this->map[i - 1][j + 2] = 3;

						if (i > 1) {
							this->map[i - 2][j + 2] = 3;
						}
						
						// incearca din nou
						if (this->map[i - 1][j + 3] == 0 && rand() % 100 < 30
							&& ((i > 1 && this->map[i - 2][j + 3] == 0) || i == 1)) {
							width++;
							center.z += 0.5f;
							this->map[i - 1][j + 3] = 3;

							if (i > 1) {
								this->map[i - 2][j + 3] = 3;
							}
						}
					}

					center.x += i - 1.5f;
					center.z += j;

					// creeaza cladirea
					building = createBuilding(center, length, width, height);

					// alege random o textura  pentru aceasta
					building->texture = chooseTexture();

					// o pune un lista de cladiri
					this->buildings.push_back(building);

					j += width;
				}
				else {
					j += 2;
				}
			}
			j = 0;
			// generare cladiri pe cealalta parte a drumului
			while (j < this->mapSize - 1) {
				height = 5 + rand() % 6;
				center = glm::vec3(-this->mapSize / 2.0f, height / 2.0f, -this->mapSize / 2.0f);

				if (this->map[i + 1][j] == 0 && this->map[i + 1][j + 1] == 0
					&& ((i < this->mapSize - 2 && this->map[i + 2][j] == 0 
						&& this->map[i + 2][j + 1] == 0) || i == this->mapSize - 1)) {
					width = 2;
					length = 2;
					center.z += 0.5f;
					this->map[i + 1][j] = 3;
					this->map[i + 1][j + 1] = 3;

					if (i < this->mapSize - 1) {
						this->map[i + 2][j] = 3;
						this->map[i + 2][j + 1] = 3;
					}

					if (this->map[i + 1][j + 2] == 0 && rand() % 100 < 50
						&& ((i < this->mapSize - 2 && this->map[i + 2][j + 2] == 0) || i == this->mapSize - 1)) {
						width++;
						center.z += 0.5f;
						this->map[i + 1][j + 2] = 3;

						if (i < this->mapSize - 1) {
							this->map[i + 2][j + 2] = 3;
						}

						if (this->map[i + 1][j + 3] == 0 && rand() % 100 < 30
							&& ((i < this->mapSize - 1 && this->map[i + 2][j + 3] == 0) || i == this->mapSize - 1)) {
							width++;
							center.z += 0.5f;
							this->map[i + 1][j + 3] = 3;

							if (i < this->mapSize - 1) {
								this->map[i + 2][j + 3] = 3;
							}
						}
					}

					center.x += i + 1.5f;
					center.z += j;

					building = createBuilding(center, length, width, height);

					building->texture = chooseTexture();

					this->buildings.push_back(building);

					j += width;
				}
				else {
					j += 2;
				}
			}
		}
	}

	// generare cladiri pe coloane
	for (j = 1; j < this->mapSize - 1; j++) {
		i = 0;
		if (this->map[i][j] == 1) {
			while (i < this->mapSize - 1) {
				height = 5 + rand() % 6;
				center = glm::vec3(-this->mapSize / 2.0f, height / 2.0f, -this->mapSize / 2.0f);

				if (i < this->mapSize - 1 && this->map[i][j - 1] == 0 && this->map[i + 1][j - 1] == 0
					&& ((j > 1 && this->map[i][j - 2] == 0 && this->map[i + 1][j - 2] == 0) || j == 1)) {
					width = 2;
					length = 2;
					center.x += 0.5f;
					this->map[i][j - 1] = 3;
					this->map[i + 1][j - 1] = 3;
					if (j > 1) {
						this->map[i][j - 2] = 3;
						this->map[i + 1][j - 2] = 3;
					}

					std::cout << "asd " << i + 2 << std::endl;

					if (i < this->mapSize - 2 && this->map[i + 2][j - 1] == 0 && rand() % 100 < 50
						&& ((j > 1 && this->map[i + 2][j - 2] == 0) || j == 1)) {
						length++;
						center.x += 0.5f;
						this->map[i + 2][j - 1] = 3;

						if (j > 1) {
							this->map[i + 2][j - 2] = 3;
						}

						if (i < this->mapSize - 3 && this->map[i + 3][j - 1] == 0 && rand() % 100 < 30
							&& ((j > 1 && this->map[i + 3][j - 2] == 0) || j == 1)) {
							length++;
							center.x += 0.5f;
							this->map[i + 3][j - 1] = 3;

							if (j > 1) {
								this->map[i + 3][j - 2] = 3;
							}
						}
					}

					center.x += i;
					center.z += j - 1.5f;

					building = createBuilding(center, length, width, height);

					building->texture = chooseTexture();

					this->buildings.push_back(building);

					i += length;
				}
				else {
					i += 2;
				}
			}
			i = 0;
			while (i < this->mapSize - 1) {
				height = 5 + rand() % 6;
				center = glm::vec3(-this->mapSize / 2.0f, height / 2.0f, -this->mapSize / 2.0f);

				if (i < this->mapSize - 1 && this->map[i][j + 1] == 0 && this->map[i + 1][j + 1] == 0
					&& ((j < this->mapSize - 1 && this->map[i][j + 2] == 0 
						&& this->map[i + 1][j + 2] == 0) || j == this->mapSize - 1)) {
					width = 2;
					length = 2;
					center.x += 0.5f;
					this->map[i][j + 1] = 3;
					this->map[i + 1][j + 1] = 3;

					if (j < this->mapSize - 1) {
						this->map[i][j + 2] = 3;
						this->map[i + 1][j + 2] = 3;
					}

					std::cout << i << std::endl;

					if (i < this->mapSize - 2 && this->map[i + 2][j + 1] == 0 && rand() % 100 < 50
						&& ((j < this->mapSize - 1 && this->map[i + 2][j + 2] == 0) || j == this->mapSize - 1)) {
						length++;
						center.x += 0.5f;
						this->map[i + 2][j + 1] = 3;

						if (j < this->mapSize - 1) {
							this->map[i + 2][j + 2] = 3;
						}

						if (i < this->mapSize - 3 && this->map[i + 3][j + 1] == 0 && rand() % 100 < 30
							&& ((j < this->mapSize - 1 && this->map[i + 3][j + 2] == 0) || j == this->mapSize - 1)) {
							length++;
							center.x += 0.5f;
							this->map[i + 3][j + 1] = 3;

							if (j < this->mapSize - 1) {
								this->map[i + 3][j + 2] = 3;
							}
						}
					}

					center.x += i;
					center.z += j + 1.5f;

					building = createBuilding(center, length, width, height);

					building->texture = chooseTexture();

					this->buildings.push_back(building);

					i += length;
				}
				else {
					i += 2;
				}
			}
		}
	}
}

// randeaza cladirile
void Tema3::renderBuildings()
{
	glm::mat4 modelMatrix = glm::mat4(1);

	for (auto& building : this->buildings) {
		RenderSimpleMesh(building, shaders["Shader"], modelMatrix, building->texture);
	}
}

// vizualizare harta
void Tema3::viewMap()
{
	for (int i = 0; i < this->mapSize; i++) {
		for (int j = 0; j < this->mapSize; j++) {
			cout << this->map[i][j] << " ";
		}

		cout << endl;
	}
}

void Tema3::Update(float deltaTimeSeconds)
{
	// randeaza drumurile
	renderRoads();
	// randeaza gazonul
	renderGrass();
	// randeaza cladirile
	renderBuildings();
}

void Tema3::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int loc_check = glGetUniformLocation(shader->program, "check");
	if (texture2 != NULL) {
		glUniform1i(loc_check, 1);
	}
	else {
		glUniform1i(loc_check, 0);
	}

	int time = glGetUniformLocation(shader->GetProgramID(), "time");
	double getTime = Engine::GetElapsedTime();
	glUniform1f(time, getTime);
	

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
