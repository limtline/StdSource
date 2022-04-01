#include "Kerrigan.h"


Kerrigan kerrigan;

Kerrigan::Kerrigan()
{
	m_KerriganAniTime = GetTickCount64();
	m_KerriganAttackTime = GetTickCount64();
	kerriganSpriteCount = 0;
	kerriganAttackCount = 0;
	kerriganCol = 0;
	COL = FALSE;
	kerriganSpriteClass = HERO_IDLE_;
	Reset();
}

Kerrigan::~Kerrigan()
{

}

void Kerrigan::Init()
{
	m_KerriganAniTime = GetTickCount64();
	m_KerriganAttackTime = GetTickCount64();
	kerriganSpriteCount = 0;
	kerriganAttackCount = 0;
	kerriganCol = 0;
	COL = FALSE;
	kerriganSpriteClass = HERO_IDLE_;
	Reset();

	char FileName[256];
	// 영웅 이동 모션
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLR/kerriganLR%d.png", i);	// 왼쪽
		KerriganMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRL/kerriganRL%d.png", i);	// 오른쪽
		KerriganMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganBT/kerriganBT%d.png", i);	// 위쪽
		KerriganMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganTB/kerriganTB%d.png", i);	// 아래쪽
		KerriganMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLBRT/kerriganLBRT%d.png", i);	// 오른쪽 위 대각선
		KerriganMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLTRB/kerriganLTRB%d.png", i);	// 오른쪽 아래 대각선
		KerriganMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRBLT/kerriganRBLT%d.png", i);	// 왼쪽 위 대각선
		KerriganMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRTLB/kerriganRTLB%d.png", i);	// 왼쪽 아래 대각선
		KerriganMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// 영웅 공격
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLR/kerriganAttackLR%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRL/kerriganAttackRL%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackBT/kerriganAttackBT%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackTB/kerriganAttackTB%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLBRT/kerriganAttackLBRT%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLTRB/kerriganAttackLTRB%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRBLT/kerriganAttackRBLT%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRTLB/kerriganAttackRTLB%d.png", i);	// 왼쪽 아래 대각선
		KerriganAttackRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Kerrigan::Update(int Enemy_Kind, BOOL& startState)
{
	// 영웅 이동
	if (GetTickCount64() - m_KerriganAniTime > 100)
	{
		kerriganSpriteCount++;
		if (kerriganSpriteCount > 7) kerriganSpriteCount = 0;
		m_KerriganAniTime = GetTickCount64();
	}

	// 영웅 공격
	if (GetTickCount64() - m_KerriganAttackTime > 100)
	{
		kerriganAttackCount++;
		if (kerriganAttackCount > 6) kerriganAttackCount = 0;
		m_KerriganAttackTime = GetTickCount64();
	}

	heroManager.Moving(curMove.nX, curMove.nY, curMove.m_nX, curMove.m_nY, curMove.speed, kerriganCol, kerriganSpriteClass);

	if ((abs(curMove.nX - curMove.m_nX) <= 1.5f) &&
		(abs(curMove.nY - curMove.m_nY) <= 1.5f))
	{
		COL = FALSE;
	}


	if (COL == FALSE)
	{
		kerriganCol = HEROCOL_ON;
		heroManager.MonCol(curMove.nX, curMove.nY, curMove.speed, kerriganCol, kerriganSpriteClass, startState);
	}

}

void Kerrigan::Draw()
{

	// 영웅 이동
	if (kerriganSpriteClass == HEROMOVE_LBRT_)		// 왼쪽 아래 -> 오른쪽 위 방향
		KerriganMoveLBRT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_LTRB_)		// 왼쪽 위 -> 오른쪽 아래 방향
		KerriganMoveLTRB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RBLT_)		// 오른쪽 아래 -> 왼쪽 위 방향
		KerriganMoveRBLT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RTLB_ || kerriganSpriteClass == HERO_IDLE_)		// 오른쪽 위 -> 왼쪽 아래 방향
		KerriganMoveRTLB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);

	if (kerriganSpriteClass == HEROMOVE_BT_)		// 아래 -> 위 방향
		KerriganMoveBT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_TB_)		// 위 -> 아래 방향
		KerriganMoveTB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_LR_)		// 왼쪽 -> 오른쪽 방향
		KerriganMoveLR[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RL_)		// 오른쪽 -> 왼쪽 방향
		KerriganMoveRL[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);


	if (heroManager.heroAttackState == TRUE)
	{
		// 영웅 공격
		if (kerriganSpriteClass == HEROATTACK_LR_)		// 왼쪽 -> 오른쪽 방향
			KerriganAttackLR[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RL_)		// 오른쪽 -> 왼쪽 방향
			KerriganAttackRL[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_BT_)		// 아래 -> 위 방향
			KerriganAttackBT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_TB_)		// 위 -> 아래 방향
			KerriganAttackTB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);

		if (kerriganSpriteClass == HEROATTACK_LBRT_)	// 왼쪽 아래 -> 오른쪽 위 방향
			KerriganAttackLBRT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_LTRB_)	// 왼쪽 위 -> 오른쪽 아래 방향
			KerriganAttackLTRB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RBLT_)	// 오른쪽 아래 -> 왼쪽 위 방향
			KerriganAttackRBLT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RTLB_)	// 오른쪽 위 -> 왼쪽 아래 방향
			KerriganAttackRTLB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	}
}

void Kerrigan::MouseMoving(LPARAM lParam)			// nX,nY 마우스 좌표를 받아옴
{
	curMove.m_nX = LOWORD(lParam);
	curMove.m_nY = HIWORD(lParam);
	kerriganCol = HERO_MOVE;
	COL = TRUE;
	curMove.speed = 1.5f;
}

void Kerrigan::Reset()
{
	curMove.InitX = 1000.0f;				// 캐릭터의 X 좌표
	curMove.InitY = 400.0f;					// 캐릭터의 Y 좌표
	curMove.speed = 1.5f;					// 캐릭터 이동속도
	curMove.nX = curMove.InitX;				// 현재 캐릭터 X 위치
	curMove.nY = curMove.InitY;				// 현재 캐리터 Y 위치
}