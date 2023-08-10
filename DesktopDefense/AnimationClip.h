#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "Sprite.h"

using namespace std;
using namespace Engine;

namespace Engine
{
	class AnimationClip
	{
	public:
		AnimationClip() = default;

		AnimationClip(float _timeForSpriteChange, int _spriteCount, ...);

	private:
		// ���� ���� ��������Ʈ�� �Ϸķ� ��ġ�Ǿ� ������� �ִϸ��̼��Դϴ�.
		vector<Sprite*> m_Sprites;

		// �� �ִϸ��̼� Ŭ���� ������ Ư���Դϴ�. �� �ִϸ��̼ǿ� �ִ� ��������Ʈ�� � �ð� ���ݸ��� 
		// ��ü�Ǿ�� �ϴ����� ���� �����Դϴ�.
		float m_TimeForSpriteChange;
	public:
		inline vector<Sprite*> GetSprites() const { return m_Sprites; }

		inline float GetTimeForSpriteChange() const { return m_TimeForSpriteChange; }

		inline void SetTimeForSpriteChange(float _value) { m_TimeForSpriteChange = _value; }
	};
}
