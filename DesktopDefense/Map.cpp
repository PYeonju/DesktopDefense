#include "Map.h"
#include "CircleCollider.h"
#include "Audio.h"

extern Audio* _audio;
extern AudioClip*_IngameBGM;

Cell::Cell()
{
	m_CellState = CellState::Clear;

	m_HittedCount = 0;
	
	m_IsPaintedByAboutBroken = false;
	
	m_IsPaintedByBroken = false;

	m_IndexOfBrokenSprite = 0;
}

Cell::~Cell()
{

}

CellState Cell::GetCellState()
{
	return this->m_CellState;
}

void Cell::SetCellState(CellState _state)
{
	m_CellState = _state;

	return;
}

int Cell::GetHittedCount()
{
	return this->m_HittedCount;
}

bool Cell::GetIsPaintedByAboutBroken()
{
	return this->m_IsPaintedByAboutBroken;
}

void Cell::SetIsPaintedByAboutBroken(bool _right)
{
	this->m_IsPaintedByAboutBroken = _right;
}

bool Cell::GetIsPaintedByBroken()
{
	return this->m_IsPaintedByBroken;
}

void Cell::SetIsPaintedByBroken(bool _right)
{
	this->m_IsPaintedByBroken = _right;
}

void Cell::PlusHittedCount()
{
	m_HittedCount++;

	return;
}

void Cell::CellTick()
{
	// ���¸� üũ�Ѵ�.
	// üũ�� ���¿� ���� Screen�� �ش��ϴ� �̹����� �������� ��û�Ѵ�.
	// MapTick()���� ����˴ϴ�.

	CellState _nowCellState = m_CellState;

	switch (_nowCellState)
	{
		case CellState::Clear:
		{
			// �� ������ ..?
			break;
		}

		case CellState::Registered:
		{
			if (this->m_HittedCount >= CELL_TOTALLYBROKEN)
			{
				this->m_CellState = CellState::Broken;
			}

			break;
		}

		case CellState::Broken:
		{
			// �� ������ ..?
			break;
		}

		default:
			break;
	}
}

