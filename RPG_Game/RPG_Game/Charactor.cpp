#include "Charactor.h"

void Charactor::PrintInfo(int iWidth, int iHeight)
{
	string strTmp = "======";
	strTmp += m_strName + "(" + to_string(m_iLevel) + "Lv)" + strTmp;
	MapDraw::DrawMidText(strTmp, iWidth, (int)(iHeight * PERSENT_50));
	strTmp = "���ݷ� = " + to_string(m_iDamage) + "\t����� = " + to_string(m_iCurrentlyHP) + "/" + to_string(m_iMaxHP);
	MapDraw::DrawMidText(strTmp, iWidth, (int)(iHeight * PERSENT_50) + LINE_LENGTH_1);
	strTmp = "����ġ = " + to_string(m_iCurrentlyExp) + "/" + to_string(m_iMaxExp) + "\t\tGetEXP = " + to_string(m_iGetExp);
	MapDraw::DrawMidText(strTmp, iWidth, (int)(iHeight * PERSENT_50) + LINE_LENGTH_2);
	strTmp = "Gold = " + to_string(m_iGold);
	MapDraw::DrawMidText(strTmp, iWidth, (int)(iHeight * PERSENT_50) + LINE_LENGTH_3);
}

void Charactor::LoadData(ifstream* Load)
{
	*Load >> m_iDamage;
	*Load >> m_iCurrentlyHP;
	*Load >> m_iMaxHP;
	if (m_iCurrentlyHP < m_iMaxHP)
		system("pause>null");
	*Load >> m_iCurrentlyExp;
	*Load >> m_iMaxExp;
	*Load >> m_iGetExp;
	*Load >> m_iLevel;
	*Load >> m_iGold;
}

bool Charactor::CutOffHP(int iDamage)
{
	m_iCurrentlyHP -= iDamage;

	if (m_iCurrentlyHP <= 0)
		return true;

	return false;
}

void Charactor::GetandCheckExp(int iEXP)
{
	m_iCurrentlyExp += iEXP;

	while (1)
	{
		if (CompareEXP())
			LevelUP();
		else
			break;
	}
}

bool Charactor::CompareEXP()
{
	if (m_iCurrentlyExp >= m_iMaxExp)
		return true;
	else
		return false;
}

void Charactor::LevelUP()
{
	int iLastLevel	= m_iLevel;
	int iLastMaxExp	= m_iMaxExp;
	int iLastMaxHP	= m_iMaxHP;
	int iLastDamage = m_iDamage;
	
	m_iLevel++;
	//������
	
	m_iCurrentlyExp -= m_iMaxExp;
	if (m_iCurrentlyExp < 0)
		m_iCurrentlyExp = 0;
	m_iMaxExp = (int)((float)m_iMaxExp * 1.3);
	//������ �� ���� ����ġ ���ҿ� �ִ� ����ġ ���� (30%)
	
	m_iMaxHP = (int)((float)m_iMaxHP * 1.5);
	RecoveryHP();
	//������ �� �ִ� HP ����(50%)�� ü�� ȸ��

	m_iDamage = (int)((float)m_iDamage * 1.3);
	//������ �� �÷��̾� ���ݷ� (����x) ���� (30%)

	PrintLevelUP(iLastDamage, iLastLevel, iLastMaxExp, iLastMaxHP);

	/*
	m_iCurrentlyExp = 0;
	m_iMaxExp += (int)(m_iMaxExp * 0.3);

	int iIncrease = rand() % (LEVEL_UP_STAT_MAX + 1);
	m_iMaxHP += iIncrease;
	m_iCurrentlyHP = m_iMaxHP;

	iIncrease = rand() % (LEVEL_UP_STAT_MAX + 1);
	m_iDamage += iIncrease;
	*/
}

void Charactor::RecoveryHP()
{
	m_iCurrentlyHP = m_iMaxHP;
}

void Charactor::PrintLevelUP(int iLastDamage, int iLastLevel, int iLastMaxExp, int iLastMaxHP)
{
	system("cls");

	int iHeightPoint = (int)(MAP_HEIGHT_SIZE * PERSENT_30);

	string strTmp = GetName();
	strTmp.append(" ������!!!");
	YELLOW
	MapDraw::DrawMidText(strTmp, MAP_WIDTH_SIZE, iHeightPoint);
	strTmp = "���� : ";
	strTmp.append(to_string(iLastLevel));
	strTmp.append(" -> ");
	strTmp.append(to_string(m_iLevel));
	MapDraw::DrawMidText(strTmp, MAP_WIDTH_SIZE, iHeightPoint + 3);

	YELLOW
	strTmp = "���� �ʿ� ����ġ�� : ";
	strTmp.append(to_string(iLastMaxExp));
	strTmp.append(" -> ");
	strTmp.append(to_string(m_iMaxExp));
	MapDraw::DrawMidText(strTmp, MAP_WIDTH_SIZE, iHeightPoint + 5);

	YELLOW
	strTmp = "�ִ� HP : ";
	strTmp.append(to_string(iLastMaxHP));
	strTmp.append(" -> ");
	strTmp.append(to_string(m_iMaxHP));
	MapDraw::DrawMidText(strTmp, MAP_WIDTH_SIZE, iHeightPoint + 7);

	YELLOW
	strTmp = "���ݷ� : ";
	strTmp.append(to_string(iLastDamage));
	strTmp.append(" -> ");
	strTmp.append(to_string(m_iDamage));
	MapDraw::DrawMidText(strTmp, MAP_WIDTH_SIZE, iHeightPoint + 9);
		
	system("pause>null");
}