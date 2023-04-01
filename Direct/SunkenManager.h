#pragma once
#include "Sunken.h"

class SunkenManager{
private:
	int nX, nY;
	int spX, spY;
	float sX, sY;
	int radian;
	BOOL drawState;

	int spriteIdx;
	BOOL enemyDetect;
	BOOL atkState;
	BOOL AttackLock;

	int damage;
public:
	DWORD m_SKManagerAniTime;
	SunkenManager();
	SunkenManager(/*Sunken,*/int _nX, int _nY, int radian, float sX, float sY, BOOL _drawState, BOOL _enemyDetect);
	//SunkenManager(SunkenManager& sunkenManager);
	~SunkenManager();

	//Sunken GetSunken();
	int GetnX();
	int GetnY();
	int GetspX();
	int GetspY();
	int GetRadian();
	float GetsX();
	float GetsY();
	int GetSPRIDX();
	BOOL GetDetect();
	ULONGLONG GetTime();
	BOOL GetAttackLock();
	int GetDamage();
	BOOL GetAtkState();

	//void SetSunken(Sunken);s
	void SetnX(int);
	void SetnY(int);
	void SetspX(int);
	void SetspY(int);
	void SetRadian(int);
	void SetsX(float);
	void SetsY(float);
	void SetSPRIDX(int);
	void SetDetect(BOOL);
	void SetTime(DWORD);
	void SetAttackLock(BOOL);
	void SetDamage(int);
	void SetAtkState(BOOL);


	void Init(SunkenManager* sunkenManager, int idx);
	BOOL EnemyCheck_Test(int Enemy_Kind, SunkenManager& skmanager);
	void Update();
};

//extern vector<SunkenManager> sunkenManager;