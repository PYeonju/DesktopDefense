#include "MiniGun.h"

#include "Audio.h"

extern Audio* _audio;

MiniGun::MiniGun(GameObject* _gameObject)
	: Weapon(_gameObject)
{
	this->m_Damage = MINIGUN_DAMAGE;

	m_FireSound = AudioClip_LoadFromFile(_audio, L"Sounds/MiniGunSound.wav", false);
}

bool MiniGun::AttackTick()
{
	auto _collider = this->m_GameObject->GetComponent<ColliderBase>();
	if (_collider == nullptr)
		return false;

	if (static_cast<int>(Input::GetInstance()->GetState(VK_LBUTTON)) & 0x01)
	{
		Audio_Play(_audio, m_FireSound, false);

		_collider->m_bEnable = true;
		return true;
	}
	else
	{
		_collider->m_bEnable = false;
		return false;
	}
}

void MiniGun::Attack(Miner* _miner)
{
	// ���� ��Ÿ���� ������ �ʾҴٸ� ������ ������ �� �����ϴ�.
	const float _gameTime = Time::GetInstance()->GetGameTime();
	if (_gameTime - m_LastAttackTime < m_TimePerAttack)
		return;

	m_LastAttackTime = _gameTime;

	_miner->Damage(m_Damage);
}
