#include "HandGun.h"

#include "Audio.h"

extern Audio* _audio;

HandGun::HandGun(GameObject* _gameObject)
	: Weapon(_gameObject)
{
	this->m_Damage = HANDGUN_DAMAGE;

	m_FireSound = AudioClip_LoadFromFile(_audio, L"Sounds/HandGunSound.wav", false);
}

bool HandGun::AttackTick()
{
	auto _collider = this->m_GameObject->GetComponent<ColliderBase>();
	if (_collider == nullptr)
		return false;

	if (Input::GetInstance()->GetState(VK_LBUTTON) == EKeyState::Down)
	{
		Audio_Play(_audio, m_FireSound, true);

		_collider->m_bEnable = true;
		return true;
	}
	else
	{
		_collider->m_bEnable = false;
		return false;
	}
}

void HandGun::Attack(Miner* _miner)
{
	// ���� ��Ÿ���� ������ �ʾҴٸ� ������ ������ �� �����ϴ�.
	const float _gameTime = Time::GetInstance()->GetGameTime();
	if (_gameTime - m_LastAttackTime < m_TimePerAttack)
		return;

	m_LastAttackTime = _gameTime;

	_miner->Damage(m_Damage);
}

// ��� : ��¥ ���콺 ���� ��ư���� �÷��̾ ������ ������ �� Weapon �� Attack�� ��� ������ �� �Լ��� ����� ��
// (AttackTick()�� �÷��̾ ���� ��ư�� ������ ���� �� ����ȴ�)

// 0. ChangeWeapon���� Ŀ���� �ش� ���⿡ �°� �ٲ۴�.
// 1. ������ Mouse Cursor�� 'ũ�ν� ���' ���������� �ٲ۴�. (���콺 ����ٴϴ� ���� ��������Ʈ�� ���콺 Ŀ�� ��ġ �������� �˸´� ���� ����) ..?
// 2. ���� ���콺 Ŭ���� �� ������ (�÷��̾ ���� ������ ������ ������) ���콺 Ŭ���� �������� �޾ƿ� �����Ѵ�.
// 3. ���� ���� �� ��ġ�� ���� ������ �´� ũ���� �ݶ��̴�, ����Ʈ ��������Ʈ�� �������� ���� �ӽ� ���� ������Ʈ�� ���� ..? => �� ��Ŭ �ݶ��̴� �� ��
// 4. �浹�˻� => �浹 �˻� �� ���� �ӽ� ������ �ݶ��̴��� delete ..? ��ƴ� .. ���÷��� ..?
// 5. �浹 true �� => ���η� Ÿ�� �ö󰡼� hp ��ƹ����� ���ο����� hp <= 0 �Ǹ� ���� GameObject�� ���忡�� ����
// 6. ��ư ������Ʈ�� �ұ� ..
