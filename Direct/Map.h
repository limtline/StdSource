#pragma once
#include "Include.h"

class Map
{

public :
	Map();
	~Map();
	Sprite test;
	bool tests;

	// map image obj
	Sprite m_MapCreep;
	Sprite m_Land;
	Sprite m_Colony[4];
	int m_Colony_count = 0;
	DWORD m_Colony_ani;

	// console image obj
	Sprite t_Console;
	Sprite z_Console;
	Sprite p_Console;

	int console_theme;

	Sprite c_SunkenIcon;
	Sprite c_SunkenHighlight;
	Sprite c_SunkenClick;
	
	// Debug image obj - to be captioned
	Sprite gyeokja;
	int backGroundArr[18][30];
	BOOL debug_BG = false;

	// Unusing
	/*Sprite m_MapImg1_1[6];
	Sprite m_MapImg1_2[45];
	Sprite m_MapImg1_3[65];*/

	/*Sprite m_MapImg2_1[7];
	Sprite m_MapImg2_2[30];
	Sprite m_MapImg2_3[45];

	DWORD m_MapImg1_1_ani1;
	DWORD m_MapImg1_2_ani1;

	int m_MapImg1_1_ani1Count;
	int m_MapImg1_2_ani1Count;

	int m_MapImg2_1_ani1Count;
	int m_MapImg2_2_ani1Count;

	int m_Stage;*/

	void Init();
	void Update(double frame);
	void Draw();
	void DrawGJ();
	void DrawConsole(int mx, int my, BOOL clickSunken);
};

extern Map m_map;