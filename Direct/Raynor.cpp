#include "Include.h"

Raynor raynor;

Raynor::Raynor()
{
	RaynorAniTime = GetTickCount64();;
	RaynorAttackAniTime = GetTickCount64();
	RaynorSpriteCount = 0;
	RaynorSpriteClass = HERO_IDLE_;
	RaynorAttackSpriteCount = 0;
	RaynorCol = 0;
	distance = 0;
	distanceZl = 0;
	distanceZg = 0;
	distanceMa = 0;
	COL = FALSE;
	Reset();
}

Raynor::~Raynor()
{
}

void Raynor::Init()
{
	RaynorAniTime = GetTickCount64();;
	RaynorAttackAniTime = GetTickCount64();
	RaynorSpriteCount = 0;
	RaynorSpriteClass = HERO_IDLE_;
	RaynorAttackSpriteCount = 0;
	RaynorCol = 0;
	distanceZl = 0;
	distanceZg = 0;
	distanceMa = 0;
	COL = FALSE;
	Reset();

	// 이동
	char FileName[256];
	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLR/raynorLR%d.png", i);	// 왼쪽
		RaynorMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRL/raynorRL%d.png", i);	// 오른쪽
		RaynorMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorBT/raynorBT%d.png", i);	// 위쪽
		RaynorMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorTB/raynorTB%d.png", i);	// 아래쪽
		RaynorMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLBRT/raynorLBRT%d.png", i);	// 오른쪽 위 대각선
		RaynorMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLTRB/raynorLTRB%d.png", i);	// 오른쪽 아래 대각선
		RaynorMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRBLT/raynorRBLT%d.png", i);	// 왼쪽 위 대각선
		RaynorMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRTLB/raynorRTLB%d.png", i);	// 왼쪽 아래 대각선
		RaynorMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// 공격
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLR/raynorAttackLR%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRL/raynorAttackRL%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttacBT/raynorAttackBT%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackTB/raynorAttackTB%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLBRT/raynorAttackLBRT%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLTRB/raynorAttackLTRB%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRTLB/raynorAttackRTLB%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRBLT/raynorAttackRBLT%d.png", i);	// 왼쪽 아래 대각선
		RaynorAttackRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Raynor::Update(int Enemy_Kind, BOOL& startState)
{
	if (GetTickCount64() - RaynorAniTime > 100)
	{
		RaynorSpriteCount++;
		if (RaynorSpriteCount > 8) RaynorSpriteCount = 0;
		RaynorAniTime = GetTickCount64();
	}

	if (GetTickCount64() - RaynorAttackAniTime > 100)
	{
		RaynorAttackSpriteCount++;
		if (RaynorAttackSpriteCount > 2) RaynorAttackSpriteCount = 0;
		RaynorAttackAniTime = GetTickCount64();
	}

	heroManager.Moving(curMove.nX, curMove.nY, curMove.m_nX, curMove.m_nY, curMove.speed, RaynorCol, RaynorSpriteClass);

	if ((abs(curMove.nX - curMove.m_nX) <= 1.5f) &&
		(abs(curMove.nY - curMove.m_nY) <= 1.5f))
	{
		COL = FALSE;
	}

	if (COL == FALSE)
	{

		RaynorCol = HEROCOL_ON;
		heroManager.MonCol(curMove.nX, curMove.nY, curMove.speed, RaynorCol, RaynorSpriteClass, startState);
	}
		
	
}

void Raynor::Draw()
{
	// 이동
	if (RaynorSpriteClass == HEROMOVE_LBRT_)	// 왼쪽 아래 -> 오른쪽 위 방향
		RaynorMoveLBRT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_LTRB_)	// 왼쪽 위 -> 오른쪽 아래 방향
		RaynorMoveLTRB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RBLT_)	// 오른쪽 아래 -> 왼쪽 위 방향
		RaynorMoveRBLT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RTLB_ || RaynorSpriteClass == HERO_IDLE_)	// 오른쪽 위 -> 왼쪽 아래 방향
		RaynorMoveRTLB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

	if (RaynorSpriteClass == HEROMOVE_BT_)		// 아래 -> 위 방향
		RaynorMoveBT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_TB_)		// 위 -> 아래 방향
		RaynorMoveTB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_LR_)		// 왼쪽 -> 오른쪽 방향
		RaynorMoveLR[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RL_)		// 오른쪽 -> 왼쪽 방향
		RaynorMoveRL[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

	// 공격
	if (heroManager.heroAttackState == TRUE)
	{
		if (RaynorSpriteClass == HEROATTACK_LBRT_)	// 왼쪽 아래 -> 오른쪽 위 방향
			RaynorAttackLBRT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_LTRB_)	// 왼쪽 위 -> 오른쪽 아래 방향
			RaynorAttackLTRB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RBLT_)	// 오른쪽 아래 -> 왼쪽 위 방향
			RaynorAttackRBLT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RTLB_)	// 오른쪽 위 -> 왼쪽 아래 방향
			RaynorAttackRTLB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

		if (RaynorSpriteClass == HEROATTACK_BT_)		// 아래 -> 위 방향
			RaynorAttackBT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_TB_)		// 위 -> 아래 방향
			RaynorAttackTB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_LR_)		// 왼쪽 -> 오른쪽 방향
			RaynorAttackLR[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RL_)		// 오른쪽 -> 왼쪽 방향
			RaynorAttackRL[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	}
}

void Raynor::MouseMoving(LPARAM lParam)
{
	curMove.m_nX = LOWORD(lParam);
	curMove.m_nY = HIWORD(lParam);
	RaynorCol = HERO_MOVE;
	COL = TRUE;
	curMove.speed = 1.5f;
}

void Raynor::Reset()
{
	curMove.InitX = 1000.0f;				// 캐릭터의 X 좌표
	curMove.InitY = 400.0f;					// 캐릭터의 Y 좌표
	curMove.speed = 1.5f;					// 캐릭터 이동속도
	curMove.attack = 10.0f;					// 캐릭터 공격력
	curMove.nX = curMove.InitX;				// 현재 캐릭터 X 위치
	curMove.nY = curMove.InitY;				// 현재 캐리터 Y 위치
}
