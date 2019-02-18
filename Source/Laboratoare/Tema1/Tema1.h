#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <time.h>
#include <Core/Engine.h>
#include "Brick.h"
#include "PowerUp.h"

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		// rezolutia
		glm::ivec2 resolution;
		// folosit pentru compararea valorilor float
		float epsilon;

		// metoda pentru detectarea coliziunii intre un obiect cu hitbox cerc, si altul cu hitbox dreptunghi
		bool collision(Mesh* ball, float cxBall, float cyBall, Mesh* obj, float deltaTimeSeconds, bool reflect);

		// metode pentru creare pereti
		void createBottomWall(float width);
		void createWalls(glm::ivec2 resolution, float width);

		// variabile si metode pentru bila
		float txBall, tyBall;
		int directionX;
		int directionY;
		float cosRadians;
		bool ballMove;
		// daca strongBall == true, bila nu va ricosa
		// din caramizi
		bool strongBall;
		void createBall(float radius);
		void ballCollision(Mesh* ball, float deltaTimeSeconds);

		// variabile si metode pentru platforma
		float txPad, tyPad;
		float padWidth;
		void createPad(float width, float height);

		// variabile si metode pentru caramizi
		int xNumOfBricks;
		int yNumOfBricks;
		std::vector<Brick*> bricks;
		void createBricks();

		// variabile si metode pentru powerups
		std::unordered_map<int, PowerUp*> powerUps;
		float powerUpChance;
		int powerUpTypes;
		// vector in care se pastreaza
		// tmpul ramas pentru care fiecare power up este activ
		float* powerUpTime;
		// timpul maxim cat un power up poate ramane activ
		float* maxPowerUpTime;
		void createPowerUp(Brick* brick);
		void resetPowerUpTime(int idx);
		
		// variabile si metode pentru vieti
		int numOfLives;
		void createLives(float radius);
		void powerUpCollision(Mesh* pad, float deltaTimeSeconds);
		
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
};
