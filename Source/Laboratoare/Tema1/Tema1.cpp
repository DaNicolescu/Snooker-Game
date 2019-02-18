#include "Tema1.h"

#include <vector>
#include <iostream>
#include <fstream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

// Exista 2 power up-uri diferite
// Unul din ele pune un perete in partea de jos a scenei
// timp de 30 de secunde, iar celalalt face bila puternica
// (nu mai ricoseaza din caramizi)

// 20% sansa sa cada un power up la distrugerea unei caramizi

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	this->resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	
	// folosit pentru compararea valorilor float
	epsilon = 0.5f;

	// numar de vieti
	numOfLives = 3;

	// coordonate initiale platforma
	txPad = 0;
	tyPad = 30;
	// lungimea platformei
	padWidth = 150;

	// variabile pentru bila
	txBall = 0;
	tyBall = 90;
	ballMove = false;
	directionX = 1;
	directionY= 1;
	cosRadians = 0;
	
	// probabilitatea ca un power up sa apara 
	// la distrugerea unei caramizi
	powerUpChance = 20.0f;
	// numarul de power up-uri diferite
	powerUpTypes = 2;
	// vector in care este pastrat timpul ramas
	// pentru fiecare power up 
	powerUpTime = new float[powerUpTypes];

	// initializare timpi
	for (int i = 0; i < powerUpTypes; i++) {
		powerUpTime[i] = 0;
	}

	maxPowerUpTime = new float[powerUpTypes];

	maxPowerUpTime[0] = 15.0f;
	maxPowerUpTime[1] = 5.0f;

	// numarul de caramizi pe lungime
	xNumOfBricks = 10;
	// numarul de caramizi pe latime
	yNumOfBricks = 5;
	
	
	// creeaza peretii
	createWalls(resolution, 30);

	// creeaza peretele de jos
	// (folosit la power up)
	createBottomWall(30);

	// creeaza platforma
	createPad(padWidth, 10);

	// creeaza bila
	createBall(10);

	// creeaza vietile
	createLives(10);

	// creeaza caramizile
	createBricks();
}

// creeaza peretii
void Tema1::createWalls(glm::ivec2 resolution, float width) {
	glm::vec3 corner = glm::vec3(0, 75, 0);
	float height = resolution.y - corner.y;

	// perete stanga
	Mesh* leftWall = Object2D::CreateRectangle("leftWall", corner, width, height, glm::vec3(1, 0, 0), true);
	AddMeshToList(leftWall);

	// perete dreapta
	corner = glm::vec3(resolution.x - width, 75, 0);
	height = resolution.y - corner.y;
	Mesh* rightWall = Object2D::CreateRectangle("rightWall", corner, width, height, glm::vec3(1, 0, 0), true);
	AddMeshToList(rightWall);

	// tavan
	corner = glm::vec3(width, resolution.y - width, 0);
	height = width;
	width = resolution.x - 2 * width;
	Mesh* ceiling = Object2D::CreateRectangle("ceiling", corner, width, height, glm::vec3(1, 0, 0), true);
	AddMeshToList(ceiling);
}

// creeaza peretele de jos, folosit la power up
void Tema1::createBottomWall(float thickness) {
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float width = this->resolution.x;
	float height = thickness;

	Mesh* bottomWall = Object2D::CreateRectangle("bottomWall", corner, width, height, glm::vec3(1, 0, 0), true);
	AddMeshToList(bottomWall);
}

// creeaza platforma
void Tema1::createPad(float width, float height) {
	glm::vec3 corner = glm::vec3(-width / 2.0f, 30, 0);

	Mesh* pad = Object2D::CreateRectangle("pad", corner, width, height, glm::vec3(0, 1, 0), true);
	AddMeshToList(pad);
}

// creeaza bila
void Tema1::createBall(float radius) {
	Mesh* ball = Object2D::CreateCircle("ball", glm::vec3(0, 0, 0), radius, glm::vec3(1, 1, 1), true);
	AddMeshToList(ball);
}

// creeaza vietile
void Tema1::createLives(float radius) {
	Mesh* life;
	float x = resolution.x / 64.0f;
	float y = resolution.y / 18.0f;

	for (int i = 0; i < numOfLives; i++) {
		life = Object2D::CreateCircle("life" + std::to_string(i + 1), glm::vec3(x, y, 0), radius, glm::vec3(1, 1, 1), true);
		x = x + resolution.x / 43.0f;
		AddMeshToList(life);
	}
}

