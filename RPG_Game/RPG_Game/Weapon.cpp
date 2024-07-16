#include "Weapon.h"

Weapon::Weapon()
{
	m_strType = "";
	m_strName = "";
	m_iDamage = 0;
	m_iGold = 0;
}

Weapon::~Weapon()
{}

void Weapon::LoadData(ifstream* Load, string strType)
{
	m_strType = strType;
	*Load >> m_strName;
	*Load >> m_iDamage;
	*Load >> m_iGold;
}

void Weapon::SaveData(ofstream* Save)
{
	*Save << "1 " << m_strType << " " << m_strName;
}

void Weapon::PrintInfo(int iWidth, int iHeight)
{
	string strTmp = "���� : ";
	strTmp.append(to_string(m_iGold));
	strTmp.append(" ���� Ÿ�� : ");
	strTmp.append(m_strType);
	MapDraw::DrawMidText(strTmp, iWidth, iHeight);
	strTmp = "�����̸� : ";
	strTmp.append(m_strName);
	strTmp.append(" ���ݷ� : ");
	strTmp.append(to_string(m_iDamage));
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + LINE_LENGTH_1);
	
}