#pragma once
#include "Include.h"

class Console
{

public:

	Console();
	~Console();

	// console image obj
	Sprite t_Console;
	Sprite z_Console;
	Sprite p_Console;
	Sprite c_ClockFrame;
	Sprite c_NumberImg[10];
	Sprite c_Colon;

	Sprite defeatBG;

	int console_theme;

	/*	Icon Group	*/ 
	// Sunken
	Sprite c_SunkenIcon;
	Sprite c_SunkenHighlight;
	Sprite c_SunkenClick;

	// Delete
	Sprite c_DeleteIcon;
	Sprite c_DeleteHighlight;
	Sprite c_DeleteClick;

	// Start
	Sprite c_StartIcon;
	Sprite c_StartHighlight;
	Sprite c_StartClick;

	// Coin System
	Sprite c_CoinImg;

	DWORD c_GameTime;
	DWORD c_NowTime;
	int timeArr[8];
	int coinArr[5];

	void Init();
	void Update();
	void Activate(int mx, int my, BOOL clickSunken, BOOL clickDelete, BOOL clickStart);
	void Draw();
	void DrawSkIcon(int mx, int my, BOOL clickSunken);
	void DrawDelIcon(int mx, int my, BOOL clickDelete);
	void DrawStrtIcon(int mx, int my, BOOL clickStart);
	void DrawSample();
};

extern Console console;