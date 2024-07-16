#include "GameManager.h"

GameManager::GameManager()
	: m_iWidth(MAP_WIDTH_SIZE),
	m_iHeight(MAP_HEIGHT_SIZE)
{
	sprintf(m_charBuf, "mode con: cols=%d lines=%d", TWO_TIMES(m_iWidth), m_iHeight + MAP_SURPLUS_LINE);
	system(m_charBuf);

	ifstream Load;
	Load.open("DefaultMonster.txt");

	if (Load.is_open())
	{
		int iMonsterCount = 0;
		Load >> iMonsterCount;

		m_Monster = new Monster[iMonsterCount];

		for (int i = 0; i < iMonsterCount; i++)
			m_Monster[i].LoadData(&Load);

		Load.close();
	}

	LoadWeaponData();
}

void GameManager::LoadWeaponData()
{
	Weapon Wp;
	
	ifstream Load;
	Load.open("WeaponList.txt");

	if(Load.is_open())
	{
		while (!Load.eof())
		{
			string strWeaponType;
			Load >> strWeaponType;

			Wp.LoadData(&Load, strWeaponType);

			WeaponMap[strWeaponType].push_back(Wp);
		}

		Load.close();
	}
}

void GameManager::MainMenu()
{
	while (1)
	{
		system("cls");

		WindowSet();
		PrintMainMenu();

			switch (MapDraw::MenuSelectCursor(MENU_COUNT_MAIN, LINE_LENGTH_2, (int)(m_iWidth * PERSENT_30) + LINE_LENGTH_2, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_2))
			{
			case MAIN_MENU_NEW_GAME:
				NewGame();
				Play();
				break;
			case MAIN_MENU_LOAD_GAME:
				SaveorLoadGame(LOAD);
				break;
			case MAIN_MENU_EXIT_GAME:
				return;
			}
	}
}

void GameManager::PrintMainMenu()
{
	MapDraw::DrawMidText("�١� DonGeonRPG �ڡ�", m_iWidth, (int)(m_iHeight * PERSENT_40));
	MapDraw::DrawMidText("New Game", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_2);
	MapDraw::DrawMidText("Load Game", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_4);
	MapDraw::DrawMidText("Game Exit", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_6);
}

void GameManager::NewGame()
{
	string strPlayerName;

	while (1)
	{
		system("cls");

		WindowSet();
		MapDraw::DrawMidText("Player �̸� �Է� : ", m_iWidth, (int)(m_iHeight * PERSENT_50));

		cin >> strPlayerName;
		m_Player.SetName(strPlayerName);

		ifstream Load;
		Load.open("DefaultPlayer.txt");

		if (Load.is_open())
		{
			m_Player.LoadData(&Load, &WeaponMap);
			Load.close();
		}

		break;
	}
}

void GameManager::Play()
{
	while (1)
	{
		system("cls");
		
		WindowSet();	
		PrintPlayMenu();

		switch (MapDraw::MenuSelectCursor(MENU_COUNT_GAME, LINE_LENGTH_2, (int)(m_iWidth * PERSENT_30) + LINE_LENGTH_1, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_2))
		{
		case PLAY_MENU_DONGEON:
			if (DongeonMenu())
			{
				RED
					MapDraw::DrawMidText("Game Over", m_iWidth, (int)(m_iHeight * PERSENT_50));
				m_Player.Reset();
				system("pause>null");
				ORIGINAL
					return;
			}
			break;
		case PLAY_MENU_PLAYER_INFO:
			system("cls"); 
			WindowSet();
			YELLOW
				m_Player.PrintInfo(m_iWidth, (int)(m_iHeight * PERSENT_40));
			ORIGINAL
			system("pause>null");
			break;
		case PLAY_MENU_MONSTER_INFO:
			system("cls");
			WindowSet();

			for (int i = 0; i < MONSTER_NAME_MAX_COUNT; i++)
				m_Monster[i].PrintInfo(m_iWidth, (int)(m_iHeight * PERSENT_10), i * 4);

			system("pause>null");
			break;
		case PLAY_MENU_WEAPON_SHOP:
			WeaponShopMenu();
			break;
		case PLAY_MENU_SAVE:
			SaveorLoadGame(SAVE);
			break;
		case PLAY_MENU_EXIT:
			m_Player.Reset();
			return;
		}
	}
}

