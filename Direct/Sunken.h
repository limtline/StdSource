#pragma once
#include "Include.h"

class Sunken
{
private:
	Sprite SunkenImg;
	Sprite SunkenEnable;
	Sprite SunkenDiable;
	ULONGLONG m_SunkenAniTime;
	ULONGLONG m_SpineAniTime;
	int m_SunkenSpineCount;
	int m_SunkenCount;
	ULONGLONG m_KillTime;
	DWORD m_AttackDelay;

public:
	Sprite SunkenAttack[21];
	Sprite SunkenInactive[2];
	Sprite SunkenSpine[21];

	Sprite MarinDie[12];
	Sprite ZerglingDie[10];
	Sprite ZealotDie[11];

	BOOL AttackLock;

	BOOL active_sunkenspine;

	int s_Attack_damage;
	int dmg;

	int sunkenSpriteCount;

	Sunken();
	Sunken(Sunken& sunken);
	
	~Sunken();

	Sunken& operator=(const Sunken& sunken);

	void Init();
	void Update(int Enemy_Kind, BOOL& startState);
	
	void Draw(BOOL drawState, int nX, int nY, char *coordinate, BOOL drawMsMoveState, BOOL delMsMoveState, int Enemy_Kind);
	BOOL DrawCheck(int mX, int mY, BOOL drawMsMoveState, char *coordinate, BOOL delMsMoveState, BOOL deleteState);
	//BOOL EnemyCheck(int Enemy_Kind);
	void CalculateBuildArea(int *x, int *y, int nX, int nY);
	void DrawDieMotion(int unit_kind, int idx, int x, int y);
};
extern Sunken sunken;