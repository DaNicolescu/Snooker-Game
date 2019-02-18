#pragma once
#include <stdlib.h>
#include <time.h>
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include "GeometricObject.h"

class Tema3 : public SimpleScene
{
	public:
		Tema3();
		~Tema3();

		void Init() override;

		int mapSize;

		// 0 - celula goala
		// 1 - drum
		// 2 - intersectie
		// 3 - cladire
		int** map;

		Mesh* roadTile;
		Mesh* grassTile;
		std::vector<Mesh*> buildings;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void createMap(int size);
		void viewMap();
		void createRoads();
		void renderRoads();
		void renderGrass();
		Mesh* createBuilding(glm::vec3 center, float length, float width, float height);
		Texture2D* chooseTexture();
		void createAndPlaceBuildings();
		void renderBuildings();

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		std::unordered_map<std::string, Texture2D*> mapTextures;
		GLuint randomTextureID;
};