void GameManager::PrintPlayMenu()
{
	MapDraw::DrawMidText("�١� Menu �ڡ�", m_iWidth, (int)(m_iHeight * PERSENT_30));
	MapDraw::DrawMidText("Dongeon", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_2);
	MapDraw::DrawMidText("Player Info", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_4);
	MapDraw::DrawMidText("Monster Info", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_6);
	MapDraw::DrawMidText("Weapon Shop", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_8);
	MapDraw::DrawMidText("Save", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_10);
	MapDraw::DrawMidText("Exit", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_12);
}

void GameManager::SaveorLoadGame(bool bLoad)
{
	int iSelect = 0;

	while (1)
	{
		system("cls");

		WindowSet();
		PrintSaveorLoadGame();
		iSelect = MapDraw::MenuSelectCursor(MENU_COUNT_SAVE_OR_LOAD, LINE_LENGTH_2, 8, 6);

		switch (iSelect)
		{
		case FILE_1:
		case FILE_2:
		case FILE_3:
		case FILE_4:
		case FILE_5:
		case FILE_6:
		case FILE_7:
		case FILE_8:
		case FILE_9:
		case FILE_10:
			if (bLoad)
			{
				if (LoadGame(iSelect + 1))
				{
					Play();
					return;
				}
				else
					break;
			}
			else
			{
				SaveGame(iSelect + 1);
				return;
			}
		case FILE_EXIT:
			return;
		}
	}
}

void GameManager::PrintSaveorLoadGame()
{
	int x = 0;

	GREEN
		for (int i = 1; i <= MENU_COUNT_SAVE_OR_LOAD; i++)
		{
			string str = "";
			str.append(to_string(i));

			if (i != MENU_COUNT_SAVE_OR_LOAD)
			{
				ifstream Load;
				string strLoad = "SavePlayer";
				strLoad.append(to_string(i));
				strLoad += ".txt";
				Load.open(strLoad);

				if (Load.is_open())
				{
					str.append("������ : (���Ͽ��� : O)");
					Load.close();
				}
				else
					str.append("������ : (���Ͽ��� : X)");
			}
			else
				str.append(". ���ư���");

			MapDraw::TextDraw(str, (int)(m_iWidth * PERSENT_70), 6 + x);
			x += LINE_LENGTH_2;
		}
}

bool GameManager::LoadGame(int iFileNum)
{
	system("cls");

	ifstream Load;
	string strLFName = "SavePlayer" + to_string(iFileNum) + ".txt";
	Load.open(strLFName);

	if (Load.is_open())
	{
		m_Player.LoadData(&Load, &WeaponMap);
		WindowSet();
		MapDraw::DrawMidText("Load �Ϸ�", m_iWidth, (int)(m_iHeight * PERSENT_50));

		system("pause>null");
		return true;
	}
	else
	{
		WindowSet();
		MapDraw::DrawMidText("�ش� ������ �����ϴ�.", m_iWidth, (int)(m_iHeight * PERSENT_50));
		MapDraw::DrawMidText("    ����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .", m_iWidth, (int)(m_iHeight * PERSENT_50) + LINE_LENGTH_1);

		system("pause>null");
		return false;
	}
	Load.close();

	return false;
}

void GameManager::SaveGame(int iFileNum)
{
	system("cls");

	ofstream Save;
	string strSFName = "SavePlayer" + to_string(iFileNum) + ".txt";
	
	Save.open(strSFName, ios::out);
	m_Player.SaveData(&Save);

	MapDraw::DrawMidText("Save �Ϸ�", m_iWidth, (int)(m_iHeight * PERSENT_50));
	Save.close();
	system("pause>null");
}

