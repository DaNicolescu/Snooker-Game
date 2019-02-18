#pragma once
#include <Component/SimpleScene.h>
#include "Object3D.h"
#include "Ball.h"
#include "Tema2Camera.h"
#include "Player.h"
#include "RenderObject.h"
#include "CreateObject.h"
#include <vector>

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		std::unordered_map<std::string, Texture2D*> mapTextures;

		void RenderWalls();

		float epsilon;

		Player* player1;
		Player* player2;
		Player* crtPlayer;
		int playerTurn;

		float firstBallTouch;
		float anyBallInPocket;

		bool fault;

		float tableLength;
		float tableHeigth;
		float tableWidth;

		float sideLength;
		float sideHeight;
		float sideWidth;

		float pocketRadius;

		float ballRadius;
		std::vector<Ball*> balls;
		std::vector<Mesh*> pockets;
		float ballPower;
		bool moveWhiteBall;
		bool trackWhiteBall;
		bool releaseWhiteBall;
		bool showCue;
		bool shot;

		int doCueAnimation;
		float cueLength;
		float cueWidth;
		float cueHeight;
		float rotateCueAngularStep;
		float cueAnimationDistance;

		Tema2Camera* poolGameCamera;

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void renderPoolTable();
		void RenderBalls();
		void initialiseBalls();
		void positionAndRenderCue(float animationDistance);
		void railsCollision(Ball* ball, float deltaTime);
		void allRailsCollisions(float deltaTime);
		bool detectBallCollision(Ball* ball1, Ball* ball2);
		void bounceBalls(Ball * ball1, Ball * ball2);
		void detectCollisionsAndBounce();
		void setFrameMove(float deltaTimeSeconds);
		bool ballsStopped();
		void checkIfCanHitBlackBall();
		void checkIfWon();
		void checkPockets();
		void resetWhiteBall();
		void takeShot();
		void prepareShot();
		void changeCrtPlayer();
		void showStats();

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat4 modelMatrix;
		glm::mat4 cueModelMatrix;
		float translateX, translateY, translateZ;
		float scaleX, scaleY, scaleZ;
		float angularStepOX, angularStepOY, angularStepOZ;
		GLenum polygonMode;
};
