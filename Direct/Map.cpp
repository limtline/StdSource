#include "Include.h"

Map m_map;


Map::Map()
{
	//m_Stage = 1;
}

Map::~Map()
{

}

void Map::Init()
{
	//int i, j;
	char FileName[256];

	console_theme = CONSOLE_TYPE_T;

	m_MapCreep.Create("./resource/BackGround/creep.png", false, D3DCOLOR_XRGB(0, 0, 0));
	m_Land.Create("./resource/BackGround/land.png", false, D3DCOLOR_XRGB(0, 0, 0));
	
	// 배열 타일 초기화 함수
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 30; j++) {
			this->backGroundArr[i][j] = BG_EMPTY;
			if (j == 0 || j == 1) this->backGroundArr[i][j] = BG_START_GROUND;
			else if (j == 28 || j == 29) this->backGroundArr[i][j] = BG_FINISH_GROUND;
			if(i == 17) this->backGroundArr[i][j] = BG_STRUCTURE;
		}
	}
	gyeokja.Create("./resource/check.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

void Map::Update(double frame)
{

	//if (GetTickCount64() - m_MapImg1_1_ani1 > frame)
	//{
	//	m_MapImg1_1_ani1 = GetTickCount64();
	//}

}

void Map::Draw()
{
	int XMap = 0;
	int YMap = 0;
	for (int i = 0; i < 3; i++)	// creep size : 256 x 256
	{
		XMap = 0;
		for (int j = 0; j < 6; j++)
		{
			m_MapCreep.Draw(XMap, YMap); //이미지출력
			XMap += 256;
		}
		YMap += 256;
	}

	XMap = 0;
	YMap = 0;
	for (int i = 0; i < 20; i++)
	{
		XMap = 0;
		for (int j = 0; j < 31; j++)
		{
			if(j <= 1 || j >= 28 || i >= 18)
				m_Land.Draw(XMap, YMap);
			XMap += 42;
		}
		YMap += 42;
	}
}

// Function : DrawGJ() / GJ = 격자
// 디버깅용 격자 배열 출력 함수
void Map::DrawGJ()
{
	gyeokja.Render(0, 0, 0, 1, 1);
}