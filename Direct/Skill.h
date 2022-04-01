#pragma once
#include "Include.h"

class Skill
{
private:
	DWORD skillPlagueTime;
	DWORD skillStormTime;
	DWORD skillWepTime;

public:
	BOOL skillSet;
	BOOL skillAct;

	// 스킬
	Sprite plague[11];
	Sprite storm[18];
	Sprite wep[15];

	int skill;
	// 스킬 스프라이트 갯수
	int plagueSpriteCount;
	int stormSpriteCount;
	int wepSpriteCount;

	int skillAttack;

	int distanceZl;
	int distanceZg;
	int	distanceMa;
	int distance;

	double skillX;
	double skillY;
	double rmX, rmY;

public:
	Skill();
	~Skill();

	void Init();
	void Update(int Enemy_Kind, BOOL& startState);
	void Draw();
	void MouseMove(LPARAM lParam);

};

extern Skill h_skill;
