#pragma once
#include "Mecro.h"

class MapDraw
{
public:
	static void BoxDraw(int Start_x, int Start_y, int Width, int Height)
	{
		if (Start_x > Width)
			Start_x -= Width;
		for (int y = 0; y < Height; y++)
		{
			gotoxy(Start_x, Start_y + y);
			if (y == 0)
			{
				for (int x = 0; x < Width; x++)
					cout << "��";
			}
			else if (y == Height - 1)
			{
				for (int x = 0; x < Width; x++)
					cout << "��";
			}
			else
			{
				cout << "��";
				for (int x = 1; x < Width - 1; x++)
					cout << "  ";
				cout << "��";
			}
		}
		return;
	}

	static void BoxErase(int Width, int Height)
	{
		for (int y = 1; y < Height - 1; y++)
		{
			gotoxy(2, y);
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
		}
	}

	static void DrawPoint(string str, int x, int y)
	{
		gotoxy(x * 2, y);
		cout << str;
		gotoxy(-1, -1);
		return;
	}

	static void DrawMidText(string str,unsigned int x, int y)
	{
		if (x > str.size() / 2)
			x -= str.size() / 2;
		gotoxy(x, y);
		cout << str;
		
		return;
	}

	static void TextDraw(string str, int x, int y)
	{
		gotoxy(x, y);
		cout << str;
	}

	static void ErasePoint(int x, int y)
	{
		gotoxy(x * 2, y);
		cout << "    ";
		gotoxy(-1, -1);
		return;
	}

	static int MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
	{
		int Select = 0;
		RED
			DrawPoint("��", x, y);
		ORIGINAL
			while (1)
			{
				switch (_getch())
				{
				case UP:
					if (Select > 0)
					{
						ErasePoint(x, y);
						y -= AddCol;
						Select--;
					}
					break;
				case DOWN:
					if (Select + 1 < MenuLen)
					{
						ErasePoint(x, y);
						y += AddCol;
						Select++;
					}
					break;
				case ENTER:
					return Select;
				}
				RED
					DrawPoint("��", x, y);
				ORIGINAL
			}
	}

	static void gotoxy(int x, int y)
	{
		COORD Pos = { (short)x, (short)y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};
