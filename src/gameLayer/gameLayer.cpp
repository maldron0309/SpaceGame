#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <tiledRenderer.h>

struct GameplayData
{
	glm::vec2 playerPos = { 100,100 }; // 플레이어 기본 위치
};

GameplayData data;

gl2d::Renderer2D renderer;

constexpr int BACKGROUNDS = 3;

gl2d::Texture spaceShipTexture; // 플레이어

gl2d::Texture backgroundTexture[BACKGROUNDS]; // 배경화면
TiledRenderer tiledRenderer[BACKGROUNDS];

bool initGame()

{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceShipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);
	backgroundTexture[0].loadFromFile(RESOURCES_PATH "background1.png", true);
	backgroundTexture[1].loadFromFile(RESOURCES_PATH "background2.png", true);
	backgroundTexture[2].loadFromFile(RESOURCES_PATH "background3.png", true);

	tiledRenderer[0].texture = backgroundTexture[0];
	tiledRenderer[1].texture = backgroundTexture[1];
	tiledRenderer[2].texture = backgroundTexture[2];

	tiledRenderer[0].paralaxStrength = 0;
	tiledRenderer[1].paralaxStrength = 0.4; 
	tiledRenderer[2].paralaxStrength = 0.7; 

	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion

#pragma region movement

	glm::vec2 move = {};

	if (platform::isButtonHeld(platform::Button::W)) move.y = -1; // up
	if (platform::isButtonHeld(platform::Button::S)) move.y = 1; // down
	if (platform::isButtonHeld(platform::Button::A)) move.x = -1; // left
	if (platform::isButtonHeld(platform::Button::D)) move.x = 1; // right

	if (move.x != 0 || move.y != 0) // 벡터 정규화
	{
		move = glm::normalize(move);
		move *= deltaTime * 1000; //200 pixels per seccond
		data.playerPos += move;
	}

#pragma endregion


#pragma region mouse pos

	glm::vec2 mousePos = platform::getRelMousePosition();
	glm::vec2 screenCenter(w / 2.f, h / 2.f); 

	glm::vec2 mouseDir = mousePos - screenCenter;

	if (glm::length(mouseDir) == 0.f) mouseDir = { 1, 0 };
	else mouseDir = normalize(mouseDir);

	float spaceShipAngle = atan2(mouseDir.y, -mouseDir.x);

#pragma endregion

#pragma region reder background

	renderer.currentCamera.zoom = 0.5; // 카메라 확대 범위

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		tiledRenderer[i].render(renderer);

	}

#pragma endregion

	// 플레이어를 따라다니는 카메라
	renderer.currentCamera.follow(data.playerPos, deltaTime * 450, 10, 50, w, h);
	renderer.renderRectangle({ data.playerPos, 250, 250 }, spaceShipTexture,
		Colors_White, {}, glm::degrees(spaceShipAngle) + 90.f);


	renderer.flush();


	//ImGui::ShowDemoWindow();


	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}