// creeaza caramizile
void Tema1::createBricks() {
	glm::vec3 corner;
	float x = resolution.x / (xNumOfBricks + 2.0f);
	float y = resolution.y / (yNumOfBricks + 2.0f);
	float width = resolution.x / 18.0f;
	float height = resolution.y / 28.0f;
	Brick* brick;
	Mesh* mesh;
	int i, j, k;
	k = 0;

	for (i = 1; i < xNumOfBricks + 1; i++) {
		for (j = 1; j < yNumOfBricks + 1; j++) {
			x = i  * resolution.x / (xNumOfBricks + 4.0f) + resolution.x / (xNumOfBricks + 2.0f);
			y = j * resolution.y / (yNumOfBricks + 8.0f) + 2 * resolution.y / (yNumOfBricks * 1.0f);

			corner = glm::vec3(x, y, 0);
			// creeaza mesh-ul
			mesh = Object2D::CreateRectangle("brick" + std::to_string(k), corner, width,
				height, glm::vec3(0, j / (yNumOfBricks * 1.0f), 0), true);
			// creeaza caramida
			brick = new Brick(mesh, k, 1.0f);
			k++;
			// adauga caramida la vectorul de caramizi
			bricks.push_back(brick);
		}
	}
}

// creeaza power up-urile
void Tema1::createPowerUp(Brick* brick) {
	PowerUp* powerUp;
	Mesh* mesh;
	int numOfBricks = xNumOfBricks * yNumOfBricks;
	float halfBrickWidth = brick->mesh->center.x - brick->mesh->bottomLeftCorner.x;
	float halfBrickHeight = brick->mesh->center.y - brick->mesh->bottomLeftCorner.y;
	float side = resolution.x / 85.3f;
	float halfSide = side / 2.0f;

	// creeaza mesh-ul
	mesh = Object2D::CreateSquare("powerUp" + std::to_string(brick->getIndex()),
		glm::vec3(
			brick->mesh->bottomLeftCorner.x + halfBrickWidth - halfSide, 
			brick->mesh->bottomLeftCorner.y + halfBrickHeight - halfSide, 
			0
		),
		15, glm::vec3(1, 0, 0), true);

	// creeaza power up-ul
	powerUp = new PowerUp(mesh, side);
	// adauga power up-ul la map
	powerUps[brick->getIndex()] = powerUp;
}

// verifica daca s-a produs vreo coliziune intre platforma si
// power up-uri si activeaza power up-ul in caz de coliziune
void Tema1::powerUpCollision(Mesh* pad, float deltaTimeSeconds) {
	float cxPad = pad->center.x / pad->center.z;
	float cyPad = pad->center.y / pad->center.z;
	float blxPad = pad->bottomLeftCorner.x / pad->bottomLeftCorner.z;
	float blyPad = pad->bottomLeftCorner.y / pad->bottomLeftCorner.z;
	glm::vec2 diff;
	float halfWidth, halfHeight;

	// deoarece patratul se roteste aproximez hit box-ul
	// cu un cerc de raza = side
	float cxPowerUp, cyPowerUp;

	halfWidth = cxPad - blxPad;
	halfHeight = cyPad - blyPad;

	srand(time(NULL));

	for (auto& powerUp : powerUps) {
		if (powerUp.second->isRemoved()) {
			continue;
		}
		cxPowerUp = powerUp.second->mesh->center.x / powerUp.second->mesh->center.z;
		cyPowerUp = powerUp.second->mesh->center.y / powerUp.second->mesh->center.z;

		// detectare coliziune
		if (collision(powerUp.second->mesh, cxPowerUp, cyPowerUp, pad, deltaTimeSeconds, false)) {
			// pornire power up
			resetPowerUpTime(rand() % powerUpTypes);
			powerUp.second->remove();
		}
	}
}

