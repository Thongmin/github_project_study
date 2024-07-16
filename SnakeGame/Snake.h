#pragma once
#include "Mecro.h"
#include "MapManager.h"

class Snake
{
private:
	std::string m_strSnakeHeadShape;
	std::string m_strSnakeTailShape;
	char m_chSnakeDirection;
	std::list<StructurePoint> m_plistSnakeB;
public:
	Snake();
	~Snake();

	void CreateSnake(int iWidth, int iHeight);
	void MoveSnake();
	bool ImpactCheckSnakeBody(int ix, int iy);
	void ChangeDirection(char chDirection);
	void DrawSnake();
	int GetSnakeHeadx();
	int GetSnakeHeady();
	void InitVariableData();
	void InitSnake();

	inline char GetDirection()
	{
		return m_chSnakeDirection;
	}
};

//���� : Life, �������, �Ӹ��� ����
//�Լ� : �켳��, ���� �����, ���� �̵�, �Ӹ� �̵�, �� �׸���, �Է�, �� ����