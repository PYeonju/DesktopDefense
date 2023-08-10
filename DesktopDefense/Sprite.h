#pragma once

#include <map>
#include <Windows.h>
#include <vector>

#include "Vector2D.h"
#include <tchar.h>
#include <string>

namespace Engine
{

	class Sprite
	{
	public:
		// �������Դϴ�.
		Sprite(HDC _hBitmapDC, HBITMAP _hBitmap, Vector2D _pivot = Vector2D::Center, Vector2D _scaler = Vector2D(1.f, 1.f));
		// �Ҹ����Դϴ�.
		~Sprite();

	private:
		// ��������Ʈ�� ������ �ִ� �޸� DC�� �ڵ��Դϴ�.
		HDC m_SpriteDC;
		// ��������Ʈ�� ������ ��Ʈ�� �̹����� �ڵ��Դϴ�.
		HBITMAP m_HandleBitmap;
		// ��������Ʈ�� ������ ��Ʈ�� �̹����� ������ ������ �ִ� ������Ʈ�Դϴ�.
		BITMAP m_BitmapInfo;

		// ��������Ʈ�� �Ǻ��Դϴ�.
		Vector2D m_Pivot;

		/// <summary>
		/// ��������Ʈ�� ǥ���� �� ��� ���� ũ��� �ٲپ� ����� �������� ���� �����Դϴ�.
		///	�� ���� 1�̶�� ���� ũ���, 0.5�� ���ݿ� �ش��ϴ� ũ��� ����մϴ�. ��, �� ������ ���� X��, Y�࿡ �����մϴ�.
		/// </summary>
		Vector2D m_Scaler;

	public:
		inline HDC GetSpriteDC() const { return m_SpriteDC; }

		inline BITMAP GetBitmapInfo() const { return m_BitmapInfo; }

		inline Vector2D GetPivot() const { return m_Pivot; }

		inline void SetPivot(Vector2D _pivot) { this->m_Pivot = _pivot; }

		inline Vector2D GetScaler() const { return m_Scaler; }

		inline void SetScaler(Vector2D _value) { m_Scaler = _value; }

	private:
		

	public:
		static Sprite* LoadSprite(const TCHAR* _fileName, Vector2D _pivot = Vector2D::Center, Vector2D _scaler = Vector2D(1.f, 1.f));

		static Sprite* LoadSprite(HDC _hdc, const TCHAR* _fileName, Vector2D _pivot = Vector2D::Center, Vector2D _scaler = Vector2D(1.f, 1.f));
	};
}