#pragma once
#include "Include.h"

typedef struct HeroMove1		// �����̵�
{
	double InitX, InitY;	// ĳ���� �ʱ� ��ġ
	double nX, nY;			// ������ġ
	double m_nX, m_nY;		// ĳ���Ͱ� ���� �϶� �޾ƿ� ����
	double speed;			// ĳ���Ͱ� �̵��� �ӵ�
};

class Phoenix
{
private:
	DWORD m_PhoenixAniTime;
	DWORD m_PhoenixMoveTime;
	DWORD m_PhoenixAttackAniTime;
	int m_PhoenixCount;
	int skill;					// ��ų���
	double distance;
	BOOL DrawColl;
	int PhoenixCol;

public:
	Sprite PhoenixMoveLR[8];	// ����
	Sprite PhoenixMoveRL[8];	// ������
	Sprite PhoenixMoveBT[8];	// ����
	Sprite PhoenixMoveTB[8];	// �Ʒ���
	Sprite PhoenixMoveLBRT[8];	// ������ �� �밢��
	Sprite PhoenixMoveLTRB[8];	// ������ �Ʒ� �밢��
	Sprite PhoenixMoveRBLT[8];	// ���� �� �밢��
	Sprite PhoenixMoveRTLB[8];	// ���� �Ʒ� �밢��

	// ���� ����
	Sprite PhoenixAttackLR[8];		// ����
	Sprite PhoenixAttackRL[8];		// ������
	Sprite PhoenixAttackBT[8];		// ����
	Sprite PhoenixAttackTB[8];		// �Ʒ���
	Sprite PhoenixAttackLBRT[8];	// ������ �� �밢��
	Sprite PhoenixAttackLTRB[8];	// ������ �Ʒ� �밢��
	Sprite PhoenixAttackRBLT[8];	// ���� �� �밢��
	Sprite PhoenixAttackRTLB[8];	// ���� �Ʒ� �밢��

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