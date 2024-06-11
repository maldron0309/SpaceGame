#include <tiledRenderer.h>



void TiledRenderer::render(gl2d::Renderer2D& renderer)
{

	auto viewRect = renderer.getViewRect();

	// 현재 플레이어의 위치 시차 강도를 곱함
	glm::vec2 paralaxDistance = { viewRect.x, viewRect.y };
	paralaxDistance *= -paralaxStrength;

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			int posX = x + int((viewRect.x - paralaxDistance.x) / backgroundSize);
			int posY = y + int((viewRect.y - paralaxDistance.y) / backgroundSize);

			renderer.renderRectangle(
				glm::vec4{ posX, posY, 1, 1 } * backgroundSize
				+ glm::vec4(paralaxDistance, 0, 0), texture); // 렌더링 호출에 추가되어 배경 이동 속도를 느리게 만듦

		}
	}



	renderer.renderRectangle({ 0, 0, backgroundSize, backgroundSize }, texture);

}