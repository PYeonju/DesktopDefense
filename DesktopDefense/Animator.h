#pragma once

#include "AnimationClip.h"
#include "ComponentBase.h"

namespace Engine
{
	class Animator : public ComponentBase
	{
	public:
		explicit Animator(GameObject* _gameObject);

		void Tick() override;

	private:
		// ���� �� Animator Component�� ��ϵ� �ִϸ��̼� Ŭ���Դϴ�.
		AnimationClip* m_AnimationClip;

		// ��ϵ� �ִϸ��̼��� ����� ���� ��������Ʈ�� �ε����Դϴ�. m_Animation�� size�� ���� ���� ��Ʈ���� �ʿ��մϴ�.
		int m_SpriteIndex = 0;

		// ���� �ֱ� ��������Ʈ�� ��ü�� �ð��Դϴ�. �� �ð��� ������ �����Ӹ��� ���� �ð��� üũ�ϰ�
		// m_TimeForSpriteChange�� �� �� ���� ���� �� ��������Ʈ�� �ѱ�� �ִϸ��̼��� ����մϴ�.
		float m_LastSpriteTime;

	public:
		// �� ������Ʈ �ν��Ͻ��� ������ �ִ� ���� ������Ʈ�� ���°� ����� �� Ʋ����� �ִϸ��̼� Ŭ���� ��ü�մϴ�.
		void SetAnimationClip(AnimationClip* _animationClip);
	};
}