bool GameManager::DongeonMenu()
{
	system("cls");
	WindowSet();
	PrintDongeonMenu();
	bool bIsDead = false;

	switch (MapDraw::MenuSelectCursor(MENU_COUNT_DONGEON, LINE_LENGTH_2, (int)(m_iWidth * PERSENT_20) + LINE_LENGTH_1, (int)(m_iHeight * PERSENT_30)))
	{
	case MONSTER_NAME_GOBLIN:
		bIsDead = DongeonPlay(MONSTER_NAME_GOBLIN);
		break;
	case MONSTER_NAME_ORC:
		bIsDead = DongeonPlay(MONSTER_NAME_ORC);
		break;
	case MONSTER_NAME_WEREWOLF:
		bIsDead = DongeonPlay(MONSTER_NAME_WEREWOLF);
		break;
	case MONSTER_NAME_OGRE:
		bIsDead = DongeonPlay(MONSTER_NAME_OGRE);
		break;
	case MONSTER_NAME_SKELETON_ARCHER:
		bIsDead = DongeonPlay(MONSTER_NAME_SKELETON_ARCHER);
		break;
	case MONSTER_NAME_LICH:
		bIsDead = DongeonPlay(MONSTER_NAME_LICH);
		break;
	case DONGEON_MENU_EXIT:
		return bIsDead;
	}
}

void GameManager::PrintDongeonMenu()
{
	MapDraw::DrawMidText("=====���� �Ա�=====", m_iWidth, (int)(m_iHeight * PERSENT_20));
	MapDraw::DrawMidText("1������ : [���]", m_iWidth, (int)(m_iHeight * PERSENT_30));
	MapDraw::DrawMidText("2������ : [��ũ]", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_2);
	MapDraw::DrawMidText("3������ : [�����ΰ�]", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_4);
	MapDraw::DrawMidText("4������ : [�����]", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_6);
	MapDraw::DrawMidText("5������ : [���̷����ó]", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_8);
	MapDraw::DrawMidText("6������ : [��ġ]", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_10);
	MapDraw::DrawMidText("���ư���", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_12);
}

bool GameManager::DongeonPlay(int iMonster)
{
	int iIsDead = 0;

	while (1)
	{
		WindowSet();
		YELLOW
			m_Player.PrintInfo(m_iWidth, (int)(m_iHeight * PERSENT_10));
		RED
			MapDraw::DrawMidText("---------------------------vs---------------------------", m_iWidth, (int)(m_iHeight * PERSENT_50));
		ORIGINAL
			m_Monster[iMonster].PrintInfo(m_iWidth, (int)(m_iHeight * PERSENT_80), 0);
		MapDraw::DrawMidText("���� : 1  ���� : 2  �� : 3", m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_6);
		mt19937 seedSetResult(m_rd());
		uniform_int_distribution<int> iRdNum(1, 3);
		int iMonsterAttack = iRdNum(seedSetResult);
		
		switch (_getch())
		{
		case ONE_SCISSORS:
			iIsDead = PlayWinCheck(iMonsterAttack, ATTACK_SCISSORS, iMonster);
			break;
		case TWO_ROCK:
			iIsDead = PlayWinCheck(iMonsterAttack, ATTACK_ROCK, iMonster);
			break;
		case THREE_PAPER:
			iIsDead = PlayWinCheck(iMonsterAttack, ATTACK_PAPER, iMonster);
			break;
		}

		if (iIsDead)
			break;
	}

	system("cls");

	if (iIsDead == RESULT_WIN)
	{
		string strTmp = m_Player.GetName();
		strTmp.append(" �¸�!!!");
		YELLOW
			MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_30));
		strTmp = "����ġ ";
		strTmp.append(to_string(m_Monster[iMonster].GetEXP()));
		strTmp.append("�� ������ϴ�.");
		MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_30) + 2);
		strTmp = "��� ";
		strTmp.append(to_string(m_Monster[iMonster].GetEXP()));
		strTmp.append("�� ������ϴ�.");
		MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_30) + 4);

		system("pause>null");
		
		m_Player.GetandCheckExp(m_Monster[iMonster].GetEXP());
		m_Player.AddGold(m_Monster[iMonster].GetGold());
		m_Monster[iMonster].RecoveryHP();
		return false;
	}
	else if (iIsDead == RESULT_LOSE)
	{
		string strTmp = m_Monster[iMonster].GetName();
		strTmp.append(" �¸�!!!");
		RED
			MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_40));
		//	strTmp = m_Monster[iMonster].GetName();
		//	strTmp.append("�� ����ġ ");
		//	strTmp.append(to_string(m_Player.GetEXP()));
		//	strTmp.append("�� ������ϴ�.");
		//	MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_40));

		m_Monster[iMonster].RecoveryHP();
		return true;
	}

	ORIGINAL
		return false;
}

