#pragma once

#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <include/glm.h>
#include <string>
#include "Object3D.h"

namespace CreateObject {
	void CreateWallsAndFloor(std::unordered_map<std::string, Mesh*>& meshes, std::unordered_map<std::string, Shader*>& shaders, std::unordered_map<std::string, Texture2D*>& mapTextures);
	void createPoolTable(std::unordered_map<std::string, Mesh*>& meshes, std::vector<Mesh*>& pockets, float tableLength, float tableHeigth, float tableWidth, float sideLength, float sideHeight, float sideWidth, float pocketRadius);
	void createBallShader(std::unordered_map<std::string, Shader*>& shaders);
	void createBallMesh(std::unordered_map<std::string, Mesh*>& meshes);
	void createCueShader(std::unordered_map<std::string, Shader*>& shaders);
	void createCue(std::unordered_map<std::string, Mesh*>& meshes, float tableLength, float tableHeigth, float cueLength, float cueWidth, float cueHeight, float ballRadius);
}