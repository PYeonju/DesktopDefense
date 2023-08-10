#pragma once
#include <vector>
#include <Windows.h>
#include <WinUser.h>
#include "DesktopDefense.h"
#define CELL_ABOUTBROKEN 5
#define CELL_TOTALLYBROKEN 9 // �� Ƚ�� �̻����� ������ ������ ������.

enum class CellState
{
	Clear, // �ƹ� �͵� �ƴϰ� ������ ����
	Registered, // Ư�� ���ο��� �������� ���� �� ������ �ִ� ����
	Broken, // ���� ����
};

/// <summary>
/// �� ���� �� �� ĭ�� ǥ���ϴ� Ŭ�����Դϴ�.
/// </summary>
class Cell
{
public:

	Cell();
	
	~Cell();

	CellState GetCellState();

	void SetCellState(CellState _state);

	int GetHittedCount();

	bool GetIsPaintedByAboutBroken();
	
	void SetIsPaintedByAboutBroken(bool _right);

	bool GetIsPaintedByBroken();

	void SetIsPaintedByBroken(bool _right);

	inline int GetIndexOfBrokenSprite() const { return m_IndexOfBrokenSprite; }

	inline void SetIndexOfBrokenSprite(int _index) { m_IndexOfBrokenSprite = _index; }

	void PlusHittedCount(); // �� ���� ġ�� �ִ� Miner�� �� ��ü�� ����. �� �� ĥ������ ���̳ʿ��� �� �� ȣ��

	void CellTick(); // ���� ��ƽ�� �����ϴ� ���̴�.

private:

	// ���� Cell�� � �������� ��Ÿ���� ��������Դϴ�. 
	CellState m_CellState;
	// Cell�� ���ο��� �� ȸ �¾Ҵ��� ��Ÿ���� ��������Դϴ�. �� ������ m_CellState ������ �� Tick���� �б��մϴ�.
	int m_HittedCount;

	bool m_IsPaintedByAboutBroken; // �� Cell�� ���� �� ����Ÿ�� ��ĥ �Ǿ����� ..?

	bool m_IsPaintedByBroken;
	
	int m_IndexOfBrokenSprite; // AboutBroken �� �� �� �ε����� ��������Ʈ�� ����� �����ߴ��� ����ϰ� Broken ��Ȳ�� �� �Ȱ��� �̹����� �̽��ϴ�.
};

/// <summary>
/// ������ ����Ǵ� �� ��ü�� �Ѱ��ϴ� Ŭ�����Դϴ�.
/// </summary>
class Map
{
public:

	Map(HWND _hWnd, int _pixelX, int _pixelY); // ����� Windows�� �ڵ�� ����, ���� �ȼ� ���� �޾� ���� �����Ѵ�.

	~Map();

	void MapTick_Logic(); // ���� ������Ʈ�� ���� ��� ������ ������ �������� ó���Ѵ�. (ȭ���� �������� �� �������� Check)

	void MapTick_Render(); // ���� ���� ������Ʈ�� ������ ���� ���� ��Ȳ�� ȭ�� �� ����մϴ�.

// private:

	Cell*** m_Map; // �׸���� ���� ǥ���սô�.

	Engine::Sprite* m_BlueScreen; // ��罺ũ�� �̹���

	Engine::Sprite* m_Desktop; // ĸ���� ����ũž �̹���

	// ������ �Ϻ� ���� (3�� ����), ������ ���� (5�� ����) �̹��� Pair, Vector�� ����
	std::vector<pair<Engine::Sprite*, Engine::Sprite*>> m_BrokenSprites; // ����Ÿ �̹������� ��Ƴ��� ����. �������� �̹����� ���⼭ �̾Ƽ� m_Desktop�� ���δ�. (TransparentBlt(RGB(0,255,0)))

	std::vector<Engine::Sprite*> m_RealBrokenAnimation;

	int m_BrokenCellCount;

	int m_MaxY;

	int m_MaxX;

	static const int m_PixelPerGrid = 40;
};

// GameWorld�� ���� ���� ..?
// 
// ������ ũ������Ʈ �� �� Map �����ϸ鼭 ��罺ũ��, ����ȭ��, ���� �̹��� ���� �ε�
// MapTick���� ȭ�� �߿�����������