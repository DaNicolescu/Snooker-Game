#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

// renders the floor and the walls
void Tema2::RenderWalls() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::RotateOX(0.78f);
	modelMatrix *= glm::scale(modelMatrix, glm::vec3(8, 6, 0.1f));
	RenderObject::RenderWall(poolGameCamera, meshes["wall"], shaders["Wall"], modelMatrix, mapTextures["floor"]);

	modelMatrix = glm::mat4(1);

	modelMatrix *= glm::translate(modelMatrix, glm::vec3(-2, 1, 1));
	modelMatrix *= Transform3D::RotateOY(-0.78f);
	modelMatrix *= glm::scale(modelMatrix, glm::vec3(8, 6, 0.1f));
	RenderObject::RenderWall(poolGameCamera, meshes["wall"], shaders["Wall"], modelMatrix, mapTextures["bricks"]);

	modelMatrix = glm::mat4(1);

	modelMatrix *= glm::translate(modelMatrix, glm::vec3(2, 1, -1));
	modelMatrix *= Transform3D::RotateOY(-0.78f);
	modelMatrix *= glm::scale(modelMatrix, glm::vec3(8, 6, 0.1f));
	RenderObject::RenderWall(poolGameCamera, meshes["wall"], shaders["Wall"], modelMatrix, mapTextures["bricks"]);

	modelMatrix = glm::mat4(1);

	modelMatrix *= glm::translate(modelMatrix, glm::vec3(0, 1, -1.5f));
	modelMatrix *= glm::scale(modelMatrix, glm::vec3(8, 6, 0.1f));
	RenderObject::RenderWall(poolGameCamera, meshes["wall"], shaders["Wall"], modelMatrix, mapTextures["bricks"]);

	modelMatrix = glm::mat4(1);

	modelMatrix *= glm::translate(modelMatrix, glm::vec3(0, 1, 1.5f));
	modelMatrix *= glm::scale(modelMatrix, glm::vec3(8, 6, 0.1f));
	RenderObject::RenderWall(poolGameCamera, meshes["wall"], shaders["Wall"], modelMatrix, mapTextures["bricks"]);
}

// renders the pool table
void Tema2::renderPoolTable() {
	modelMatrix = glm::mat4(1);

	RenderObject::RenderMesh(poolGameCamera, meshes["table"], shaders["VertexColor"], modelMatrix);
	RenderObject::RenderMesh(poolGameCamera, meshes["side1"], shaders["VertexColor"], modelMatrix);
	RenderObject::RenderMesh(poolGameCamera, meshes["side2"], shaders["VertexColor"], modelMatrix);
	RenderObject::RenderMesh(poolGameCamera, meshes["side3"], shaders["VertexColor"], modelMatrix);
	RenderObject::RenderMesh(poolGameCamera, meshes["side4"], shaders["VertexColor"], modelMatrix);

	for (int i = 0; i < 16; i++) {
		RenderObject::RenderMesh(poolGameCamera, meshes["pocket" + std::to_string(i + 1)], 
			shaders["VertexColor"], modelMatrix);
	}
}