// detecteaza coliziunile dintre bila si celelalte elemente de pe
// ecran, schimba traiectoria mingii si distruge caramizile
void Tema1::ballCollision(Mesh* ball, float deltaTimeSeconds) {
	float cxBall = ball->center.x / ball->center.z;
	float cyBall = ball->center.y / ball->center.z;
	srand(time(NULL));

	for (auto &obj : meshes) {
		if (obj.second == ball 
			|| !obj.first.compare(0, 7, "powerUp")
			|| ((powerUpTime[0] <= 0) && !obj.first.compare(0, 10, "bottomWall"))) {
			continue;
		}

		if (collision(ball, cxBall, cyBall, obj.second, deltaTimeSeconds, true)) {
			return;
		}
	}

	for (auto &brick : bricks) {
		if (brick->isRemoved()) {
			continue;
		} else if (collision(ball, cxBall, cyBall, brick->mesh, deltaTimeSeconds, true)) {
			// daca s-a produs o coliziune cu o caramida, aceasta este distrusa,
			// si se poate crea, sau nu, un power up
			if (rand() % 100 < powerUpChance) {
				createPowerUp(brick);
			}
			brick->remove();
			return;
		}
	}
}

// Functie care detecteaza coliziuniea dintre un obiect ball, ce are drept hitbox un cerc
// si un obiect obj, ce are drept hitbox un dreptunghi.
// Daca reflect este true, atunci collision modifica traiectoria lui ball
bool Tema1::collision(Mesh* ball, float cxBall, float cyBall, Mesh* obj, float deltaTimeSeconds, bool reflect) {
	float cxObj, cyObj;
	float blxObj, blyObj;
	float halfWidth, halfHeight;
	float closestX, closestY;
	glm::vec2 diff;

	// obtinere coordonate carteziene pentru centru
	cxObj = obj->center.x / obj->center.z;
	cyObj = obj->center.y / obj->center.z;

	// obtinere coordonate carteziene pentru bottom left corner
	blxObj = obj->bottomLeftCorner.x / obj->bottomLeftCorner.z;
	blyObj = obj->bottomLeftCorner.y / obj->bottomLeftCorner.z;

	halfWidth = cxObj - blxObj;
	halfHeight = cyObj - blyObj;

	// vector distanta intre centrele celor doua obiecte
	diff = glm::vec2(cxBall, cyBall) - glm::vec2(cxObj, cyObj);

	// determina posibilul punct de coliziune incadrand vectorul intre
	// dimensiunile obiectului obj
	closestX = std::max(-halfWidth, std::min(halfWidth, diff.x));;
	closestY = std::max(-halfHeight, std::min(halfHeight, diff.y));;

	closestX += cxObj;
	closestY += cyObj;

	// calculeaza distanta de la centrul bilei la punctul de 
	// coliziune
	diff = glm::vec2(closestX, closestY) - glm::vec2(cxBall, cyBall);

	// daca distanta este mai mica decat raza bilei, 
	// atunci s-a produs o coliziune
	if (glm::length(diff) <= ball->radius) {
		if (!reflect) {
			return true;
		}

		// determinarea tipului de coliziune
		// si schimbarea traiectoriei
		if (!obj->meshID.compare("pad")) {
			cosRadians = (closestX - cxObj) / halfWidth;
			
			if (cosRadians < 0) {
				directionX = -1;
				cosRadians *= -1;
			}
			else {
				directionX = 1;
			}
			directionY = 1;
		}
		else if (strongBall && !obj->meshID.compare(0, 5, "brick")) {
			return true;
		}
		else if (abs(closestY - (blyObj + 2 * halfHeight)) < epsilon) {
			directionY = 1;
		}
		else if (abs(closestX - blxObj) < epsilon) {
			directionX = -1;
		}
		else if (abs(closestY - blyObj) < epsilon) {
			directionY = -1;
		}
		else if (abs(closestX - (blxObj + 2 * halfWidth)) < epsilon) {
			directionX = 1;
		}

		return true;
	}

	return false;
}

// reseteaza timpul pentru care power up-ul
// cu indicele idx este activ
void Tema1::resetPowerUpTime(int idx) {
	this->powerUpTime[idx] = this->maxPowerUpTime[idx];
}
 
