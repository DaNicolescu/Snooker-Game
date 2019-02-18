#pragma once

#include <Core/GPU/Mesh.h>

class PowerUp {
public:
	Mesh* mesh;

	PowerUp(Mesh* mesh, float side);
	~PowerUp();
	float getTranslateY();
	void incTranslateY(float value);
	float getAngularStep();
	void incAngularStep(float value);
	float getSide();
	bool isRemoved();
	void remove();

private:
	float translateY;
	float angularStep;
	float side;
	bool removed;
};