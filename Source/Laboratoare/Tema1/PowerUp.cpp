#include "PowerUp.h"

PowerUp::PowerUp(Mesh* mesh, float side) 
	: mesh(mesh),
	side(side),
	translateY(0),
	angularStep(0),
	removed(false) {

	mesh->radius = side;
}

PowerUp::~PowerUp() {
}

float PowerUp::getTranslateY() {
	return this->translateY;
}

void PowerUp::incTranslateY(float value) {
	this->translateY += value;
}

float PowerUp::getAngularStep() {
	return this->angularStep;
}

void PowerUp::incAngularStep(float value) {
	this->angularStep += value;
}

float PowerUp::getSide() {
	return this->side;
}

bool PowerUp::isRemoved() {
	return this->removed;
}

void PowerUp::remove() {
	this->removed = true;
}
