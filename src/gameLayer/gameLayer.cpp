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


struct GameplayData
{
	glm::vec2 playerPos = { 100,100 }; // 플레이어 기본 위치
};


GameplayData data;

gl2d::Renderer2D renderer;

gl2d::Texture spaceShipTexture;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceShipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);


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
		move *= deltaTime * 200; //200 pixels per seccond
		data.playerPos += move;
	}

#pragma endregion


	renderer.renderRectangle({ data.playerPos, 200, 200 }, spaceShipTexture);


	renderer.flush();


	//ImGui::ShowDemoWindow();


	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}