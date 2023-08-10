#include "Animator.h"

#include "GameObject.h"
#include "Renderer.h"

using namespace Engine;

Animator::Animator(GameObject* _gameObject)
	: ComponentBase(_gameObject)
{
}

void Animator::Tick()
{
	ComponentBase::Tick();

	if (m_AnimationClip == nullptr)
		return;

	const float _gameTime = Time::GetInstance()->GetGameTime();

	const bool _bShouldFlip = _gameTime - m_LastSpriteTime >= m_AnimationClip->GetTimeForSpriteChange();
	if (_bShouldFlip == false)
		return;

	const auto& _sprites = m_AnimationClip->GetSprites();

	m_SpriteIndex = (m_SpriteIndex + 1) % _sprites.size();

	Renderer* _renderer = m_GameObject->GetComponent<Renderer>();
	if (_renderer != nullptr)
		_renderer->SetSprite(_sprites.at(m_SpriteIndex));

	m_LastSpriteTime = _gameTime;
}

void Animator::SetAnimationClip(AnimationClip* _animationClip)
{
	// �θ� ���� ������Ʈ�� ���¿� �´� �ִϸ��̼� Ŭ���� �Ű������� �޾� �ִϸ����Ϳ� ��ϵ� Ŭ���� �����մϴ�.
	m_AnimationClip = _animationClip;

	// �ִϸ��̼��� �������� �ʱ�ȭ�մϴ�.
	m_SpriteIndex = 0;

	// ���� �ð����� �ٽ� �ִϸ��̼� �ð��� �ʱ�ȭ�մϴ�.
	m_LastSpriteTime = Time::GetInstance()->GetGameTime();
}
