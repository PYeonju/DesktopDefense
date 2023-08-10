#include "GameObject.h"

#include "ComponentBase.h"
#include "GameInstanceBase.h"
#include "GameWorld.h"

using namespace Engine;

GameObject::GameObject()
	: m_bEnable(true),
	  m_Position(Vector2D::Zero)
{
	GameWorld::GetInstance()->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObject�� �Ҹ�ɶ� GameObject�� ������ �ִ� component�� ���� ������
	for (ComponentBase* _component : this->m_Components)
	{
		delete _component;
	}
}

void GameObject::PreTick()
{
	for (const auto& _component : m_Components)
		_component->PreTick();
}

void GameObject::Tick()
{
	for (const auto& _component : m_Components)
		_component->TryTick();
}

void GameObject::SetEnable(bool _value)
{
	if (_value == m_bEnable)
		return;

	m_bEnable = _value;

	GameWorld::GetInstance()->UpdateGameObjectEnable(this);
}