int GameManager::PlayWinCheck(int iMonsterAttack, int iPlayerAttack, int iMonster)
{
	int iWinCheck = iPlayerAttack - iMonsterAttack;

	string strMonsterAttack = CharactorAttack(iMonsterAttack);
	string strPlayerAttack = CharactorAttack(iPlayerAttack);

	if (iPlayerAttack == iMonsterAttack)
	{
		//Draw
		PrintDongeonPlay(strMonsterAttack, strPlayerAttack, RESULT_DRAW);
	}
	else if (iWinCheck == 1 || iWinCheck == -2)
	{
		//Win
		PrintDongeonPlay(strMonsterAttack, strPlayerAttack, RESULT_WIN);
		if (m_Monster[iMonster].CutOffHP(m_Player.GetDamage()))
			return RESULT_WIN;
	}
	else if (iWinCheck == 2 || iWinCheck == -1)
	{
		//Lose
		PrintDongeonPlay(strMonsterAttack, strPlayerAttack, RESULT_LOSE);
		if (m_Player.CutOffHP(m_Monster[iMonster].GetDamage()))
			return RESULT_LOSE;
	}

	return 0;
}

string GameManager::CharactorAttack(int iAttack)
{
	if (iAttack == ATTACK_SCISSORS)
		return "����";
	else if (iAttack == ATTACK_ROCK)
		return "����";
	else if (iAttack == ATTACK_PAPER)
		return "��";
}

void GameManager::PrintDongeonPlay(string strMonsterAttack, string strPlayerAttack, int iResult)
{
	YELLOW
		MapDraw::ErasePoint(m_iWidth, (int)(m_iHeight * PERSENT_40));
		MapDraw::DrawMidText(strPlayerAttack, m_iWidth, (int)(m_iHeight * PERSENT_40));
	ORIGINAL
		MapDraw::ErasePoint(m_iWidth, (int)(m_iHeight * PERSENT_60));
		MapDraw::DrawMidText(strMonsterAttack, m_iWidth, (int)(m_iHeight * PERSENT_60));
	RED
		MapDraw::ErasePoint(m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_1);
		MapDraw::ErasePoint(m_iWidth, (int)(m_iHeight * PERSENT_60) - LINE_LENGTH_1);

		if (iResult == RESULT_DRAW)
		{
			MapDraw::DrawMidText("DRAW", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_1);
			MapDraw::DrawMidText("DRAW", m_iWidth, (int)(m_iHeight * PERSENT_60) - LINE_LENGTH_1);
		}
		else if (iResult == RESULT_WIN)
		{
			MapDraw::DrawMidText("WIN", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_1);
			MapDraw::DrawMidText("LOSE", m_iWidth, (int)(m_iHeight * PERSENT_60) - LINE_LENGTH_1);
		}
		else if (iResult == RESULT_LOSE)
		{
			MapDraw::DrawMidText("LOSE", m_iWidth, (int)(m_iHeight * PERSENT_40) + LINE_LENGTH_1);
			MapDraw::DrawMidText("WIN", m_iWidth, (int)(m_iHeight * PERSENT_60) - LINE_LENGTH_1);
		}
		Sleep(1000);
	ORIGINAL
}

