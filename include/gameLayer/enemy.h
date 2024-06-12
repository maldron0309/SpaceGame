#pragma once
#include <gl2d/gl2d.h>

constexpr float enemyShipSize = 250.f;

struct Enemy
{
	glm::uvec2 type = {}; // �ؽ�ó ��Ʋ�� �ε��̿�
	glm::vec2 position = {}; // ���� ��ġ

	glm::vec2 viewDir = { 1,0 }; // ���� ���� ����

	float speed = 1500.f; // �̵� �ӵ�
	float turnSpeed = 3.f; // ȸ�� �ӵ�

	float firedTime = 1.f; // �߻� Ÿ�̸�

	float fireTimeReset = 0.2; // �߻� Ÿ�̸� ���� ��
	float fireRange = 1.5; // �߻� ����
	float bulletSpeed = 2000; // źȯ �ӵ�

	/// <summary>
	/// �� ���ּ��� �������ϴ� �Լ�
	/// </summary>
	/// <param name="renderer">�׸��⿡ ����� ������</param>
	/// <param name="sprites">���ּ� ��������Ʈ�� ���Ե� �ؽ�ó</param>
	/// <param name="atlas">���ּ� ��������Ʈ�� ���� �ؽ�ó ��Ʋ��</param>
	void render(gl2d::Renderer2D& renderer, gl2d::Texture& sprites, gl2d::TextureAtlasPadding& atlas);

	bool update(float deltaTime, glm::vec2 playerPos);
};
