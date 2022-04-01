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

	// �̵�
	char FileName[256];
	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLR/raynorLR%d.png", i);	// ����
		RaynorMoveLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRL/raynorRL%d.png", i);	// ������
		RaynorMoveRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorBT/raynorBT%d.png", i);	// ����
		RaynorMoveBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorTB/raynorTB%d.png", i);	// �Ʒ���
		RaynorMoveTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLBRT/raynorLBRT%d.png", i);	// ������ �� �밢��
		RaynorMoveLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorLTRB/raynorLTRB%d.png", i);	// ������ �Ʒ� �밢��
		RaynorMoveLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRBLT/raynorRBLT%d.png", i);	// ���� �� �밢��
		RaynorMoveRBLT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/Raynor_done/raynorRTLB/raynorRTLB%d.png", i);	// ���� �Ʒ� �밢��
		RaynorMoveRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// ����
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLR/raynorAttackLR%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackLR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRL/raynorAttackRL%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackRL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttacBT/raynorAttackBT%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackBT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackTB/raynorAttackTB%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackTB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLBRT/raynorAttackLBRT%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackLBRT[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackLTRB/raynorAttackLTRB%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackLTRB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRTLB/raynorAttackRTLB%d.png", i);	// ���� �Ʒ� �밢��
		RaynorAttackRTLB[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++) {
		sprintf_s(FileName, "./resource/HeroUnit/HeroAttack/RaynorAttack/RaynorAttackRBLT/raynorAttackRBLT%d.png", i);	// ���� �Ʒ� �밢��
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
	// �̵�
	if (RaynorSpriteClass == HEROMOVE_LBRT_)	// ���� �Ʒ� -> ������ �� ����
		RaynorMoveLBRT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_LTRB_)	// ���� �� -> ������ �Ʒ� ����
		RaynorMoveLTRB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RBLT_)	// ������ �Ʒ� -> ���� �� ����
		RaynorMoveRBLT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RTLB_ || RaynorSpriteClass == HERO_IDLE_)	// ������ �� -> ���� �Ʒ� ����
		RaynorMoveRTLB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

	if (RaynorSpriteClass == HEROMOVE_BT_)		// �Ʒ� -> �� ����
		RaynorMoveBT[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_TB_)		// �� -> �Ʒ� ����
		RaynorMoveTB[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_LR_)		// ���� -> ������ ����
		RaynorMoveLR[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
	if (RaynorSpriteClass == HEROMOVE_RL_)		// ������ -> ���� ����
		RaynorMoveRL[RaynorSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

	// ����
	if (heroManager.heroAttackState == TRUE)
	{
		if (RaynorSpriteClass == HEROATTACK_LBRT_)	// ���� �Ʒ� -> ������ �� ����
			RaynorAttackLBRT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_LTRB_)	// ���� �� -> ������ �Ʒ� ����
			RaynorAttackLTRB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RBLT_)	// ������ �Ʒ� -> ���� �� ����
			RaynorAttackRBLT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RTLB_)	// ������ �� -> ���� �Ʒ� ����
			RaynorAttackRTLB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);

		if (RaynorSpriteClass == HEROATTACK_BT_)		// �Ʒ� -> �� ����
			RaynorAttackBT[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_TB_)		// �� -> �Ʒ� ����
			RaynorAttackTB[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_LR_)		// ���� -> ������ ����
			RaynorAttackLR[RaynorAttackSpriteCount].Render(curMove.nX - 25, curMove.nY - 25, 0, 0.7, 0.7);
		if (RaynorSpriteClass == HEROATTACK_RL_)		// ������ -> ���� ����
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
	curMove.InitX = 1000.0f;				// ĳ������ X ��ǥ
	curMove.InitY = 400.0f;					// ĳ������ Y ��ǥ
	curMove.speed = 1.5f;					// ĳ���� �̵��ӵ�
	curMove.attack = 10.0f;					// ĳ���� ���ݷ�
	curMove.nX = curMove.InitX;				// ���� ĳ���� X ��ġ
	curMove.nY = curMove.InitY;				// ���� ĳ���� Y ��ġ
}
