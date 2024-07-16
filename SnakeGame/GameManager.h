#pragma once
#include "Mecro.h"
#include "MapManager.h"
#include "Block.h"
#include "Snake.h"

class GameManager
{
private:
	const int m_iMapWidth;
	int m_iMapHeight;
	int m_iCurClock;
	int m_iCheckSpeedClock;
	int m_iScore;
	int m_iSpeed;
	int m_iCheckDirection;
	char m_pcharBuf[256];
	Block m_Block;
	Snake m_Snake;
public:
	GameManager();
	~GameManager();

	void MainMenu();

private:
	void PrintMainMenu();
	void PrintGameInfo();
	void PlayGame();
	int ImpactCheck(char chDirection);
	void InitSnakeGameData();
	void PrintGameOver();
};

//���� : ��, �� �迭, ���� ���迭, ��
//�Լ� : ��ü ���� �Լ�, �� �׸��� �Լ�, ���� �÷��� �Լ�, �浹üũ�Լ