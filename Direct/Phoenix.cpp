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
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLR/phoenixLR%d.png", i);	// ���� -> ������
		PhoenixMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRL/phoenixRL%d.png", i);	// ������ -> ����
		PhoenixMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixBT/phoenixBT%d.png", i);	// �Ʒ� -> ��
		PhoenixMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixTB/phoenixTB%d.png", i);	// �� -> �Ʒ�
		PhoenixMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLBRT/phoenixLBRT%d.png", i);	// ���� �Ʒ� -> ������ ��
		PhoenixMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixLTRB/phoenixLTRB%d.png", i);	// ���� �� -> ������ �Ʒ�
		PhoenixMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRBLT/phoenixRBLT%d.png", i);	// ������ �Ʒ� -> ���� ��
		PhoenixMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Phoenix_done/phoenixRTLB/phoenixRTLB%d.png", i);	// ������ �� -> ���� �Ʒ�
		PhoenixMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// ����
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLR/phoenixAttackLR%d.png", i);	// ���� -> ������
		PhoenixAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRL/phoenixAttackRL%d.png", i);	// ������ -> ����
		PhoenixAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackBT/phoenixAttackBT%d.png", i);	// ���� -> �Ʒ���
		PhoenixAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackTB/phoenixAttackTB%d.png", i);	// �Ʒ��� -> ����
		PhoenixAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLBRT/phoenixAttackLBRT%d.png", i);	// ���� �Ʒ� -> ������ ��
		PhoenixAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackLTRB/phoenixAttackLTRB%d.png", i);	// ���� �� -> ������ �Ʒ�
		PhoenixAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRBLT/phoenixAttackRBLT%d.png", i);	// ������ �Ʒ� -> ���� ��
		PhoenixAttackRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 8; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/PhoenixAttack/PhoenixAttackRTLB/phoenixAttackRTLB%d.png", i);	// ������ �� -> ���� �Ʒ�
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
	// �̵�
	if (PhoenixSpriteClass == HEROMOVE_LBRT_)	// (������ �� �밢��)
		PhoenixMoveLBRT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_LTRB_)	// (������ �Ʒ� �밢��)
		PhoenixMoveLTRB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RBLT_)	// (���� �� �밢��)
		PhoenixMoveRBLT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RTLB_ || PhoenixSpriteClass == HERO_IDLE_)	// (���� �Ʒ� �밢��)
		PhoenixMoveRTLB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

	if (PhoenixSpriteClass == HEROMOVE_BT_)		// (����)
		PhoenixMoveBT[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_TB_)		// (�Ʒ���)
		PhoenixMoveTB[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_LR_)		// (������)
		PhoenixMoveLR[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
	if (PhoenixSpriteClass == HEROMOVE_RL_)		// (����)
		PhoenixMoveRL[PhoenixSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

	if (heroManager.heroAttackState == TRUE)
	{
		// ����
		if (PhoenixSpriteClass == HEROATTACK_LR_)		// ���� -> ������ ����
			PhoenixAttackLR[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RL_)		// ������ -> ���� ����
			PhoenixAttackRL[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_BT_)		// �Ʒ� -> �� ����
			PhoenixAttackBT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_TB_)		// �� -> �Ʒ� ����
			PhoenixAttackTB[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);

		if (PhoenixSpriteClass == HEROATTACK_LBRT_)	// ���� �Ʒ� -> ������ �� ����
			PhoenixAttackLBRT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_LTRB_)	// ���� �� -> ������ �Ʒ� ����
			PhoenixAttackLTRB[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RBLT_)	// ������ �Ʒ� -> ���� �� ����
			PhoenixAttackRBLT[PhoenixAttackSpriteCount].Render(curMove.nX - 32, curMove.nY - 32, 0, 0.7, 0.7);
		if (PhoenixSpriteClass == HEROATTACK_RTLB_)	// ������ �� -> ���� �Ʒ� ����
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
	curMove.InitX = 1000.0f;				// ĳ������ X ��ǥ
	curMove.InitY = 400.0f;					// ĳ������ Y ��ǥ
	curMove.speed = 1.5f;					// ĳ���� �̵��ӵ�
	curMove.nX = curMove.InitX;				// ���� ĳ���� X ��ġ
	curMove.nY = curMove.InitY;				// ���� ĳ���� Y ��ġ
}
