#pragma once
#include "Mecro.h"
#include "MapDraw.h"

class Charactor
{
protected:

	string m_strName;
	int m_iDamage;		//공격력
	int m_iMaxHP;		//최대 HP
	int m_iCurrentlyHP;	//현재 HP
	int m_iLevel;		//레벨
	int m_iMaxExp;		//최대(레벨업에 필요한) 경험치
	int m_iCurrentlyExp;//현재 경험치
	int m_iGetExp;		//얻은(받는) 경험치
	int m_iGold;		//돈

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

// 공격력, 생명력, 경험치, 죽었을 때 주는 경험치, 소지금
