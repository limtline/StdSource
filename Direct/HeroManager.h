#pragma once
#include "Include.h"

class HeroManager
{
private:
	double distance;

public:
	int m_heroSel;				// ¿µ¿õ ¼±ÅÃ
	int heroSpriteClass;
	BOOL m_heroMove;
	BOOL m_heroCol;
	BOOL heroAttackState;
	int m_Col;
	int distanceZl;
	int distanceZg;
	int	distanceMa;

public:
	HeroManager();
	~HeroManager();

	void MonCol(double& nX, double& nY, double& speed, int& heroMoveCol, int& heroSprite,BOOL& startState);
	void Moving(double& nX, double& nY, double& m_nX, double& m_nY, double& speed, int& heroMoveCol, int& heroSprite);
	void HeroSelect(int sel);
};

extern HeroManager heroManager;