// ���� �����մϴ�.
// Map(GetSystemMetrics(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); �� ȣ��
Map::Map(HWND _hWnd, int _pixelX, int _pixelY)
{
	// �� ���� ���� (10�ȼ����� 1�׸���)
	m_MaxY = _pixelY / Map::m_PixelPerGrid;

	m_MaxX = _pixelX / Map::m_PixelPerGrid;

	m_Map = new Cell** [m_MaxY];

	for (int i = 0; i < m_MaxY; i++)
		m_Map[i] = new Cell* [m_MaxX];

	for (int y = 0; y < m_MaxY; y++)
	{
		for (int x = 0; x < m_MaxX; x++)
		{
			m_Map[y][x] = new Cell();
		}
	}

	m_BrokenCellCount = 0;
	
	// �ʿ��� �����ϴ� ��������Ʈ�� �ε��Ѵ�. (����ũž, ��罺ũ��, ���� ����� ����Ÿ)
	HDC _hScrDC, _hMemDC;
	HBITMAP _hBitmap;

	_hScrDC = CreateDCA("DISPLAY", NULL, NULL, NULL);
	_hMemDC = CreateCompatibleDC(_hScrDC);
	_hBitmap = CreateCompatibleBitmap(_hScrDC, _pixelX, _pixelY);
	SelectObject(_hMemDC, _hBitmap);
	BitBlt(_hMemDC, 0, 0, _pixelX, _pixelY, _hScrDC, 0, 0, SRCCOPY);

	// ����ũž �̹��� �ε�
	m_Desktop = new Engine::Sprite(_hMemDC, _hBitmap, Engine::Vector2D(0.f, 0.f));

	DeleteDC(_hScrDC);

	HDC _hDC = GetDC(_hWnd);

	// ��罺ũ���� ������ ����� �̹��� �ε�

	m_BlueScreen = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/BLUESCREEN16by9.bmp"), Engine::Vector2D(0.f, 0.f));

	Engine::Vector2D _newScaler = Engine::Vector2D((double)_pixelX / (double)m_BlueScreen->GetBitmapInfo().bmWidth, (double)_pixelY / (double)m_BlueScreen->GetBitmapInfo().bmHeight);

	m_BlueScreen->SetScaler(_newScaler);

	// ������ ����� �̹��� �ε� (for������ �ص� ������ �׳� ���������� �ϰ� �; ��) => ���߿� ��� �ٲ��ٵ� ��������
	Sprite* _zeroOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/0-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _zeroTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/0-2.bmp"), Engine::Vector2D(0.f, 0.f));

	Engine::Vector2D _scalerForBrokenSprite = Engine::Vector2D((double)m_PixelPerGrid / (double)_zeroOne->GetBitmapInfo().bmWidth, (double)m_PixelPerGrid / (double)_zeroOne->GetBitmapInfo().bmHeight);

	_zeroOne->SetScaler(_scalerForBrokenSprite);

	_zeroTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _zeroOne, _zeroTwo });

	Sprite* _oneOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/1-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _oneTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/1-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_oneOne->SetScaler(_scalerForBrokenSprite);

	_oneTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _oneOne, _oneTwo });

	Sprite* _TwoOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/2-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _TwoTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/2-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_TwoOne->SetScaler(_scalerForBrokenSprite);

	_TwoTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _TwoOne, _TwoTwo });

	Sprite* _ThreeOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/3-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _ThreeTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/3-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_ThreeOne->SetScaler(_scalerForBrokenSprite);

	_ThreeTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _ThreeOne, _ThreeTwo });

	Sprite* _FourOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/4-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _FourTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/4-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_FourOne->SetScaler(_scalerForBrokenSprite);

	_FourTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _FourOne, _FourTwo });

	Sprite* _FiveOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/5-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _FiveTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/5-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_FiveOne->SetScaler(_scalerForBrokenSprite);

	_FiveTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _FiveOne, _FiveTwo });

	Sprite* _SixOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/6-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _SixTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/6-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_SixOne->SetScaler(_scalerForBrokenSprite);

	_SixTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _SixOne, _SixTwo });

	Sprite* _SevenOne = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/7-1.bmp"), Engine::Vector2D(0.f, 0.f));

	Sprite* _SevenTwo = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/7-2.bmp"), Engine::Vector2D(0.f, 0.f));

	_SevenOne->SetScaler(_scalerForBrokenSprite);

	_SevenTwo->SetScaler(_scalerForBrokenSprite);

	m_BrokenSprites.push_back({ _SevenOne, _SevenTwo });

	Sprite* _RealBroken = Engine::Sprite::LoadSprite(_hDC, TEXT("Sprites/Broken/REALBROKEN.bmp"), Engine::Vector2D(0.f, 0.f));
	
	Vector2D _overScaler = Vector2D((double)_pixelX / _RealBroken->GetBitmapInfo().bmWidth, (double)_pixelY / _RealBroken->GetBitmapInfo().bmHeight);

	_RealBroken->SetScaler(_overScaler);

	m_RealBrokenAnimation.push_back(_RealBroken);
}

// ���� �����մϴ�. �������� �Ҵ�Ǿ� �ִ� ��� �ڷ���� �����մϴ�.
Map::~Map()
{
	for (int i = 0; i < m_MaxY; i++)
		delete [] m_Map[i];

	delete[] m_Map;

	for (int i = 0; i < m_BrokenSprites.size(); i++)
	{
		delete m_BrokenSprites[i].first;
		delete m_BrokenSprites[i].second;
	}

	delete m_BlueScreen;
	delete m_Desktop;
}

