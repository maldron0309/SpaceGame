#pragma once
#include <gl2d/gl2d.h>

constexpr float enemyShipSize = 250.f;

struct Enemy
{
	glm::uvec2 type = {}; // 텍스처 아틀라스 인덱싱용
	glm::vec2 position = {}; // 적의 위치

	glm::vec2 viewDir = { 1,0 }; // 적이 보는 방향

	float speed = 1500.f; // 이동 속도
	float turnSpeed = 3.f; // 회전 속도

	float firedTime = 1.f; // 발사 타이머

	float fireTimeReset = 0.2; // 발사 타이머 리셋 값
	float fireRange = 1.5; // 발사 범위
	float bulletSpeed = 2000; // 탄환 속도

	/// <summary>
	/// 적 우주선을 렌더링하는 함수
	/// </summary>
	/// <param name="renderer">그리기에 사용할 렌더러</param>
	/// <param name="sprites">우주선 스프라이트가 포함된 텍스처</param>
	/// <param name="atlas">우주선 스프라이트에 대한 텍스처 아틀라스</param>
	void render(gl2d::Renderer2D& renderer, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas);

	bool update(float deltaTime, glm::vec2 playerPos);
};
