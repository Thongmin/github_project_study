#include "Monster.h"

Monster::Monster()
{}
Monster::~Monster()
{}

void Monster::PrintInfo(int iWidth, int iHeight, int iLength)
{
	string strTmp = "======";
	strTmp += m_strName + "(" + to_string(m_iLevel) + "Lv)" + strTmp;
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + iLength);
	strTmp = "공격력 = " + to_string(m_iDamage) + "\t생명력 = " + to_string(m_iCurrentlyHP) + "/" + to_string(m_iMaxHP);
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + iLength + LINE_LENGTH_1);
	strTmp = "경험치 = " + to_string(m_iGetExp) + " Gold = " + to_string(m_iGold);
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + iLength + LINE_LENGTH_2);
	cout << endl;
}

void Monster::LoadData(ifstream* Load)
{
	*Load >> m_strName;
	Charactor::LoadData(Load);
}