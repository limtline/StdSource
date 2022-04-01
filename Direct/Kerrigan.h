#pragma once
#include "Include.h"

typedef struct HeroMove		// �����̵�
{
	double InitX, InitY;	// ĳ���� �ʱ� ��ġ
	double nX, nY;			// ������ġ
	double m_nX, m_nY;		// ĳ���Ͱ� ���� �϶� �޾ƿ� ����
	double speed;			// ĳ���Ͱ� �̵��� �ӵ�
};

class Kerrigan {
private:
	DWORD m_KerriganAniTime;
	DWORD m_KerriganAttackTime;
	int kerriganSpriteCount;
	int kerriganAttackCount;
	double distance;

public:
	// ���� �̵�
	Sprite KerriganMoveLR[8];	// ����
	Sprite KerriganMoveRL[8];	// ������
	Sprite KerriganMoveBT[8];	// ����
	Sprite KerriganMoveTB[8];	// �Ʒ���
	Sprite KerriganMoveLBRT[8];	// ������ �� �밢��
	Sprite KerriganMoveLTRB[8];	// ������ �Ʒ� �밢��
	Sprite KerriganMoveRBLT[8];	// ���� �� �밢��
	Sprite KerriganMoveRTLB[8];	// ���� �Ʒ� �밢��

	// ���� ����
	Sprite KerriganAttackLR[8];		// ����
	Sprite KerriganAttackRL[8];		// ������
	Sprite KerriganAttackBT[8];		// ����
	Sprite KerriganAttackTB[8];		// �Ʒ���
	Sprite KerriganAttackLBRT[8];	// ������ �� �밢��
	Sprite KerriganAttackLTRB[8];	// ������ �Ʒ� �밢��
	Sprite KerriganAttackRBLT[8];	// ���� �� �밢��
	Sprite KerriganAttackRTLB[8];	// ���� �Ʒ� �밢��

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