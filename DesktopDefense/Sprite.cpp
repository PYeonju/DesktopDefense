#include "Sprite.h"

#include "GameInstanceBase.h"

using namespace Engine;

// �ڵ� ���
extern HDC g_hdc;

Sprite::Sprite(HDC _hBitmapDC, HBITMAP _hBitmap, Vector2D _pivot, Vector2D _scaler)
	: m_SpriteDC(_hBitmapDC),
	m_HandleBitmap(_hBitmap),
	m_Pivot(_pivot),
	m_Scaler(_scaler)
{
	// �ش��ϴ� ��������Ʈ�� ������ ��Ʈ�� �̹����� ������ �����ɴϴ�.
	BITMAP _bitmapInfo;
	GetObject(_hBitmap, sizeof(BITMAP), &_bitmapInfo);

	m_BitmapInfo = _bitmapInfo;
}

Sprite::~Sprite()
{
	// �ش� ��������Ʈ�� ������ �ִ� �޸� DC�� �����մϴ�.
	DeleteDC(m_SpriteDC);
	// �ش� ��������Ʈ�� ������ �ִ� ��Ʈ�� �̹����� �����մϴ�.
	DeleteObject(m_HandleBitmap);
}

Sprite* Sprite::LoadSprite(const TCHAR* _fileName, Vector2D _pivot, Vector2D _scaler)
{
	return LoadSprite(GameInstanceBase::GetInstance()->GetGeneralDC(), _fileName, _pivot, _scaler);
}

std::map<std::wstring, HBITMAP> LoadedBitmaps;
std::map<std::wstring, HDC> LoadedBitmapDCs;
Sprite* Sprite::LoadSprite(HDC _hDC, const TCHAR* _fileName, Vector2D _pivot, Vector2D _scaler)
{
	// ����, ���� �Ű��� ���� ���� ��� ��ġ�ϴ� ������ �� ���̶� �ҷ��� �� �ִٸ�,
	// ������ �ҷ����� �ڵ�� �����ϰ�, �̹� �ҷ��°� �������� �̰���.

	HDC _hBitmapDC;
	// Bitmap �̹����� ����� DC ���� �غ� (�޸� ����)

	HBITMAP _hBitmap;

	std::wstring _fileNameString = _fileName;

	auto _loadedBitmapIter = LoadedBitmaps.find(_fileNameString);
	if (_loadedBitmapIter == LoadedBitmaps.end())
	{
		_hBitmapDC = CreateCompatibleDC(_hDC);
		_hBitmap = (HBITMAP)LoadImage(nullptr, _fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(_hBitmapDC, _hBitmap); // m_TextureDC�� m_BitmapInfo �����ֱ�

		LoadedBitmaps.insert({ _fileNameString, _hBitmap });		
		LoadedBitmapDCs.insert({ _fileNameString, _hBitmapDC });
	}
	else
	{
		_hBitmapDC = LoadedBitmapDCs.at(_fileNameString);
		_hBitmap = LoadedBitmaps.at(_fileName);
	}

	if (_hBitmap == nullptr)
	{
		// �̹��� �ε� ����
		// �ε� ���п� ���� ����ó���� �ǽ��մϴ�.
		return nullptr;
	}

	Sprite* _newSprite = new Sprite(_hBitmapDC, _hBitmap, _pivot, _scaler);

	return _newSprite;
}
