#pragma once

#include <Core/GPU/Mesh.h>

class Brick {
public:
	Mesh* mesh;

	Brick(Mesh* mesh, int index, float displayTime);
	~Brick();

	int getIndex();
	bool isRemoved();
	void remove();
	void stopScale();
	bool isScaled();
	void decreaseDisplayTime(float value);
	float getDisplayTime();

private:
	int index;
	bool removed;
	bool scaled;
	float displayTime;
};