// creates 16 Ball objects
void Tema2::initialiseBalls() {
	ballRadius = 0.02625;
	epsilon = ballRadius / 20.0;

	glm::vec3 whiteColor = glm::vec3(1, 1, 0.875);
	std::string white = "white";
	glm::vec3 blackColor = glm::vec3(0, 0, 0);
	std::string black = "black";
	glm::vec3 redColor = glm::vec3(0.72, 0, 0);
	std::string red = "red";
	glm::vec3 yellowColor = glm::vec3(0.972, 0.648, 0.0078);
	std::string yellow = "yellow";

	// white ball
	this->balls.push_back(new Ball(glm::vec3(tableLength / 6.0, tableHeigth + ballRadius, 0),
		ballRadius, whiteColor, white));

	// first row
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0, tableHeigth + ballRadius, 0),
		ballRadius, redColor, red));

	// sescond row
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 2 * ballRadius, tableHeigth + ballRadius,
		11 * ballRadius / 10.0), ballRadius, yellowColor, yellow));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 2 * ballRadius, tableHeigth + ballRadius,
		-11 * ballRadius / 10.0), ballRadius, redColor, red));

	// third row
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 4 * ballRadius, tableHeigth + ballRadius,
		21 * ballRadius / 10.0), ballRadius, redColor, red));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 4 * ballRadius, tableHeigth + ballRadius, 0),
		ballRadius, blackColor, black));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 4 * ballRadius, tableHeigth + ballRadius,
		-21 * ballRadius / 10.0), ballRadius, yellowColor, yellow));

	// fourth row
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 6 * ballRadius, tableHeigth + ballRadius,
		32 * ballRadius / 10.0), ballRadius, yellowColor, yellow));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 6 * ballRadius, tableHeigth + ballRadius,
		11 * ballRadius / 10.0), ballRadius, redColor, red));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 6 * ballRadius, tableHeigth + ballRadius,
		-11 * ballRadius / 10.0), ballRadius, redColor, red));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 6 * ballRadius, tableHeigth + ballRadius,
		-32 * ballRadius / 10.0), ballRadius, yellowColor, yellow));

	// fifth row
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 8 * ballRadius, tableHeigth + ballRadius,
		42 * ballRadius / 10.0), ballRadius, redColor, red));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 8 * ballRadius, tableHeigth + ballRadius,
		21 * ballRadius / 10.0), ballRadius, yellowColor, yellow));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 8 * ballRadius, tableHeigth + ballRadius, 0),
		ballRadius, yellowColor, yellow));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 8 * ballRadius, tableHeigth + ballRadius,
		-21 * ballRadius / 10.0), ballRadius, redColor, red));
	this->balls.push_back(new Ball(glm::vec3(-tableLength / 6.0 - 8 * ballRadius, tableHeigth + ballRadius,
		-42 * ballRadius / 10.0), ballRadius, yellowColor, yellow));
}

// renders the balls
void Tema2::RenderBalls() {
	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(ball->center.x, ball->center.y, ball->center.z);
		modelMatrix *= Transform3D::Scale(2 * ball->radius, 2 * ball->radius, 2 * ball->radius);
		RenderObject::RenderBall(poolGameCamera, meshes["ball"], shaders["BallShader"], modelMatrix, ball->color);
	}
}

// positions and rotates the cue based on the camera position
void Tema2::positionAndRenderCue(float animationDistance) {
	glm::vec3 cameraPosition = poolGameCamera->getCameraPosition();
	Ball* whiteBall = this->balls.at(0);

	cueModelMatrix = glm::mat4(1);
	// translates the cue to point twoards the white ball
	cueModelMatrix *= Transform3D::Translate(whiteBall->center.x, 0, whiteBall->center.z);
	// rotates the cue with the angle generated by the camera rotation
	cueModelMatrix *= Transform3D::RotateOY(rotateCueAngularStep);
	// initial translate
	cueModelMatrix *= Transform3D::Translate(cueLength / 2.0 + ballRadius, 0, 0);

	RenderObject::renderCue(poolGameCamera, meshes["cue"], shaders["CueShader"], cueModelMatrix, glm::vec3(0.4, 0.2, 0), 
		animationDistance, doCueAnimation);
}

// rails collisions for a single ball
void Tema2::railsCollision(Ball* ball, float deltaTime) {
	if (ball->center.x - deltaTime / 2.0 - (-tableLength / 2.0 + sideHeight + ball->radius) < epsilon) {
		ball->moveVector.x *= -1;
	}
	else if (tableLength / 2.0 - sideHeight - ball->radius - (ball->center.x + deltaTime / 2.0) < epsilon) {
		ball->moveVector.x *= -1;
	}
	else if (tableWidth / 2.0 - sideHeight - ball->radius - (ball->center.z + deltaTime / 2.0) < epsilon
		|| ball->center.z - deltaTime / 2.0 - (-tableWidth / 2.0 + sideHeight + ball->radius) < epsilon) {
		ball->moveVector.z *= -1;
	}
}

// rails collisions for all balls
void Tema2::allRailsCollisions(float deltaTime) {
	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}
		railsCollision(ball, deltaTime);
	}
}

