#pragma once
#include "Include.h"

typedef struct HeroMove2		// 영웅이동
{
	double InitX, InitY;	// 캐릭터 초기 위치
	double nX, nY;			// 현재위치
	double m_nX, m_nY;		// 캐릭터가 움직 일때 받아올 변수
	double speed;			// 캐릭터가 이동할 속도
	double attack;
};

class Raynor
{
private:
	DWORD RaynorAniTime;
	DWORD RaynorAttackAniTime;

	double distance;
	double distanceZl;
	double distanceZg;
	double distanceMa;
	int RaynorCol;

public:
	// 이동
	Sprite RaynorMoveLR[9];	// 왼쪽
	Sprite RaynorMoveRL[9];	// 오른쪽
	Sprite RaynorMoveBT[9];	// 위쪽
	Sprite RaynorMoveTB[9];	// 아래쪽
	Sprite RaynorMoveLBRT[9];	// 오른쪽 위 대각선
	Sprite RaynorMoveLTRB[9];	// 오른쪽 아래 대각선
	Sprite RaynorMoveRBLT[9];	// 왼쪽 위 대각선
	Sprite RaynorMoveRTLB[9];	// 왼쪽 아래 대각선

	// 공격
	Sprite RaynorAttackLR[3];	// 왼쪽
	Sprite RaynorAttackRL[3];	// 오른쪽
	Sprite RaynorAttackBT[3];	// 위쪽
	Sprite RaynorAttackTB[3];	// 아래쪽
	Sprite RaynorAttackLBRT[3];	// 오른쪽 위 대각선
	Sprite RaynorAttackLTRB[3];	// 오른쪽 아래 대각선
	Sprite RaynorAttackRBLT[3];	// 왼쪽 위 대각선
	Sprite RaynorAttackRTLB[3];	// 왼쪽 아래 대각선

	int RaynorSpriteClass;
	int RaynorSpriteCount;
	int RaynorAttackSpriteCount;
	HeroMove2 curMove;

	BOOL COL;

	Raynor();
	~Raynor();

	void Init();
	void Update(int Enemy_Kind, BOOL& startState);
	void Draw();
	void MouseMoving(LPARAM lParam);

	void Reset();
};

extern Raynor raynor;