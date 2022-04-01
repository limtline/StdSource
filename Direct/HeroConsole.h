#pragma once
#include "Include.h"

class HeroConsole
{
public:
	// 캐리건 초상화
	Sprite kerriganPortrait;
	Sprite kerriganHighlight;
	Sprite kerriganClick;
	// 캐리건 초상화

	// 레이너 초상화
	Sprite raynorPortrait;
	Sprite raynorHighlight;
	Sprite raynorClick;
	// 레이너 초상화

	// 피닉스 초상화
	Sprite phoenixPortrait;
	Sprite phoenixHighlight;
	Sprite phoenixClick;
	// 피닉스 초상화

	Sprite heroBG;			// 배경
	Sprite choose;			// 글씨

	int heroDraw;			// 영웅 초상화 선택
	int mX, mY;				// 마우스 위치

public:
	HeroConsole();
	~HeroConsole();

	BOOL portrait;

	void Init();
	void Update();
	void Draw();
	//void OnMessage(MSG* msg);	

	void DrawHero(int mX, int mY, int show);	// 마우스 위치에 따른 초상화
};

extern HeroConsole heroC;