void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	int k;
	PowerUp* powerUp;

	k = 0;

	// resetare centre
	modelMatrix = glm::mat3(1);
	meshes["ball"]->center = glm::vec3(0, 0, 1);
	meshes["pad"]->center = glm::vec3(0, 40, 1);
	meshes["pad"]->bottomLeftCorner = glm::vec3(-padWidth / 2.0f, 40, 1);

	// render pereti
	RenderMesh2D(meshes["leftWall"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["rightWall"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["ceiling"], shaders["VertexColor"], modelMatrix);

	// randare perete de jos daca power up-ul este activ
	if (powerUpTime[0] > 0) {
		RenderMesh2D(meshes["bottomWall"], shaders["VertexColor"], modelMatrix);

		powerUpTime[0] -= deltaTimeSeconds;
	}

	if (powerUpTime[1] > 0) {
		strongBall = true;

		powerUpTime[1] -= deltaTimeSeconds;
	}
	else {
		strongBall = false;
	}

	// render vieti
	for (int i = numOfLives; i > 0; i--) {
		RenderMesh2D(meshes["life" + std::to_string(i)], shaders["VertexColor"], modelMatrix);
	}

	for (auto& brick : bricks) {
		modelMatrix = glm::mat3(1);
		if (brick->isRemoved() && brick->isScaled()) {
			// scaleaza caramida daca aceasta a fst distrusa
			modelMatrix *= Transform2D::Translate(brick->mesh->center.x, brick->mesh->center.y);
			modelMatrix *= Transform2D::Scale(brick->getDisplayTime(), brick->getDisplayTime());
			modelMatrix *= Transform2D::Translate(-brick->mesh->center.x, -brick->mesh->center.y);

			brick->decreaseDisplayTime(3 * deltaTimeSeconds);

			if (brick->getDisplayTime() < 0) {
				brick->stopScale();
			}
		} else if (brick->isRemoved()) {
			// render power up
			if (powerUps.count(brick->getIndex()) > 0) {
				powerUp = powerUps[brick->getIndex()];

				if (!powerUp->isRemoved()) {
					powerUp->mesh->center = brick->mesh->center;

					// roteste si translateaza power up-ul
					modelMatrix *= Transform2D::Translate(0, powerUp->getTranslateY());
					modelMatrix *= Transform2D::Translate(powerUp->mesh->center.x, powerUp->mesh->center.y);
					modelMatrix *= Transform2D::Rotate(powerUp->getAngularStep());
					modelMatrix *= Transform2D::Translate(-powerUp->mesh->center.x, -powerUp->mesh->center.y);

					powerUp->incAngularStep(8 * deltaTimeSeconds);
					powerUp->incTranslateY(-300 * deltaTimeSeconds);

					// render power up
					RenderMesh2D(powerUp->mesh, shaders["VertexColor"], modelMatrix);

					if (powerUp->mesh->center.y < 0) {
						powerUp->remove();
						powerUps.erase(brick->getIndex());
					}
				}
			}

			continue;
		}
		// render caramida
		RenderMesh2D(brick->mesh, shaders["VertexColor"], modelMatrix);
	}

	// render platforma
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(txPad, tyPad);
	RenderMesh2D(meshes["pad"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);

	// verifica daca exista coliziuni intre platforma si power up-uri
	powerUpCollision(meshes["pad"], deltaTimeSeconds);
	
	// daca bila se misca
	if (ballMove) {
		// render bila
		modelMatrix *= Transform2D::Translate(txBall, tyBall);
		RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);

		// verifica daca exista coliziuni intre bila si celelalte elemente
		ballCollision(meshes["ball"], deltaTimeSeconds);

		txBall += directionX * 500 * cosRadians * deltaTimeSeconds;
		tyBall += directionY * 500 * deltaTimeSeconds;

		// gestiune vieti
		if (meshes["ball"]->center.y < 0 
			|| meshes["ball"]->center.x < 0
			|| meshes["ball"]->center.x > this->resolution.x) {
			tyBall = 90;
			cosRadians = 0;
			--numOfLives;

			if (numOfLives == 0) {
				exit(0);
			}

			ballMove = false;
		}
	}
	// daca bila este atasata de platforma
	else {
		txBall = txPad;
		modelMatrix *= Transform2D::Translate(txBall, tyBall);
		RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	txPad = mouseX;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// button to release the ball
	if (button == GLFW_MOUSE_BUTTON_2) {
		ballMove = true;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
