#pragma once
#include "Include.h"

typedef struct HeroMove2		// �����̵�
{
	double InitX, InitY;	// ĳ���� �ʱ� ��ġ
	double nX, nY;			// ������ġ
	double m_nX, m_nY;		// ĳ���Ͱ� ���� �϶� �޾ƿ� ����
	double speed;			// ĳ���Ͱ� �̵��� �ӵ�
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
	// �̵�
	Sprite RaynorMoveLR[9];	// ����
	Sprite RaynorMoveRL[9];	// ������
	Sprite RaynorMoveBT[9];	// ����
	Sprite RaynorMoveTB[9];	// �Ʒ���
	Sprite RaynorMoveLBRT[9];	// ������ �� �밢��
	Sprite RaynorMoveLTRB[9];	// ������ �Ʒ� �밢��
	Sprite RaynorMoveRBLT[9];	// ���� �� �밢��
	Sprite RaynorMoveRTLB[9];	// ���� �Ʒ� �밢��

	// ����
	Sprite RaynorAttackLR[3];	// ����
	Sprite RaynorAttackRL[3];	// ������
	Sprite RaynorAttackBT[3];	// ����
	Sprite RaynorAttackTB[3];	// �Ʒ���
	Sprite RaynorAttackLBRT[3];	// ������ �� �밢��
	Sprite RaynorAttackLTRB[3];	// ������ �Ʒ� �밢��
	Sprite RaynorAttackRBLT[3];	// ���� �� �밢��
	Sprite RaynorAttackRTLB[3];	// ���� �Ʒ� �밢��

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