void Map::MapTick_Logic()
{	
	for (int y = 0; y < m_MaxY; y++)
	{
		for (int x = 0; x < m_MaxX; x++)
		{
			if (m_Map[y][x]->GetCellState() != CellState::Broken) // �̹� Broken�� Cell�̶�� �� �̻� ������Ʈ�� ��Ȳ�� ����.
			{
				m_Map[y][x]->CellTick(); // ���� ���� ������Ʈ = ����ũž ȭ�� ������Ʈ
			}
		}
	}

	if (m_BrokenCellCount >= (int)m_MaxX * m_MaxY * 0.3f) // ���� ������ Cell�� ������
	{
		// ���� �����Ű�� .. 

		// ����� ��ž

		Audio_Stop(_IngameBGM);

		Screen::GetInstance()->PrintSpriteToScreenNow(m_RealBrokenAnimation[0], Vector2D{ 0, 0 }, RGB(255, 0, 255));

		Sleep(1000);
		
		Screen::GetInstance()->PrintSpriteToScreenNow(m_BlueScreen, Vector2D{ 0, 0 }); // ��罺ũ�� ȭ�鿡 ���� �ɱ�

		Screen::GetInstance()->PrintSpriteToScreenNow(m_RealBrokenAnimation[0], Vector2D{ 0, 0 }, RGB(255, 0, 255));

		while (true)
		{
			Sleep(100000);
		}

		//Screen::GetInstance()->PrintSpriteToScreenNow(m_RealBrokenAnimation[0], Vector2D{ 0, 0 });
		
		// �������� ��û�ؼ� �� �����ϰ� ����â, ��罺ũ�� -> ��
	}
}

void Map::MapTick_Render()
{
	Screen::GetInstance()->PrintSprite(this->m_BlueScreen, Vector2D{0, 0});
	
	for (int y = 0; y < m_MaxY; y++)
	{
		for (int x = 0; x < m_MaxX; x++)
		{
			if (!m_Map[y][x]->GetIsPaintedByAboutBroken() && m_Map[y][x]->GetCellState() == CellState::Registered && m_Map[y][x]->GetHittedCount() >= CELL_ABOUTBROKEN)
			{
				m_Map[y][x]->SetIsPaintedByAboutBroken(true); // AboutBroken �̹��� ����Ͽ��ٴ� Flag On
				// �ݰ� �̹����� �������� �̾Ƽ� DesktopDC�� �׸���. (PrintSpriteTo �Լ��� screen ��ǥ�� ���ϴ�)
				m_Map[y][x]->SetIndexOfBrokenSprite(rand() % m_BrokenSprites.size()); // �غ�� �ı� �̹��� �� �������� �ϳ��� �̴´�.
				Screen::GetInstance()->PrintSpriteTo(m_Desktop->GetSpriteDC(), m_BrokenSprites[m_Map[y][x]->GetIndexOfBrokenSprite()].first, m_PixelPerGrid * x, m_PixelPerGrid * y, RGB(0, 255, 0));
			}
			else if (!m_Map[y][x]->GetIsPaintedByBroken() && m_Map[y][x]->GetCellState() == CellState::Broken && m_Map[y][x]->GetHittedCount()>= CELL_TOTALLYBROKEN)
			{
				m_Map[y][x]->SetIsPaintedByBroken(true); // TotallyBroken �̹����� ����Ͽ��ٴ� Flag On
;				Screen::GetInstance()->PrintSpriteTo(m_Desktop->GetSpriteDC(), m_BrokenSprites[m_Map[y][x]->GetIndexOfBrokenSprite()].second, m_PixelPerGrid * x, m_PixelPerGrid * y, RGB(0, 255, 0));
				m_BrokenCellCount++;
			}
		}
	}

	Screen::GetInstance()->PrintSprite(this->m_Desktop, Vector2D{0, 0});
}

// �Ϲ� (���⼭ Map�� ���� ������ �������� ó���Ѵ�)
// ���� 
// ������ 

// ���� ���� ���� Ÿ���� ���ϰ� ���� ���� �˰���
// CellState::Clear�� Cell�� ���� ������ m_Map���� rand(m_MaxX -1, m_MaxY -1) ..
// ã���� m_Map[y][x]->SetCellState(CellState::Registered)�� �������ְ� �� ������ �̵�
// �� ��ǥ (�ȼ� ��ǥ)�� ���� x * 10 + 5 , y * 10 + 5�� (�»�� 0,0 / ���ϴ� m_Map->SM_CXSCREEN, m_Map->SM_CYSCREEN)
// ã�Ƽ� ���� ��� ���� '��̷� ���� ��� Sprite'�� ���� �� g_Map->m_Map[y][x] (�����ϱ�� ������ Cell)->PlusHittedCount() �� �� ȣ��
// ���� MinerTick���� ���� ������ Cell�� Breaked�� �ٲ���ٸ� ���� ���� ���� ��