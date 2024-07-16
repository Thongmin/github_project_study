#pragma once
#include "Mecro.h"
#include "MapManager.h"

class Block
{
private:
	std::string m_strBlock;
	std::string m_strHeart;
	int m_iCreateHeartClock;
	std::list<StructurePoint> m_plistBlock;
	std::list<StructurePoint> m_plistHeart;

public:
	Block();
	~Block();

	void CreateBlock(int iWidth, int iHeight);
	void CreateHeart(int iWidth, int iHeight, int iCurClock);
	void DrawBlock();
	bool ImpactCheckBlock(int ix, int iy);
	bool ImpactCheckHeart(int ix, int iy);
	void InitBlock();
	void InitHeart();
	bool EraseHeart(int ix, int iy, int iCheckDirection);
};

//���� : ��, ����, ��Ӹ�, �첿��, ����� ����, �� ���, ��ǥ
//�Լ� : ����浹üũ, ��ǥ����, �� �׸���, ��� �� �����, Ʋ�� �� �����, �� ����.