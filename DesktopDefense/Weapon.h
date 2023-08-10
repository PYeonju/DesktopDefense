#pragma once
#include "AudioClip.h"
#include "ComponentBase.h"
#include "DesktopDefense.h"
#include "GameObject.h"
#include "Miner.h"

using namespace Engine;

class Weapon : public ComponentBase
{
public:
	Weapon(GameObject* _gameObject);

	virtual bool AttackTick() = 0; // ���� �����Լ� (�������̽��� ����)

	virtual void Attack(Miner* _miner) = 0;

	int m_Damage;

	float m_LastAttackTime; // �ֱ� �������� �� �ð�

	float m_TimePerAttack; // ���� �ӵ� (���� 1ȸ�� �� ���� �ð��� �ɸ����� ��Ʈ��)

	AudioClip* m_FireSound;
};

// ��� : ��¥ ���콺 ���� ��ư���� �÷��̾ ������ ������ �� Weapon �� Attack�� ��� ������ �� �Լ��� ����� ��
// (AttackTick()�� �÷��̾ ���� ��ư�� ������ ���� �� ����ȴ�)

// 1. ������ Mouse Cursor�� 'ũ�ν� ���' ���������� �ٲ۴�. (���콺 ����ٴϴ� ���� ��������Ʈ�� ���콺 Ŀ�� ��ġ �������� �˸´� ���� ����) ..?
// 2. ���� ���콺 Ŭ���� �� ������ (�÷��̾ ���� ������ ������ ������) ���콺 Ŭ���� �������� �޾ƿ� �����Ѵ�.
// 3. ���� ���� �� ��ġ�� ���� ������ �´� ũ���� �ݶ��̴�, ����Ʈ ��������Ʈ�� �������� ���� �ӽ� ���� ������Ʈ�� ���� ..? => �� ��Ŭ �ݶ��̴� �� ��
// 4. �浹�˻� => �浹 �˻� �� ���� �ӽ� ������ �ݶ��̴��� delete ..? ��ƴ� .. ���÷��� ..?
// 5. �浹 true �� => ���η� Ÿ�� �ö󰡼� hp ��ƹ����� ���ο����� hp <= 0 �Ǹ� ���� GameObject�� ���忡�� ����
// 6. ��ư ������Ʈ�� �ұ� ..

// m_Player�� .. ������Ʈ �� �ھ�
// Collider�� ���콺 Ŀ���� ���󰣴� (���� ������ on, ���� �� ������ off)
// ���콺 Ŀ�� ��ǥ�� ����Ʈ�� ����Ų��.

// ���� ������ AttackTick()�� ���� => �ݶ��̴� Tick���ٰ� �ݹ��� ������.
// �� �ݶ��̴� tick ���� �� m_bEnable�� ���ش� ..?

// �浹�� true�̸� ���ڷ� ���� �ݹ��Լ��� �������ٵ� ..
// ���ڷ� �� �ѱ沨�ݾ� ..?
