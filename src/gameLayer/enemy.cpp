#include <enemy.h>
#include <tiledRenderer.h>

void Enemy::render(gl2d::Renderer2D &renderer, gl2d::Texture &sprites, gl2d::TextureAtlasPadding &atlas)
{
	renderSpaceShip(renderer, position, enemyShipSize, sprites, atlas.get(type.x, type.y), viewDir);
}


//returns true if should shoot bullet
bool Enemy::update(float deltaTime, glm::vec2 playerPos)
{

	glm::vec2 dirToPlayer = playerPos - position;
	if (glm::length(dirToPlayer) == 0) { dirToPlayer = {1,0}; }
	else { dirToPlayer = glm::normalize(dirToPlayer); }

	glm::vec2 newDirection = {};

	bool shoot = (glm::length(dirToPlayer + viewDir) >= fireRange);

	if (shoot)
	{
		if (firedTime <= 0.f) firedTime = fireTimeReset;
		else shoot = 0;
	}

	firedTime -= deltaTime;
	if (firedTime < 0) firedTime = 0.f;


	if (glm::length(dirToPlayer + viewDir) <= 0.2)
	{
		if (rand() % 2) newDirection = glm::vec2(dirToPlayer.y, -dirToPlayer.x);
		else newDirection = glm::vec2(-dirToPlayer.y, dirToPlayer.x);
	}
	else newDirection = deltaTime * turnSpeed * dirToPlayer + viewDir;

	float length = glm::length(newDirection);
	viewDir = glm::normalize(newDirection);
	
	length = glm::clamp(length, 0.1f, 3.f);

	position += viewDir * deltaTime * speed * length;

	return shoot;
}
