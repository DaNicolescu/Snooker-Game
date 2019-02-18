#include "CreateObject.h"

void CreateObject::CreateWallsAndFloor(std::unordered_map<std::string, Mesh*>& meshes,
	std::unordered_map<std::string, Shader*>& shaders, 
	std::unordered_map<std::string, Texture2D*>& mapTextures) {

	const std::string textureLoc = "Source/Laboratoare/Tema2/Textures/";

	Texture2D* texture = new Texture2D();
	texture->Load2D((textureLoc + "floor.jpg").c_str(), GL_REPEAT);
	mapTextures["floor"] = texture;

	Mesh* mesh = new Mesh("wall");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "stones.jpg").c_str(), GL_REPEAT);
	mapTextures["bricks"] = texture;

	Shader *shader = new Shader("Wall");
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/WallVertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/WallFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;
}


void CreateObject::createPoolTable(std::unordered_map<std::string, Mesh*>& meshes, 
	std::vector<Mesh*>& pockets, float tableLength, float tableHeigth,
	float tableWidth, float sideLength, float sideHeight, float sideWidth, float pocketRadius) {

	float offset = 0.0001;

	Mesh* table = Object3D::CreateRectagularCuboid("table", glm::vec3(0, tableHeigth / 2.0, 0),
		tableLength, tableHeigth, tableWidth, glm::vec3(0.039, 0.42, 0.011));
	meshes["table"] = table;

	Mesh* side1 = Object3D::CreateRectagularCuboid("side1", glm::vec3(0, tableHeigth + sideHeight / 2.0,
		-tableWidth / 2.0 + sideWidth / 2.0), sideLength, sideHeight, sideWidth, glm::vec3(0, 0.5, 0));
	meshes["side1"] = side1;

	Mesh* side3 = Object3D::CreateRectagularCuboid("side3", glm::vec3(0, tableHeigth + sideHeight / 2.0,
		tableWidth / 2.0 - sideWidth / 2.0), sideLength, sideHeight, sideWidth, glm::vec3(0, 0.5, 0));
	meshes["side3"] = side3;

	sideWidth = tableWidth;
	sideLength = 0.1;

	Mesh* side2 = Object3D::CreateRectagularCuboid("side2", glm::vec3(tableLength / 2.0 - sideLength / 2.0,
		tableHeigth + sideHeight / 2.0, 0), sideLength, sideHeight, sideWidth, glm::vec3(0, 0.5, 0));
	meshes["side2"] = side2;

	Mesh* side4 = Object3D::CreateRectagularCuboid("side4", glm::vec3(-tableLength / 2.0 + sideLength / 2.0,
		tableHeigth + sideHeight / 2.0, 0), sideLength, sideHeight, sideWidth, glm::vec3(0, 0.5, 0));
	meshes["side4"] = side4;


	// middle pockets
	meshes["pocket1"] = Object3D::CreateHalfCircle("pocket1", glm::vec3(0, tableHeigth + offset,
		-tableWidth / 2.0 + sideLength), pocketRadius, glm::vec3(0, 0, 0), false, false);
	meshes["pocket2"] = Object3D::CreateHalfCircle("pocket2", glm::vec3(0, tableHeigth,
		-tableWidth / 2.0 + sideLength + offset), pocketRadius, glm::vec3(0, 0, 0), true, false);

	pockets.push_back(meshes["pocket1"]);

	meshes["pocket3"] = Object3D::CreateHalfCircle("pocket3", glm::vec3(0, tableHeigth + offset,
		tableWidth / 2.0 - sideLength), pocketRadius, glm::vec3(0, 0, 0), false, true);
	meshes["pocket4"] = Object3D::CreateHalfCircle("pocket4", glm::vec3(0, tableHeigth,
		tableWidth / 2.0 - sideLength - offset), pocketRadius, glm::vec3(0, 0, 0), true, false);

	pockets.push_back(meshes["pocket3"]);

	// left side pockets
	meshes["pocket5"] = Object3D::CreateQuarterCircle("pocket5", glm::vec3(-tableLength / 2.0 + sideLength,
		tableHeigth, -tableWidth / 2.0 + sideLength + offset), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XY, false, false);
	meshes["pocket6"] = Object3D::CreateQuarterCircle("pocket6", glm::vec3(-tableLength / 2.0 + sideLength + offset,
		tableHeigth + offset, -tableWidth / 2.0 + sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::YZ, false, false);
	meshes["pocket7"] = Object3D::CreateQuarterCircle("pocket7", glm::vec3(-tableLength / 2.0 + sideLength,
		tableHeigth + offset, -tableWidth / 2.0 + sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XZ, false, false);

	pockets.push_back(meshes["pocket7"]);

	meshes["pocket8"] = Object3D::CreateQuarterCircle("pocket8", glm::vec3(-tableLength / 2.0 + sideLength,
		tableHeigth, tableWidth / 2.0 - sideLength - offset), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XY, false, false);
	meshes["pocket9"] = Object3D::CreateQuarterCircle("pocket9", glm::vec3(-tableLength / 2.0 + sideLength + offset,
		tableHeigth + offset, tableWidth / 2.0 - sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::YZ, true, false);
	meshes["pocket10"] = Object3D::CreateQuarterCircle("pocket10", glm::vec3(-tableLength / 2.0 + sideLength,
		tableHeigth + offset, tableWidth / 2.0 - sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XZ, true, false);

	pockets.push_back(meshes["pocket10"]);

	// right side pockets
	meshes["pocket11"] = Object3D::CreateQuarterCircle("pocket11", glm::vec3(tableLength / 2.0 - sideLength,
		tableHeigth, -tableWidth / 2.0 + sideLength + offset), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XY, true, false);
	meshes["pocket12"] = Object3D::CreateQuarterCircle("pocket12", glm::vec3(tableLength / 2.0 - sideLength - offset,
		tableHeigth + offset, -tableWidth / 2.0 + sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::YZ, false, false);
	meshes["pocket13"] = Object3D::CreateQuarterCircle("pocket13", glm::vec3(tableLength / 2.0 - sideLength,
		tableHeigth + offset, -tableWidth / 2.0 + sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XZ, false, true);

	pockets.push_back(meshes["pocket13"]);

	meshes["pocket14"] = Object3D::CreateQuarterCircle("pocket14", glm::vec3(tableLength / 2.0 - sideLength,
		tableHeigth, tableWidth / 2.0 - sideLength - offset), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XY, true, false);
	meshes["pocket15"] = Object3D::CreateQuarterCircle("pocket15", glm::vec3(tableLength / 2.0 - sideLength - offset,
		tableHeigth + offset, tableWidth / 2.0 - sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::YZ, true, false);
	meshes["pocket16"] = Object3D::CreateQuarterCircle("pocket16", glm::vec3(tableLength / 2.0 - sideLength,
		tableHeigth + offset, tableWidth / 2.0 - sideLength), pocketRadius, glm::vec3(0, 0, 0),
		Object3D::viewPlane::XZ, true, true);

	pockets.push_back(meshes["pocket16"]);
}

void CreateObject::createBallShader(std::unordered_map<std::string, Shader*>& shaders) {
	Shader *shader = new Shader("BallShader");
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/BallVertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/BallFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;
}

void CreateObject::createBallMesh(std::unordered_map<std::string, Mesh*>& meshes) {
	Mesh* mesh = new Mesh("ball");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes["ball"] = mesh;
}

void CreateObject::createCueShader(std::unordered_map<std::string, Shader*>& shaders) {
	Shader *shader = new Shader("CueShader");
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/CueVertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Tema2/Shaders/CueFragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;
}

void CreateObject::createCue(std::unordered_map<std::string, Mesh*>& meshes, float tableLength, 
	float tableHeigth, float cueLength, float cueWidth, float cueHeight, float ballRadius) {

	Mesh* cue = Object3D::CreateRectagularCuboid("cue", glm::vec3(0, tableHeigth + ballRadius, 0),
		cueLength, cueHeight, cueWidth, glm::vec3(0.4, 0.2, 0));
	meshes["cue"] = cue;
}