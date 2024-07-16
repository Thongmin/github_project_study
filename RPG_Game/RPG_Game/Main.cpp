#pragma once
#include "GameManager.h"

void main()
{
	srand((unsigned)time(NULL)); //타임 기준 시드 랜덤 설정.

	GameManager GM; //GM 객체 생성
	GM.MainMenu(); // GM 객체의 MainMenu 함수 호출
}