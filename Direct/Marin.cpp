#include "Include.h"

Marin marin;
extern vector<EnemyManager> m_Manager;


Marin::Marin()
{
	marin_BG = FALSE;
	m_MarinAniTime = 0;
	m_MarinCount = 0;
	strcpy(Fname, "");
	curX = 0, curY = 0;
	mrX = 0, mrY = 0;
}

Marin::~Marin()
{

}

void Marin::Init()
{
	Timer = 0;
	for (int i = 0; i < 9; i++)
	{
		sprintf_s(Fname, "./resource/EnemyUnit/Marin_done/marinLR/marinLR%d.png", i);
		MarinRightImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++)
	{
		sprintf_s(Fname, "./resource/EnemyUnit/Marin_done/marinRL/marinRL%d.png", i);
		MarinLeftImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++)
	{
		sprintf_s(Fname, "./resource/EnemyUnit/Marin_done/marinTB/marinTB%d.png", i);
		MarinDownImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 9; i++)
	{
		sprintf_s(Fname, "./resource/EnemyUnit/Marin_done/marinBT/marinBT%d.png", i);
		MarinUpImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 12; i++)
	{
		sprintf_s(Fname, "./resource/EnemyUnit/Marin_done/marinDie/marinDie%d.png", i);
		MarinDieImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	FullHP.Create("./resource/EnemyUnit/hpFull05.png", false, D3DCOLOR_XRGB(0, 0, 0));
	MidHP.Create("./resource/EnemyUnit/hpMid05.png", false, D3DCOLOR_XRGB(0, 0, 0));
	LowHP.Create("./resource/EnemyUnit/hpLow05.png", false, D3DCOLOR_XRGB(0, 0, 0));
	//memcpy(marinMoveArr, m_map.backGroundArr, sizeof(m_map.backGroundArr));
	enemyManager.maxCount = 10;
	enemyManager.Enemy_Activate = FALSE;
	//m_Manager.push_back(enemyManager);
}

void Marin::Update()
{

	if (GetTickCount64() - m_MarinAniTime > 25)
	{
		m_MarinCount++;
		if (m_MarinCount > 8) m_MarinCount = 0;
		m_MarinAniTime = GetTickCount64();
	}

	if (enemyManager.count < enemyManager.maxCount && enemyManager.EnemyExist == TRUE) {
		if (GetTickCount64() - Timer > 1000) {
			enemyManager.emX = 0;
			enemyManager.emY = 0;
			enemyManager.move_direction = MOVE_INIT;
			enemyManager.count += 1;
			enemyManager.objTrace_idx = 0;
			enemyManager.Enemy_Activate = TRUE;
			enemyManager.hp = enemyManager.max_hp;
			m_Manager.push_back(enemyManager);
			Timer = GetTickCount64();
			
		}
	}
	

	for (int i = 0; i < m_Manager.size(); i++) {
		if (Trace[m_Manager[i].objTrace_idx].d == 1) {
			m_Manager[i].emX += 3;
			if (m_Manager[i].emX / 42 > Trace[m_Manager[i].objTrace_idx].x)
				m_Manager[i].objTrace_idx += 1;
		}
		else if (Trace[m_Manager[i].objTrace_idx].d == 2) {
			m_Manager[i].emY += 3;
			if (m_Manager[i].emY / 42 > Trace[m_Manager[i].objTrace_idx].y)
				m_Manager[i].objTrace_idx += 1;
		}
		else if (Trace[m_Manager[i].objTrace_idx].d == 3) {
			m_Manager[i].emX -= 3;
			if (m_Manager[i].emX < Trace[m_Manager[i].objTrace_idx].x * 42 - 41)
				m_Manager[i].objTrace_idx += 1;
		}
		else if (Trace[m_Manager[i].objTrace_idx].d == 4) {
			m_Manager[i].emY -= 3;
			if ((m_Manager[i].emY < Trace[m_Manager[i].objTrace_idx].y * 42 - 41))
				m_Manager[i].objTrace_idx += 1;
		}

		if (m_Manager[i].emX >= 1176) {
			m_Manager[i].EnemyExist = FALSE;
			m_Manager[i].emX += 3;
		}
		if (m_Manager[i].emX >= 1280) {
			m_Manager.erase(m_Manager.begin() + i);
			userSystem.userHp -= 1;
			if(m_Manager.size() == 0) {
				enemyManager.count = 0;
				enemyManager.EnemyExist = FALSE;
				enemyManager.Enemy_Activate = FALSE;
				ArrInit();
			}
		}
	}
}

void Marin::Draw(int mx, int my)
{
	memcpy(marinMoveArr, m_map.backGroundArr, sizeof(m_map.backGroundArr));
	for (int i = 0; i < m_Manager.size(); i++) {
		if (m_Manager[i].EnemyExist == TRUE) {
			curX = m_Manager[i].emX / 42;
			curY = m_Manager[i].emY / 42;
			if(Trace[m_Manager[i].objTrace_idx].d == 1)
				MarinRightImg[m_MarinCount].Render(m_Manager[i].emX, m_Manager[i].emY, 0, 0.6, 0.6);
			else if (Trace[m_Manager[i].objTrace_idx].d == 2)
				MarinDownImg[m_MarinCount].Render(m_Manager[i].emX, m_Manager[i].emY, 0, 0.6, 0.6);
			else if (Trace[m_Manager[i].objTrace_idx].d == 3)
				MarinLeftImg[m_MarinCount].Render(m_Manager[i].emX, m_Manager[i].emY, 0, 0.6, 0.6);
			else if (Trace[m_Manager[i].objTrace_idx].d == 4)
				MarinUpImg[m_MarinCount].Render(m_Manager[i].emX, m_Manager[i].emY, 0, 0.6, 0.6);
			marinMoveArr[curY][curX] = BG_ENEMY;
			for (int j = 0; j < m_Manager[i].hp; j+=10) {
				if (m_Manager[i].hp > 70)
					FullHP.Render(m_Manager[i].emX - 10 + (j/10 * 5), m_Manager[i].emY + 45, 0, 1, 1);
				else if (m_Manager[i].hp > 30)
					MidHP.Render(m_Manager[i].emX - 10 + (j/10 * 5), m_Manager[i].emY + 45, 0, 1, 1);
				else
					LowHP.Render(m_Manager[i].emX - 10 + (j/10 * 5), m_Manager[i].emY + 45, 0, 1, 1);
			}
		}	
	}
}

void Marin::ArrInit()
{
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 30; j++) {
			marinMoveArr[i][j] = BG_EMPTY;
		}
	}
}