// detects the collision between two balls and modifies their
// movement done in a frame so as to just touch each other
bool Tema2::detectBallCollision(Ball* ball1, Ball* ball2) {
	// move vector
	glm::vec3 moveVec = ball1->frameMove - ball2->frameMove;

	// Early Escape test: if the length of the movevec is less
	// than distance between the centers of these circles minus 
	// their radii, there's no way they can hit. 
	double distance = glm::distance(ball1->center, ball2->center);
	double origDist = distance;

	distance -= ball1->radius;
	distance -= ball2->radius;

	if (glm::length(moveVec) < distance) {
		return false;
	}

	// Normalize the movevec
	glm::vec3 n = glm::normalize(moveVec);

	// Find C, the vector from the center of the moving
	// circle A to the center of B
	glm::vec3 c = ball2->center - ball1->center;

	// D = N . C = ||C|| * cos(angle between N and C)
	float d = glm::dot(n, c);

	// Another early escape: Make sure that A is moving
	// towards B! If the dot product between the movevec and
	// B . center - A . center is less that or equal to 0,
	// A isn't isn't moving towards B
	if (d <= 0) {
		return false;
	}

	// Find the length of the vector C
	float lengthC = glm::length(c);

	float f = (lengthC * lengthC) - (d * d);

	// Escape test: if the closest that A will get to B
	// is more than the sum of their radii, there's no
	// way they are going collide

	float sumRadii = ball1->radius + ball2->radius;
	float sumRadiiSquared = sumRadii * sumRadii;

	if (f >= sumRadiiSquared) {
		return false;
	}

	// We now have F and sumRadii, two sides of a right triangle.
	// Use these to find the third side, sqrt(T)
	float t = sumRadiiSquared - f;

	// If there is no such right triangle with sides length of
	// sumRadii and sqrt(f), T will probably be less than 0.
	// Better to check now than perform a square root of a
	// negative number.
	if (t < 0) {
		return false;
	}

	// Therefore the distance the circle has to travel along
	// movevec is D - sqrt(T)
	distance = d - glm::sqrt(t);

	// Get the magnitude of the movement vector
	float mag = glm::length(moveVec);

	// Finally, make sure that the distance A has to move
	// to touch B is not greater than the magnitude of the
	// movement vector.
	if (mag < distance) {
		return false;
	}

	// Set the length of the movevec so that the circles will just
	// touch
	moveVec = glm::normalize(moveVec);
	moveVec *= distance;

	double newDist = glm::length(moveVec);

	float percent = newDist / origDist;

	ball1->frameMove *= percent;
	ball2->frameMove *= percent;

	return true;
}

// changes the speed vectors of the balls based on how they
// collided
void Tema2::bounceBalls(Ball* ball1, Ball* ball2) {
	// First, find the normalized vector n from the center of 
	// circle1 to the center of circle2
	glm::vec3 n = ball1->center - ball2->center;
	n = glm::normalize(n);

	// Find the length of the component of each of the movement
	// vectors along n. 
	// a1 = v1 . n
	// a2 = v2 . n
	float a1 = glm::dot(ball1->moveVector, n);
	float a2 = glm::dot(ball2->moveVector, n);

	// Using the optimized version, 
	// optimizedP =  2(a1 - a2)
	//              -----------
	//                m1 + m2
	float optimizedP = a1 - a2;

	// Calculate v1', the new movement vector of circle1
	// v1' = v1 - optimizedP * m2 * n
	glm::vec3 newV1 = ball1->moveVector - optimizedP * n;

	// Calculate v1', the new movement vector of circle1
	// v2' = v2 + optimizedP * m1 * n
	glm::vec3 newV2 = ball2->moveVector + optimizedP * n;

	// circle1.setMovementVector(v1');
	ball1->moveVector = newV1;

	// circle2.setMovementVector(v2');
	ball2->moveVector = newV2;
}

