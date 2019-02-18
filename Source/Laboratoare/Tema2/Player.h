#pragma once

#include <string>

class Player {
public:
	Player() :
		color("noColor"),
		numOfBallsPutInPocket(0),
		numOfFaults(0),
		won(false),
		canHitBlackBall(false)
	{
	}
	~Player();

	std::string color;
	int numOfBallsPutInPocket;
	int numOfFaults;
	bool won;
	bool canHitBlackBall;
private:

};