void GameManager::WeaponShopMenu()
{
	while (1)
	{
		system("cls");

		int iSelect = 0;
		string strWeaponType = "";

		WindowSet();
		PrintWeaponShopMenu();

		iSelect = MapDraw::MenuSelectCursor(MENU_COUNT_WEAPON_SHOP, LINE_LENGTH_2, (int)(m_iWidth * PERSENT_30), (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_2);

		switch (iSelect)
		{
		case WEAPON_TYPE_DAGGER:
			strWeaponType = "Dagger";
			break;
		case WEAPON_TYPE_GUN:
			strWeaponType = "Gun";
			break;
		case WEAPON_TYPE_SWORD:
			strWeaponType = "Sword";
			break;
		case WEAPON_TYPE_WAND:
			strWeaponType = "Wand";
			break;
		case WEAPON_TYPE_BOW:
			strWeaponType = "Bow";
			break;
		case WEAPON_TYPE_HAMMER:
			strWeaponType = "Hammer";
			break;
		case WEAPON_SHOP_EXIT:
			return;
		}

		WeaponShop(strWeaponType);
	}
}

void GameManager::PrintWeaponShopMenu()
{
	MapDraw::DrawMidText("�� �� S H O P �� ��", m_iWidth, (int)(m_iHeight * PERSENT_30));
	MapDraw::DrawMidText("Dagger", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_2);
	MapDraw::DrawMidText("Gun", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_4);
	MapDraw::DrawMidText("Sword", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_6);
	MapDraw::DrawMidText("Wand", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_8);
	MapDraw::DrawMidText("Bow", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_10);
	MapDraw::DrawMidText("Hammer", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_12);
	MapDraw::DrawMidText("���ư���", m_iWidth, (int)(m_iHeight * PERSENT_30) + LINE_LENGTH_14);
}

void GameManager::WeaponShop(string strWeaponType)
{
	int iPage = 0;

	while (1)
	{
		system("cls");
		WindowSet();

		int i_This_Weapon_Type_Max_Num			= WeaponMap[strWeaponType].size();
		//�ش� Ÿ���� ���� ����.
		
		PrintWeaponShop(strWeaponType, i_This_Weapon_Type_Max_Num, iPage);
		//ȭ�����

		int iCheckNum = 0;
		//���� �������� �������� ���� ���� üũ

		if (iPage) {
			if (i_This_Weapon_Type_Max_Num - WEAPON_SHOW_MAX_NUM > WEAPON_SHOW_MAX_NUM)
				iCheckNum = iPage * 5 + 5;
			else
				iCheckNum = i_This_Weapon_Type_Max_Num - WEAPON_SHOW_MAX_NUM;
		}
		else
			iCheckNum = MIN(i_This_Weapon_Type_Max_Num, WEAPON_SHOW_MAX_NUM);


		int iSelect = MapDraw::MenuSelectCursor(iCheckNum + DEFAULT_SHOP_MENU_NUM, LINE_LENGTH_3, (int)(m_iWidth * PERSENT_10), (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_4);

		if (iSelect < iCheckNum)
		{
			Weapon* WeaponTmp = &WeaponMap[strWeaponType].at(iSelect + iPage * 5);
			m_Player.CutOffGold(WeaponTmp->GetGold());
			m_Player.WeaponDataSave(WeaponTmp);
		}
		else if (iSelect == iCheckNum) //���� ������ ��ư
		{
			if (iPage)
				iPage--;
		}
		else if (iSelect == iCheckNum + 1) //���� ������ ��ư
		{
			if (iPage * 5 + 5 < i_This_Weapon_Type_Max_Num)
				iPage++;
		}
		else if (iSelect == iCheckNum + 2) //���ư��� ��ư
			return;
	}
}

void GameManager::PrintWeaponShop(string strWeaponType, int iWeaponMaxNum, int iPage)
{
	
	string strTmp = "���� Gold : ";
	strTmp.append(to_string(m_Player.GetGold()));
	MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight* PERSENT_10));

	strTmp = strWeaponType;
	strTmp.append(" Shop");
	MapDraw::DrawMidText(strTmp, m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_2);

	int iCount = 0;

	for (int i = iPage * 5; i < (iPage * 5) + 5; i++)
	{
		if (iWeaponMaxNum <= i)
			break;
		else
			YELLOW
			WeaponMap[strWeaponType].at(i).PrintInfo(m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_4 + iCount++ * 3);
	}

	ORIGINAL
	MapDraw::DrawMidText("���� ������", m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_4 + iCount * 3);
	MapDraw::DrawMidText("���� ������", m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_4 + (iCount + 1) * 3);
	MapDraw::DrawMidText("������", m_iWidth, (int)(m_iHeight * PERSENT_10) + LINE_LENGTH_4 + (iCount + 2) * 3);
}

void GameManager::WindowSet()
{
	SKY_BLUE
		MapDraw::BoxDraw(0, 0, m_iWidth, m_iHeight);
	ORIGINAL
}

GameManager::~GameManager()
{
	delete[] m_Monster;
}