// checks collision between all balls
// if two balls collide, their speed vectors change
void Tema2::detectCollisionsAndBounce() {
	for (int i = 0; i < this->balls.size(); i++) {
		Ball* ball1 = this->balls.at(i);

		// if it's in a pocket, ignore it
		if (this->balls.at(i)->inPocket) {
			continue;
		}

		for (int j = i + 1; j < this->balls.size(); j++) {
			Ball* ball2 = this->balls.at(j);

			if (this->balls.at(j)->inPocket) {
				continue;
			}

			// if it detects collision between the balls
			if (detectBallCollision(ball1, ball2)) {
				// tries to determine if the first collision between the white ball
				// and another ball constitutes a fault
				if (crtPlayer->color.compare("noColor") && !firstBallTouch) {
					if (!ball1->colorName.compare("white")) {
						if ((!ball2->colorName.compare("black") && !crtPlayer->canHitBlackBall)
							|| (ball2->colorName.compare("black") && ball2->colorName.compare(crtPlayer->color))) {
							fault = true;
						}
						firstBallTouch = true;
					}
					else if (!ball2->colorName.compare("white")) {
						if ((!ball1->colorName.compare("black") && !crtPlayer->canHitBlackBall)
							|| (ball1->colorName.compare("black") && ball1->colorName.compare(crtPlayer->color))) {
							fault = true;
						}
						firstBallTouch = true;
					}
				}

				// updates the ball center using the movement done in a single frame
				ball2->center.x += ball2->frameMove.x;
				ball2->center.z += ball2->frameMove.z;

				// calculates their new moveVector (speed vector)
				ball2->moveVector.x = ball2->moveVector.x - ball2->frameMove.x;
				ball2->moveVector.z = ball2->moveVector.z - ball2->frameMove.z;

				// changes their speed vectors
				bounceBalls(ball1, ball2);
			}
		}

		ball1->center.x += ball1->frameMove.x;
		ball1->center.z += ball1->frameMove.z;

		ball1->moveVector.x = ball1->moveVector.x - ball1->frameMove.x;
		ball1->moveVector.z = ball1->moveVector.z - ball1->frameMove.z;
	}
}

// determines the movement done in a frame for each ball, 
// before any collisions
void Tema2::setFrameMove(float deltaTimeSeconds) {
	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}
		ball->frameMove.x = deltaTimeSeconds / 2.0 * ball->moveVector.x;
		ball->frameMove.z = deltaTimeSeconds / 2.0 * ball->moveVector.z;
	}
}

// checks if the balls have stopped
bool Tema2::ballsStopped() {
	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}
		if (glm::length(ball->moveVector) >= ball->radius / 2.0) {
			return false;
		}
	}

	return true;
}

// checks if the current player can put the black
// ball in the pocket
void Tema2::checkIfCanHitBlackBall() {
	bool crtPlayerBalls = false;

	if (!crtPlayer->color.compare("noColor")) {
		return;
	}

	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}
		if (!ball->colorName.compare(crtPlayer->color)) {
			crtPlayerBalls = true;
		}
	}

	if (!crtPlayerBalls) {
		crtPlayer->canHitBlackBall = true;
	}
}

// checks if the current player has won
void Tema2::checkIfWon() {
	if (crtPlayer->won) {
		if (crtPlayer == player1) {
			std::cout << "Player1 won" << std::endl;
		}
		else {
			std::cout << "Player2 won" << std::endl;
		}

		exit(0);
	}
}

// checks if the balls entered the pockets
// and also modifies the score
void Tema2::checkPockets() {
	for (auto& ball : this->balls) {
		if (ball->inPocket) {
			continue;
		}

		for (auto& pocket : this->pockets) {
			// if the ball is the pocket
			if (glm::length(pocket->center - ball->center) <= pocket->radius) {
				// if the current player has no color assigned
				if (!crtPlayer->color.compare("noColor") && ball->colorName.compare("white")
					&& ball->colorName.compare("black")) {
					crtPlayer->color = ball->colorName;

					if (crtPlayer == player1) {
						if (!ball->colorName.compare("red")) {
							player2->color = "yellow";
						}
						else {
							player2->color = "red";
						}
					}
					else {
						if (!ball->colorName.compare("red")) {
							player1->color = "yellow";
						}
						else {
							player1->color = "red";
						}
					}

					anyBallInPocket = true;
					crtPlayer->numOfBallsPutInPocket++;
				}
				// if the ball is black and can hit it, then te current player won
				else if (crtPlayer->canHitBlackBall && !ball->colorName.compare("black") && !fault) {
					crtPlayer->won = true;
					crtPlayer->numOfBallsPutInPocket++;
				}
				// if it's a colored ball, then increase the current player's score
				else if (!crtPlayer->color.compare(ball->colorName) && !fault) {
					crtPlayer->numOfBallsPutInPocket++;
					anyBallInPocket = true;
				}

				ball->inPocket = true;
			}
		}
	}
}

