#pragma once
#include "Include.h"

class Marin
{
private:
	
	int m_MarinCount;
	DWORD m_MarinAniTime;
	

public:
	//BOOL MarinExist;
	BOOL marin_BG;
	Sprite MarinRightImg[9];
	Sprite MarinLeftImg[9];
	Sprite MarinDownImg[9];
	Sprite MarinUpImg[9];
	Sprite MarinDieImg[12];

	Sprite FullHP;
	Sprite MidHP;
	Sprite LowHP;

	int marinMoveArr[18][30];
	int mrX, mrY;
	int curX, curY;

	int hp;

	char Fname[256];

	ULONGLONG Timer;
	int Check;


	Marin();
	~Marin();

	void Init();
	void Update();
	void Draw(int x, int y);
	void ArrInit();

	//virtual void OnMessage(MSG* msg);
};
extern Marin marin;
