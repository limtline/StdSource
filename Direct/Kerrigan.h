#pragma once
#include "Include.h"

typedef struct HeroMove		// 영웅이동
{
	double InitX, InitY;	// 캐릭터 초기 위치
	double nX, nY;			// 현재위치
	double m_nX, m_nY;		// 캐릭터가 움직 일때 받아올 변수
	double speed;			// 캐릭터가 이동할 속도
};

class Kerrigan {
private:
	DWORD m_KerriganAniTime;
	DWORD m_KerriganAttackTime;
	int kerriganSpriteCount;
	int kerriganAttackCount;
	double distance;

public:
	// 영웅 이동
	Sprite KerriganMoveLR[8];	// 왼쪽
	Sprite KerriganMoveRL[8];	// 오른쪽
	Sprite KerriganMoveBT[8];	// 위쪽
	Sprite KerriganMoveTB[8];	// 아래쪽
	Sprite KerriganMoveLBRT[8];	// 오른쪽 위 대각선
	Sprite KerriganMoveLTRB[8];	// 오른쪽 아래 대각선
	Sprite KerriganMoveRBLT[8];	// 왼쪽 위 대각선
	Sprite KerriganMoveRTLB[8];	// 왼쪽 아래 대각선

	// 영웅 공격
	Sprite KerriganAttackLR[8];		// 왼쪽
	Sprite KerriganAttackRL[8];		// 오른쪽
	Sprite KerriganAttackBT[8];		// 위쪽
	Sprite KerriganAttackTB[8];		// 아래쪽
	Sprite KerriganAttackLBRT[8];	// 오른쪽 위 대각선
	Sprite KerriganAttackLTRB[8];	// 오른쪽 아래 대각선
	Sprite KerriganAttackRBLT[8];	// 왼쪽 위 대각선
	Sprite KerriganAttackRTLB[8];	// 왼쪽 아래 대각선

	int kerriganCol;
	int kerriganSpriteClass;
	HeroMove curMove;

	BOOL COL;

	Kerrigan();

	~Kerrigan();

	void Init();
	void Update(int Enemy_Kind, BOOL& startState);
	void Draw();
	void MouseMoving(LPARAM lParam);

	void Reset();
};

extern Kerrigan kerrigan;