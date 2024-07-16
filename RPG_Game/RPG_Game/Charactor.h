#pragma once
#include "Mecro.h"
#include "MapDraw.h"

class Charactor
{
protected:

	string m_strName;
	int m_iDamage;		//���ݷ�
	int m_iMaxHP;		//�ִ� HP
	int m_iCurrentlyHP;	//���� HP
	int m_iLevel;		//����
	int m_iMaxExp;		//�ִ�(�������� �ʿ���) ����ġ
	int m_iCurrentlyExp;//���� ����ġ
	int m_iGetExp;		//����(�޴�) ����ġ
	int m_iGold;		//��

public:

	void PrintInfo(int iWidth, int iHeight);
	void LoadData(ifstream* Load);
	bool CutOffHP(int iDamage);
	void GetandCheckExp(int iEXP);
	bool CompareEXP();
	void LevelUP();
	void RecoveryHP();
	void PrintLevelUP(int iLastDamage, int iLastLevel, int iLastMaxExp, int iLastMaxHP);

	int GetDamage()
	{
		return m_iDamage;
	}
	string GetName()
	{
		return m_strName;
	}
	int GetEXP()
	{
		return m_iGetExp;
	}
	int GetGold()
	{
		return m_iGold;
	}
};

// ���ݷ�, �����, ����ġ, �׾��� �� �ִ� ����ġ, ������
