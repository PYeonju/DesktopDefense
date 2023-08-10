#pragma once
#include <vector>

#include "ObjectBase.h"
#include "Vector2D.h"

namespace Engine
{
	class GameObject : public ObjectBase<GameObject>
	{
	public:
		GameObject();

		~GameObject();

		/// <summary>
		/// �� �����Ӹ��� World�� ��� ������Ʈ�� Tick()�� ȣ��Ǳ� ���� ȣ��Ǵ� �޼ҵ��Դϴ�.
		///	�Ϲ������� �� �����Ӹ��� ó���Ǳ� �ռ� �ʱ�ȭ�Ǿ�� �� ó���� ����մϴ�.
		/// </summary>
		void PreTick();

		/// <summary>
		/// �� �����Ӹ��� World�� ���� ȣ��Ǵ� �޼ҵ��Դϴ�.
		/// </summary>
		virtual void Tick();

		/// <summary>
		/// ���� ������Ʈ�� ������ �ִ� ������Ʈ �߿��� �Է¹��� Ÿ�԰� ��ġ�ϰų� �� Ÿ���� ����Ÿ���� ������Ʈ�� �ִ� ���
		///	�ش� ������Ʈ�� ��ȯ�մϴ�.
		///	���� �ش��ϴ� ������Ʈ�� ���ٸ� nullptr�� ��ȭ���մϴ�.
		/// </summary>
		template <class TComponent>
		TComponent* GetComponent();

		template <class TComponent>
		TComponent* AddComponent();

	public:
		Vector2D m_Position;

	private:
		bool m_bEnable;

		std::vector<class ComponentBase*> m_Components;

	public:
		inline bool GetEnable() const { return m_bEnable; }

		void SetEnable(bool _value);
	};

	template <class TComponent>
	TComponent* GameObject::GetComponent()
	{
		for (auto _component : m_Components)
		{
			TComponent* _castedComponent = dynamic_cast<TComponent*>(_component);

			if (_castedComponent != nullptr)
				return _castedComponent;
		}

		return nullptr;
	}

	template <class TComponent>
	TComponent* GameObject::AddComponent()
	{
		static_assert(std::is_base_of<ComponentBase, TComponent>::value, "TComponent must inherit from ComponentBase");

		TComponent* _newComponent = new TComponent(this);

		m_Components.emplace_back(_newComponent);
		return _newComponent;
	}
}