// resets the white ball so as the current player
// can position it using WASD
void Tema2::resetWhiteBall() {
	Ball* whiteBall = this->balls.at(0);

	poolGameCamera->positionWhiteBall();
	whiteBall->center = whiteBall->initialCenter;
	whiteBall->inPocket = false;
	whiteBall->moveVector = glm::vec3(0, 0, 0);
	rotateCueAngularStep = 0;
	moveWhiteBall = true;

	// changes turns
	crtPlayer->numOfFaults++;
	changeCrtPlayer();
}

// "hits the white ball with the cue"
void Tema2::takeShot() {
	Ball* ball = this->balls.at(0);
	glm::vec4 translate;

	translate.x = -ball->speed * 3 * tableLength / (2 * 0.15);
	translate.y = 0;
	translate.z = 0;
	translate.w = 1;
	translate = Transform3D::RotateOY(rotateCueAngularStep) * translate;
	ball->moveVector = translate;

	shot = true;
}

// changes the camera to third person and enables
// the rendering of the cue
void Tema2::prepareShot() {
	Ball* whiteBall = this->balls.at(0);

	trackWhiteBall = true;
	whiteBall->moveVector = glm::vec3(0, 0, 0);

	poolGameCamera->trackWhiteBall(whiteBall);
	poolGameCamera->RotateThirdPerson_OY(rotateCueAngularStep);
}

// changes the current player
void Tema2::changeCrtPlayer() {
	playerTurn = 1 - playerTurn;
	if (playerTurn == 0) {
		crtPlayer = player1;
	}
	else {
		crtPlayer = player2;
	}

	fault = false;
}

