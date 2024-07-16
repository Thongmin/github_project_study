#include "Player.h"

Player::Player()
{
	m_Weapon		= NULL;
	m_iDamage		= NULL;
	m_iGetExp		= NULL;
	m_strName		= "";
	m_iGold			= NULL;
	m_iLevel		= NULL;
	m_iMaxExp		= NULL;
	m_iCurrentlyExp = NULL;
	m_iCurrentlyHP	= NULL;
}

Player::~Player()
{}

void Player::PrintInfo(int iWidth, int iHeight)
{
	string strTmp = "======";
	strTmp += m_strName + "(" + to_string(m_iLevel) + "Lv)" + strTmp;
	MapDraw::DrawMidText(strTmp, iWidth, iHeight);
	strTmp = "공격력 = " + to_string(m_iDamage) + " 생명력 = " + to_string(m_iCurrentlyHP) + "/" + to_string(m_iMaxHP);
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + LINE_LENGTH_1);
	strTmp = "경험치 = " + to_string(m_iCurrentlyExp) + "/" + to_string(m_iMaxExp) + " Gold = " + to_string(m_iGold);
	MapDraw::DrawMidText(strTmp, iWidth, iHeight + LINE_LENGTH_2);
	
	if (m_Weapon != NULL)
	{
		strTmp = "무기타입 : ";
		strTmp.append(m_Weapon->GetType());
		strTmp.append(" 무기 이름 : ");
		strTmp.append(m_Weapon->GetName());
		MapDraw::DrawMidText(strTmp, iWidth, iHeight + LINE_LENGTH_3);
		strTmp = "무기공격력 : ";
		strTmp.append(to_string(m_Weapon->GetDamage()));
		MapDraw::DrawMidText(strTmp, iWidth, iHeight + LINE_LENGTH_4);
	}
}

void Player::LoadData(ifstream* Load, map<string, vector<Weapon>>* LoadWeapon)
{
	if ("" == m_strName)
		*Load >> m_strName;

	Charactor::LoadData(Load);

	int iCheckWeapon = 0;
	*Load >> iCheckWeapon;

	if (iCheckWeapon)
	{
		string strWeaponType = "";
		string strWeaponName = "";

		*Load >> strWeaponType;
		*Load >> strWeaponName;

		for (int i = 0; i < (*LoadWeapon)[strWeaponType].size(); i++)
		{
			if ((*LoadWeapon)[strWeaponType].at(i).GetName() == strWeaponName)
			{
				m_Weapon = &(*LoadWeapon)[strWeaponType].at(i);
				break;
			}
		}
	}
}

int Player::GetDamage()
{
	if (m_Weapon != NULL)
		return m_iDamage + m_Weapon->GetDamage();
	else
		return m_iDamage;
}

void Player::SaveData(ofstream* Save)
{
	*Save << m_strName << " " << m_iDamage << " " << m_iCurrentlyHP << " " << m_iMaxHP << " " << m_iCurrentlyExp << " " << m_iMaxExp << " " << m_iGetExp << " " << m_iLevel << " " << m_iGold << endl;

	if (m_Weapon != NULL)
		m_Weapon->SaveData(Save);
	else
		*Save << 0;
}

void Player::Reset()
{
	m_strName		= "";
	m_iDamage		= NULL;
	m_iCurrentlyHP	= NULL;
	m_iMaxHP		= NULL;
	m_iCurrentlyExp = NULL;
	m_iMaxExp		= NULL;
	m_iGetExp		= NULL;
	m_iLevel		= NULL;
	m_iGold			= NULL;
	m_Weapon		= NULL;
}
