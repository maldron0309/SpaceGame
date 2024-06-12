#include <enemy.h>
#include <tiledRenderer.h>


void Enemy::render(gl2d::Renderer2D& renderer, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas)
{
	// 적 우주선 렌더링
	renderSpaceShip(renderer, position, enemyShipSize, sprites, atlas.get(type.x, type.y), viewDir);
}

bool Enemy::update(float deltaTime, glm::vec2 playerPos)
{
	// 플레이어와 적 사이의 방향 벡터 계산
	glm::vec2 directionToPlayer = playerPos - position;

	// 플레이어와 적이 같은 위치에 있는 경우, 기본 방향을 오른쪽으로 설정
	if (glm::length(directionToPlayer) == 0)
		directionToPlayer = { 1,0 };
	else
		directionToPlayer = glm::normalize(directionToPlayer);

	// 적이 발사할지 여부를 결정
	bool shoot = (glm::length(directionToPlayer + viewDir) >= fireRange);

	// 발사 가능 상태인지 확인하고, 그렇지 않으면 타이머를 리셋
	if (shoot)
	{
		if (firedTime <= 0.f)
			firedTime = fireTimeReset;
		else
			shoot = 0;
	}

	// 발사 타이머 업데이트
	firedTime -= deltaTime;
	if (firedTime < 0)
		firedTime = 0.f;

	// 새로운 방향 벡터 초기화
	glm::vec2 newDir = {};

	// 적이 플레이어를 향해 일정 각도 이내로 회전할 경우
	if (glm::length(directionToPlayer + viewDir) <= 0.2)
	{
		// 랜덤하게 새로운 회전 방향 설정
		if (rand() % 2)
			newDir = glm::vec2(directionToPlayer.y, -directionToPlayer.x);
		else
			newDir = glm::vec2(-directionToPlayer.y, directionToPlayer.x);
	}
	else
		// 새로운 방향을 계산
		newDir = deltaTime * turnSpeed * directionToPlayer + viewDir;

	// 새로운 방향 벡터의 길이 계산 및 정규화
	float length = glm::length(newDir);
	viewDir = glm::normalize(newDir);

	// 방향 벡터의 길이를 제한
	length = glm::clamp(length, 0.1f, 3.f);
	// 새로운 위치 계산
	position += viewDir * deltaTime * speed * length;

	// 발사 여부를 반환
	return shoot;
}
