#pragma once
#include "Include.h"

typedef struct HeroMove1		// 영웅이동
{
	double InitX, InitY;	// 캐릭터 초기 위치
	double nX, nY;			// 현재위치
	double m_nX, m_nY;		// 캐릭터가 움직 일때 받아올 변수
	double speed;			// 캐릭터가 이동할 속도
};

class Phoenix
{
private:
	DWORD m_PhoenixAniTime;
	DWORD m_PhoenixMoveTime;
	DWORD m_PhoenixAttackAniTime;
	int m_PhoenixCount;
	int skill;					// 스킬사용
	double distance;
	BOOL DrawColl;
	int PhoenixCol;

public:
	Sprite PhoenixMoveLR[8];	// 왼쪽
	Sprite PhoenixMoveRL[8];	// 오른쪽
	Sprite PhoenixMoveBT[8];	// 위쪽
	Sprite PhoenixMoveTB[8];	// 아래쪽
	Sprite PhoenixMoveLBRT[8];	// 오른쪽 위 대각선
	Sprite PhoenixMoveLTRB[8];	// 오른쪽 아래 대각선
	Sprite PhoenixMoveRBLT[8];	// 왼쪽 위 대각선
	Sprite PhoenixMoveRTLB[8];	// 왼쪽 아래 대각선

	// 영웅 공격
	Sprite PhoenixAttackLR[8];		// 왼쪽
	Sprite PhoenixAttackRL[8];		// 오른쪽
	Sprite PhoenixAttackBT[8];		// 위쪽
	Sprite PhoenixAttackTB[8];		// 아래쪽
	Sprite PhoenixAttackLBRT[8];	// 오른쪽 위 대각선
	Sprite PhoenixAttackLTRB[8];	// 오른쪽 아래 대각선
	Sprite PhoenixAttackRBLT[8];	// 왼쪽 위 대각선
	Sprite PhoenixAttackRTLB[8];	// 왼쪽 아래 대각선

	int PhoenixSpriteClass;
	int PhoenixSpriteCount;
	int PhoenixAttackSpriteCount;

	HeroMove1 curMove;

	BOOL COL;

	Phoenix();

	~Phoenix();

	void Init();
	void Update(int Enemy_Kind, BOOL& startState);
	void Draw();
	void MouseMoving(LPARAM lParam);

	void Reset();
};

extern Phoenix phoenix;