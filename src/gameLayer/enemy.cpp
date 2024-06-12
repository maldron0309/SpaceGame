#include <enemy.h>
#include <tiledRenderer.h>


void Enemy::render(gl2d::Renderer2D& renderer, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas)
{
	// �� ���ּ� ������
	renderSpaceShip(renderer, position, enemyShipSize, sprites, atlas.get(type.x, type.y), viewDir);
}

bool Enemy::update(float deltaTime, glm::vec2 playerPos)
{
	// �÷��̾�� �� ������ ���� ���� ���
	glm::vec2 directionToPlayer = playerPos - position;

	// �÷��̾�� ���� ���� ��ġ�� �ִ� ���, �⺻ ������ ���������� ����
	if (glm::length(directionToPlayer) == 0)
		directionToPlayer = { 1,0 };
	else
		directionToPlayer = glm::normalize(directionToPlayer);

	// ���� �߻����� ���θ� ����
	bool shoot = (glm::length(directionToPlayer + viewDir) >= fireRange);

	// �߻� ���� �������� Ȯ���ϰ�, �׷��� ������ Ÿ�̸Ӹ� ����
	if (shoot)
	{
		if (firedTime <= 0.f)
			firedTime = fireTimeReset;
		else
			shoot = 0;
	}

	// �߻� Ÿ�̸� ������Ʈ
	firedTime -= deltaTime;
	if (firedTime < 0)
		firedTime = 0.f;

	// ���ο� ���� ���� �ʱ�ȭ
	glm::vec2 newDir = {};

	// ���� �÷��̾ ���� ���� ���� �̳��� ȸ���� ���
	if (glm::length(directionToPlayer + viewDir) <= 0.2)
	{
		// �����ϰ� ���ο� ȸ�� ���� ����
		if (rand() % 2)
			newDir = glm::vec2(directionToPlayer.y, -directionToPlayer.x);
		else
			newDir = glm::vec2(-directionToPlayer.y, directionToPlayer.x);
	}
	else
		// ���ο� ������ ���
		newDir = deltaTime * turnSpeed * directionToPlayer + viewDir;

	// ���ο� ���� ������ ���� ��� �� ����ȭ
	float length = glm::length(newDir);
	viewDir = glm::normalize(newDir);

	// ���� ������ ���̸� ����
	length = glm::clamp(length, 0.1f, 3.f);
	// ���ο� ��ġ ���
	position += viewDir * deltaTime * speed * length;

	// �߻� ���θ� ��ȯ
	return shoot;
}
