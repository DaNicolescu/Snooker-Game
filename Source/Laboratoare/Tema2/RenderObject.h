#pragma once
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <include/glm.h>
#include "Tema2Camera.h"

namespace RenderObject {
	void RenderWall(Tema2Camera* camera, Mesh *mesh, Shader *shader, const glm::mat4& modelMatrix, Texture2D* texture1);
	void RenderBall(Tema2Camera * camera, Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, const glm::vec3 & color);
	void renderCue(Tema2Camera * camera, Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, const glm::vec3 & color, float incDistance, int doAnimation);
	void RenderMesh(Tema2Camera * camera, Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix);
}