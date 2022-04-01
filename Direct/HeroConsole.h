#pragma once
#include "Include.h"

class HeroConsole
{
public:
	// ĳ���� �ʻ�ȭ
	Sprite kerriganPortrait;
	Sprite kerriganHighlight;
	Sprite kerriganClick;
	// ĳ���� �ʻ�ȭ

	// ���̳� �ʻ�ȭ
	Sprite raynorPortrait;
	Sprite raynorHighlight;
	Sprite raynorClick;
	// ���̳� �ʻ�ȭ

	// �Ǵн� �ʻ�ȭ
	Sprite phoenixPortrait;
	Sprite phoenixHighlight;
	Sprite phoenixClick;
	// �Ǵн� �ʻ�ȭ

	Sprite heroBG;			// ���
	Sprite choose;			// �۾�

	int heroDraw;			// ���� �ʻ�ȭ ����
	int mX, mY;				// ���콺 ��ġ

public:
	HeroConsole();
	~HeroConsole();

	BOOL portrait;

	void Init();
	void Update();
	void Draw();
	//void OnMessage(MSG* msg);	

	void DrawHero(int mX, int mY, int show);	// ���콺 ��ġ�� ���� �ʻ�ȭ
};

extern HeroConsole heroC;