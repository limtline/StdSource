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
	// ���� �̵� ���
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLR/kerriganLR%d.png", i);	// ����
		KerriganMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRL/kerriganRL%d.png", i);	// ������
		KerriganMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganBT/kerriganBT%d.png", i);	// ����
		KerriganMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganTB/kerriganTB%d.png", i);	// �Ʒ���
		KerriganMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLBRT/kerriganLBRT%d.png", i);	// ������ �� �밢��
		KerriganMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganLTRB/kerriganLTRB%d.png", i);	// ������ �Ʒ� �밢��
		KerriganMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRBLT/kerriganRBLT%d.png", i);	// ���� �� �밢��
		KerriganMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Kerrigan_done/KerriganRTLB/kerriganRTLB%d.png", i);	// ���� �Ʒ� �밢��
		KerriganMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// ���� ����
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLR/kerriganAttackLR%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRL/kerriganAttackRL%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackBT/kerriganAttackBT%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackTB/kerriganAttackTB%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLBRT/kerriganAttackLBRT%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackLTRB/kerriganAttackLTRB%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRBLT/kerriganAttackRBLT%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 7; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/KerriganAttack/KerriganAttackRTLB/kerriganAttackRTLB%d.png", i);	// ���� �Ʒ� �밢��
		KerriganAttackRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Kerrigan::Update(int Enemy_Kind, BOOL& startState)
{
	// ���� �̵�
	if (GetTickCount64() - m_KerriganAniTime > 100)
	{
		kerriganSpriteCount++;
		if (kerriganSpriteCount > 7) kerriganSpriteCount = 0;
		m_KerriganAniTime = GetTickCount64();
	}

	// ���� ����
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

	// ���� �̵�
	if (kerriganSpriteClass == HEROMOVE_LBRT_)		// ���� �Ʒ� -> ������ �� ����
		KerriganMoveLBRT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_LTRB_)		// ���� �� -> ������ �Ʒ� ����
		KerriganMoveLTRB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RBLT_)		// ������ �Ʒ� -> ���� �� ����
		KerriganMoveRBLT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RTLB_ || kerriganSpriteClass == HERO_IDLE_)		// ������ �� -> ���� �Ʒ� ����
		KerriganMoveRTLB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);

	if (kerriganSpriteClass == HEROMOVE_BT_)		// �Ʒ� -> �� ����
		KerriganMoveBT[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_TB_)		// �� -> �Ʒ� ����
		KerriganMoveTB[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_LR_)		// ���� -> ������ ����
		KerriganMoveLR[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	if (kerriganSpriteClass == HEROMOVE_RL_)		// ������ -> ���� ����
		KerriganMoveRL[kerriganSpriteCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);


	if (heroManager.heroAttackState == TRUE)
	{
		// ���� ����
		if (kerriganSpriteClass == HEROATTACK_LR_)		// ���� -> ������ ����
			KerriganAttackLR[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RL_)		// ������ -> ���� ����
			KerriganAttackRL[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_BT_)		// �Ʒ� -> �� ����
			KerriganAttackBT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_TB_)		// �� -> �Ʒ� ����
			KerriganAttackTB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);

		if (kerriganSpriteClass == HEROATTACK_LBRT_)	// ���� �Ʒ� -> ������ �� ����
			KerriganAttackLBRT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_LTRB_)	// ���� �� -> ������ �Ʒ� ����
			KerriganAttackLTRB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RBLT_)	// ������ �Ʒ� -> ���� �� ����
			KerriganAttackRBLT[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
		if (kerriganSpriteClass == HEROATTACK_RTLB_)	// ������ �� -> ���� �Ʒ� ����
			KerriganAttackRTLB[kerriganAttackCount].Render(curMove.nX - 35, curMove.nY - 35, 0, 0.7, 0.7);
	}
}

void Kerrigan::MouseMoving(LPARAM lParam)			// nX,nY ���콺 ��ǥ�� �޾ƿ�
{
	curMove.m_nX = LOWORD(lParam);
	curMove.m_nY = HIWORD(lParam);
	kerriganCol = HERO_MOVE;
	COL = TRUE;
	curMove.speed = 1.5f;
}

void Kerrigan::Reset()
{
	curMove.InitX = 1000.0f;				// ĳ������ X ��ǥ
	curMove.InitY = 400.0f;					// ĳ������ Y ��ǥ
	curMove.speed = 1.5f;					// ĳ���� �̵��ӵ�
	curMove.nX = curMove.InitX;				// ���� ĳ���� X ��ġ
	curMove.nY = curMove.InitY;				// ���� ĳ���� Y ��ġ
}