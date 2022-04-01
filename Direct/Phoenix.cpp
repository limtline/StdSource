#include "Include.h"

Phoenix phoenix;

Phoenix::Phoenix()
{
	m_PhoenixAniTime = 0;
	m_PhoenixCount = 0;
	PhoenixCol = 0;
	m_PhoenixMoveTime = GetTickCount64();
	m_PhoenixAttackAniTime = GetTickCount64();
	PhoenixSpriteClass = HERO_IDLE_;
	PhoenixAttackSpriteCount = 0;
	PhoenixSpriteCount = 0;
	DrawColl = FALSE;
	COL = FALSE;
	Reset();
}

Phoenix::~Phoenix()
{
}

void Phoenix::Init()
{
	m_PhoenixAniTime = 0;
	m_PhoenixCount = 0;
	PhoenixCol = 0;
	m_PhoenixMoveTime = GetTickCount64();
	m_PhoenixAttackAniTime = GetTickCount64();
	PhoenixSpriteClass = HERO_IDLE_;
	PhoenixAttackSpriteCount = 0;
	PhoenixSpriteCount = 0;
	DrawColl = FALSE;
	COL = FALSE;
	Reset();

	char FileName[256];
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLR/phoenixLR%d.png", i);	// 왼쪽 -> 오른쪽
		PhoenixMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRL/phoenixRL%d.png", i);	// 오른쪽 -> 왼쪽
		PhoenixMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixBT/phoenixBT%d.png", i);	// 아래 -> 위
		PhoenixMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixTB/phoenixTB%d.png", i);	// 위 -> 아래
		PhoenixMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLBRT/phoenixLBRT%d.png", i);	// 왼쪽 아래 -> 오른쪽 위
		PhoenixMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLTRB/phoenixLTRB%d.png", i);	// 왼쪽 위 -> 오른쪽 아래
		PhoenixMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRBLT/phoenixRBLT%d.png", i);	// 오른쪽 아래 -> 왼쪽 위
		PhoenixMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRTLB/phoenixRTLB%d.png", i);	// 오른쪽 위 -> 왼쪽 아래
		PhoenixMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// 공격
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLR/phoenixAttackLR%d.png", i);	// 왼쪽 -> 오른쪽
		PhoenixAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRL/phoenixAttackRL%d.png", i);	// 오른쪽 -> 왼쪽
		PhoenixAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackBT/phoenixAttackBT%d.png", i);	// 위쪽 -> 아래쪽
		PhoenixAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackTB/phoenixAttackTB%d.png", i);	// 아래쪽 -> 위쪽
		PhoenixAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLBRT/phoenixAttackLBRT%d.png", i);	// 왼쪽 아래 -> 오른쪽 위
		PhoenixAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLTRB/phoenixAttackLTRB%d.png", i);	// 왼쪽 위 -> 오른쪽 아래
		PhoenixAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRBLT/phoenixAttackRBLT%d.png", i);	// 오른쪽 아래 -> 왼쪽 위
		PhoenixAttackRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRTLB/phoenixAttackRTLB%d.png", i);	// 오른쪽 위 -> 왼쪽 아래
		PhoenixAttackRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Phoenix::Update(int Enemy_Kind, BOOL& startState)
{
	if (GetTickCount64() - m_PhoenixAniTime > 100)
	{
		PhoenixSpriteCount++;
		if (PhoenixSpriteCount > 7) PhoenixSpriteCount = 0;
		m_PhoenixAniTime = GetTickCount64();
	}

	if (GetTickCount64() - m_PhoenixAttackAniTime > 100)
	{
		PhoenixAttackSpriteCount++;
		if (PhoenixAttackSpriteCount > 7) PhoenixAttackSpriteCount = 0;
		m_PhoenixAttackAniTime = GetTickCount64();
	}

	heroManager.Moving(curMove.nX, curMove.nY, curMove.m_nX, curMove.m_nY, curMove.speed, PhoenixCol, PhoenixSpriteClass);

	if ((abs(curMove.nX - curMove.m_nX) <= 1.5f) &&
		(abs(curMove.nY - curMove.m_nY) <= 1.5f))
	{
		COL = FALSE;
	}

	if (COL == FALSE)
	{
		PhoenixCol = HEROCOL_ON;
		heroManager.MonCol(curMove.nX, curMove.nY, curMove.speed, PhoenixCol, PhoenixSpriteClass, startState);
	}
}

void Phoenix::Draw()
{
	// 이동
	if (PhoenixSpriteClass == HEROMOVE_LBRT_)	// (오른쪽 위 대각선)
		PhoenixMoveLBRT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_LTRB_)	// (오른쪽 아래 대각선)
		PhoenixMoveLTRB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RBLT_)	// (왼쪽 위 대각선)
		PhoenixMoveRBLT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RTLB_ || PhoenixSpriteClass == HERO_IDLE_)	// (왼쪽 아래 대각선)
		PhoenixMoveRTLB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

	if (PhoenixSpriteClass == HEROMOVE_BT_)		// (위쪽)
		PhoenixMoveBT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_TB_)		// (아래쪽)
		PhoenixMoveTB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_LR_)		// (오른쪽)
		PhoenixMoveLR[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RL_)		// (왼쪽)
		PhoenixMoveRL[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

	if (heroManager.heroAttackState == TRUE)
	{
		// 공격
		if (PhoenixSpriteClass == HEROATTACK_LR_)		// 왼쪽 -> 오른쪽 방향
			PhoenixAttackLR[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RL_)		// 오른쪽 -> 왼쪽 방향
			PhoenixAttackRL[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_BT_)		// 아래 -> 위 방향
			PhoenixAttackBT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_TB_)		// 위 -> 아래 방향
			PhoenixAttackTB[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

		if (PhoenixSpriteClass == HEROATTACK_LBRT_)	// 왼쪽 아래 -> 오른쪽 위 방향
			PhoenixAttackLBRT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_LTRB_)	// 왼쪽 위 -> 오른쪽 아래 방향
			PhoenixAttackLTRB[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RBLT_)	// 오른쪽 아래 -> 왼쪽 위 방향
			PhoenixAttackRBLT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RTLB_)	// 오른쪽 위 -> 왼쪽 아래 방향
			PhoenixAttackRTLB[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	}
}

void Phoenix::MouseMoving(LPARAM lParam)
{
	curMove.m_nX = LOWORD(lParam);
	curMove.m_nY = HIWORD(lParam);
	PhoenixCol = HERO_MOVE;
	COL = TRUE;
	curMove.speed = 1.5f;
}

void Phoenix::Reset()
{
	curMove.InitX = 1000.0f;				// 캐릭터의 X 좌표
	curMove.InitY = 400.0f;					// 캐릭터의 Y 좌표
	curMove.speed = 1.5f;					// 캐릭터 이동속도
	curMove.nX = curMove.InitX;				// 현재 캐릭터 X 위치
	curMove.nY = curMove.InitY;				// 현재 캐리터 Y 위치
}
