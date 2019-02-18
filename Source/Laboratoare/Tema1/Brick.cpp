#include "Brick.h"

Brick::Brick(Mesh* mesh, int index, float displayTime) 
	: mesh(mesh),
	index(index),
	displayTime(displayTime),
	removed(false),
	scaled(true) {
}

Brick::~Brick() {
}

int Brick::getIndex() {
	return this->index;
}

bool Brick::isRemoved() {
	return this->removed;
}

void Brick::remove() {
	this->removed = true;
}

void Brick::stopScale() {
	this->scaled = false;
}

bool Brick::isScaled() {
	return this->scaled;
}

void Brick::decreaseDisplayTime(float value) {
	this->displayTime -= value;
}

float Brick::getDisplayTime() {
	return this->displayTime;
}
