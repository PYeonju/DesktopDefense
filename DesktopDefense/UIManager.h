#pragma once
#include "ComponentBase.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Player.h"
#include "Sprite.h"
#include <map>
#include <string>

using namespace Engine;

class UIManager : public ComponentBase
{
public:
	UIManager(GameObject* _gameObject);

	void Tick() override;

	// GameStart �� �� �� �������� ǥ���ϴ� �Լ�
	void GameTimeTick();

	// 0. �ʱ�ȭ
	void Initialize(Player* _Player);

	// 1. �κ��丮 UI�� �׸���, ���⸦ ȹ���� ��� ������ �����ϴ� �Լ�
	void InventoryTick();

	// 2. ���� ������ ���⿡ ���� Ŀ���� �����Ű�� ���� �Լ�
	void ChangeWeaponCursor();
	
	void MoveToMouseCursorTick();

	// inline Vector2D GetInventoryPosition() const { return this->m_InventoryPosition; }
	
private:
	// �κ��丮 Ui�� Position
	Vector2D m_InventoryPosition;

	// �κ��丮 Ui �� ���� �������� Position
	Vector2D m_WeaponIconPosition;

	// �÷��̾�Լ� �κ��丮 ���� �� ���� ������� ���⸦ ��� ����
	Player* m_Player;

	// �κ��丮 ��������Ʈ
	Sprite* m_Select_WeaponSprite[5];

	// �κ��丮 UI�� Render�ϱ� ���� ������Ʈ
	GameObject* m_InventoryObject;

	// ���� Ŀ�� ��������Ʈ
	Sprite* m_WeaponCursorSprite[5];

	// ���� Ŀ�� ���� �� ��������Ʈ
	Sprite* m_WeaponCursorAttackSprite[5];

	// ���� Ŀ���� Render�� ������Ʈ
	GameObject* m_WeaponCursorObject;

	// ���� Ŀ�� ���ݽ��� ��������Ʈ�� Render�� ������Ʈ
	GameObject* m_WeaponCursorAttackObject;

	Vector2D m_MousePosition;

	// ������� �� �� ������� ����ϱ� ���� ��������Ʈ���� ����
	vector<Sprite*> m_NumbersForTime;
};