// shows statistics about the game
void Tema2::showStats() {
	std::cout << std::endl;

	std::cout << "-----" << std::endl;
	std::cout << "STATS" << std::endl;
	std::cout << "-----" << std::endl;
	std::cout << std::endl;

	std::cout << "Current player is ";
	if (playerTurn == 0) {
		std::cout << "Player1" << std::endl;
	}
	else {
		std::cout << "Player2" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Player1: " << std::endl;
	std::cout << "Color: ";
	std::cout << player1->color << std::endl;
	std::cout << "Number of balls put in pockets by him: ";
	std::cout << player1->numOfBallsPutInPocket << std::endl;
	std::cout << "Number of faults: ";
	std::cout << player1->numOfFaults << std::endl;

	std::cout << "Player2: " << std::endl;
	std::cout << "Color: ";
	std::cout << player2->color << std::endl;
	std::cout << "Number of balls put in pockets by him: ";
	std::cout << player2->numOfBallsPutInPocket << std::endl;
	std::cout << "Number of faults: ";
	std::cout << player2->numOfFaults << std::endl;
}

void Tema2::Init()
{
	polygonMode = GL_FILL;
	poolGameCamera = new Tema2Camera(GetSceneCamera()->GetProjectionMatrix());

	tableLength = 2.75;
	tableHeigth = 0.7;
	tableWidth = 1.5;

	sideLength = tableLength;
	sideHeight = 0.1;
	sideWidth = 0.1;

	pocketRadius = 0.07;

	cueLength = tableLength / 2.0;
	cueWidth = 0.01;
	cueHeight = 0.01;

	// creates the walls and floor
	CreateObject::CreateWallsAndFloor(meshes, shaders, mapTextures);

	moveWhiteBall = true;
	trackWhiteBall = false;
	ballPower = 0;
	releaseWhiteBall = false;
	showCue = true;
	shot = false;

	doCueAnimation = 0;
	rotateCueAngularStep = 0;
	cueAnimationDistance = 0;

	// creates the pool table and the balls
	CreateObject::createBallShader(shaders);
	CreateObject::createBallMesh(meshes);

	CreateObject::createPoolTable(meshes, pockets, tableLength, tableHeigth, tableWidth, 
		sideLength, sideHeight, sideWidth, pocketRadius);

	initialiseBalls();

	// creates the cue
	CreateObject::createCueShader(shaders);
	CreateObject::createCue(meshes, tableLength, tableHeigth, cueLength, cueWidth, cueHeight, ballRadius);

	// creates the players
	player1 = new Player;
	player2 = new Player;
	// 0 for player 1, 1 for player 2
	playerTurn = 0;
	crtPlayer = player1;

	fault = false;

	showStats();
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// renders the walls, the pool table and the balls
	RenderWalls();
	renderPoolTable();
	RenderBalls();

	// if it's tracking the white ball
	if (trackWhiteBall) {
		// renders the cue and chnges the power the cue
		// can produce
		positionAndRenderCue(cueAnimationDistance);
		cueAnimationDistance += 2 * deltaTimeSeconds;
		ballPower = (1 - cos(cueAnimationDistance)) / 13.33f;
	}

	// if the left mouse button has been released
	if (releaseWhiteBall) {
		// if the shot hasn't taken place
		if (!shot) {
			// if the cue animation hasn't been completed
			if (ballPower >= 0.01) {
				positionAndRenderCue(cueAnimationDistance);
				cueAnimationDistance += 10 * deltaTimeSeconds;
				ballPower = (1 - cos(cueAnimationDistance)) / 13.33f;
			}
			// else execute the shot
			else {
				firstBallTouch = false;
				anyBallInPocket = false;

				doCueAnimation = 0;
				poolGameCamera->viewShot();

				takeShot();
			}

		}
	}

	// checks rails collisions
	allRailsCollisions(deltaTimeSeconds);

	// calculates the movement done in a frame 
	// before any collisions take place
	setFrameMove(deltaTimeSeconds);
	// detects collisions, modifies the movement done
	// in the current frame, but also modifies the speed
	// vectors
	detectCollisionsAndBounce();

	// checks for balls put in pockets
	checkPockets();

	// checks if the current player can put the black
	// ball in the pocket
	checkIfCanHitBlackBall();

	// checks if the current player has won
	checkIfWon();

	// if the white ball is in the pocket, or
	// another fault has been commited
	// it waits for the balls to stop, then resets
	// the white balls, changes the current player,
	// and shows the stats
	if (this->balls.at(0)->inPocket || fault) {
		ballsStopped();
		resetWhiteBall();
		showStats();
	}
	// else it waits for the balls to stop and if the current player hasn't put any ball in
	// in the pockets, then it chenges the current player
	else if (releaseWhiteBall && !moveWhiteBall && !poolGameCamera->isTracking && ballsStopped()) {
		if (!anyBallInPocket) {
			changeCrtPlayer();
		}
		showStats();
		prepareShot();
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(poolGameCamera->GetViewMatrix(), poolGameCamera->GetProjectionMatrix());
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (moveWhiteBall) {
		float radius = this->balls.at(0)->radius;

		if (window->KeyHold(GLFW_KEY_W)
			&& this->balls.at(0)->center.x - deltaTime / 2.0 > tableLength / 6.0 + radius) {
			this->balls.at(0)->center.x -= deltaTime / 2.0;
		}
		if (window->KeyHold(GLFW_KEY_S)
			&& this->balls.at(0)->center.x + deltaTime / 2.0 < tableLength / 2.0 - sideHeight - radius) {
			this->balls.at(0)->center.x += deltaTime / 2.0;
		}
		if (window->KeyHold(GLFW_KEY_A)
			&& this->balls.at(0)->center.z + deltaTime / 2.0 < tableWidth / 2.0 - sideHeight - radius) {
			this->balls.at(0)->center.z += deltaTime / 2.0;
		}
		if (window->KeyHold(GLFW_KEY_D)
			&& this->balls.at(0)->center.z - deltaTime / 2.0 > -tableWidth / 2.0 + sideHeight + radius) {
			this->balls.at(0)->center.z -= deltaTime / 2.0;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		moveWhiteBall = false;
		trackWhiteBall = true;
		firstBallTouch = false;
		poolGameCamera->trackWhiteBall(this->balls.at(0));
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (trackWhiteBall && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		poolGameCamera->RotateThirdPerson_OY(-deltaX / 100.0);
		rotateCueAngularStep = rotateCueAngularStep - deltaX / 100.0;
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (button == GLFW_MOUSE_BUTTON_2)
	{
		doCueAnimation = 1;
		cueAnimationDistance = 0;
	}
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (button == GLFW_MOUSE_BUTTON_2)
	{
		//doCueAnimation = 0;
		//poolGameCamera->viewShot();
		this->balls.at(0)->speed = ballPower;
		trackWhiteBall = false;
		releaseWhiteBall = true;
		shot = false;
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
