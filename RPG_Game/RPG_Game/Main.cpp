#pragma once
#include "GameManager.h"

void main()
{
	srand((unsigned)time(NULL)); //Ÿ�� ���� �õ� ���� ����.

	GameManager GM; //GM ��ü ����
	GM.MainMenu(); // GM ��ü�� MainMenu �Լ� ȣ��
}