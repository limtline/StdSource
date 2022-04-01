#include "Include.h"

Skill h_skill;

extern vector<EnemyManager> zg_Manager;
extern vector<EnemyManager> m_Manager;
extern vector<EnemyManager> zl_Manager;
extern vector<DeadPosition> deadPosition;
extern DeadPosition curPosition;

Skill::Skill()
{
	skillX = 0;
	skillY = 0;
	skillPlagueTime = GetTickCount64();
	skillStormTime = GetTickCount64();
	skillWepTime = GetTickCount64();
	plagueSpriteCount = 0;
	stormSpriteCount = 0;
	wepSpriteCount = 0;

	skillAttack = 10;

	distance = 0;
	skillSet = FALSE;
	skillAct = FALSE;
}

Skill::~Skill()
{
}

void Skill::Init()
{
	skillX = 0;
	skillY = 0;
	skillPlagueTime = GetTickCount64();
	skillStormTime = GetTickCount64();
	skillWepTime = GetTickCount64();
	plagueSpriteCount = 0;
	stormSpriteCount = 0;
	wepSpriteCount = 0;
	skillAttack = 10;

	distance = 0;
	skillSet = FALSE;
	skillAct = FALSE;

	char FileName[256];
	
	// ÇÃ·¹ÀÌ±×
	for (int i = 0; i < 11; i++) {
		sprintf_s(FileName, "./resource/Skill/Plague_done/plague%d.png", i);
		plague[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// ½ºÅè
	for (int i = 0; i < 18; i++) {
		sprintf_s(FileName, "./resource/Skill/Storm_done/storm%d.png", i);
		storm[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// À¥
	for (int i = 0; i < 15; i++) {
		sprintf_s(FileName, "./resource/Skill/Wep_done/wep%d.png", i);
		wep[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

}

void Skill::Update(int Enemy_Kind, BOOL& startState)
{
	if (heroManager.m_heroSel == KERRIGAN_SHOW)
	{
		// ¿µ¿õ ½ºÅ³ (ÇÃ·¹ÀÌ±×)
		if (GetTickCount64() - skillPlagueTime > 100)
		{
			plagueSpriteCount++;

			if (plagueSpriteCount > 10)
			{
				skillSet = FALSE;
				plagueSpriteCount = 0;
				skillAct = FALSE;
				skillAttack = 0;

			}

			skillPlagueTime = GetTickCount64();
		}
	}

	if (heroManager.m_heroSel == PHOENIX_SHOW)
	{
	
		// ¿µ¿õ ½ºÅ³ (½ºÅè)
		if (GetTickCount64() - skillStormTime > 70)
		{
			stormSpriteCount++;

			if (stormSpriteCount > 17)
			{
				skillSet = FALSE;
				stormSpriteCount = 0;
				skillAct = FALSE;
				skillAttack = 0;
			}
	
			skillStormTime = GetTickCount64();
		}
	}

	if (heroManager.m_heroSel == RAYNOR_SHOW)
	{
		// ¿µ¿õ ½ºÅ³ (À¥)
		if (GetTickCount64() - skillWepTime > 80)
		{
			wepSpriteCount++;

			if (wepSpriteCount > 14)
			{
				skillSet = FALSE;
				wepSpriteCount = 0;
				skillAct = FALSE;
				skillAttack = 0;
			}

			skillWepTime = GetTickCount64();
		}
	}

	if (startState == TRUE && skillAct ==TRUE)
	{
		if (Enemy_Kind == 1)
		{
			for (int i = 0; i < zg_Manager.size(); i++)
			{
				distanceZg = sqrt(pow((skillX - 126) - zg_Manager[i].emX, 2) + pow((skillY - 109) - zg_Manager[i].emY, 2));
				if (distanceZg < 140)
				{
					zg_Manager[i].hp -= skillAttack;
					if (zg_Manager[i].hp <= 0) {
						//zergling.zerglingMoveArr[zg_Manager[i].emY / 42][zg_Manager[i].emX / 42] = BG_EMPTY;
						curPosition.x = zg_Manager[i].emX;
						curPosition.y = zg_Manager[i].emY;
						curPosition.idx = 0;
						deadPosition.push_back(curPosition);
						//deathSound.EffectPlay(0);
						zg_Manager.erase(zg_Manager.begin() + i);
						userSystem.coin += userSystem.cost;
					}
					if ((zg_Manager.size() <= 0) && (enemyManager.count == enemyManager.maxCount)) {
						startState = FALSE;
						//sunkenManager[i].SetAtkState(FALSE);
						zergling.ArrInit();
					}
				}
			}
		}

		if (Enemy_Kind == 2)
		{
			for (int i = 0; i < m_Manager.size(); i++)
			{
				distanceMa = sqrt(pow((skillX - 126) - m_Manager[i].emX, 2) + pow((skillY - 109) - m_Manager[i].emY, 2));
				if (distanceMa < 140)
				{
					m_Manager[i].hp -= skillAttack;
					if (m_Manager[i].hp <= 0) {
						//zergling.zerglingMoveArr[zg_Manager[i].emY / 42][zg_Manager[i].emX / 42] = BG_EMPTY;
						curPosition.x = m_Manager[i].emX;
						curPosition.y = m_Manager[i].emY;
						curPosition.idx = 0;
						deadPosition.push_back(curPosition);
						//deathSound.EffectPlay(0);
						m_Manager.erase(m_Manager.begin() + i);
						userSystem.coin += userSystem.cost;
					}
					if ((m_Manager.size() <= 0) && (enemyManager.count == enemyManager.maxCount)) {
						startState = FALSE;
						//sunkenManager[i].SetAtkState(FALSE);
						marin.ArrInit();
					}
				}
			}
		}

		if (Enemy_Kind == 3)
		{
			for (int i = 0; i < zl_Manager.size(); i++)
			{
				distanceZl = sqrt(pow((skillX - 126) - zl_Manager[i].emX, 2) + pow((skillY - 109) - zl_Manager[i].emY, 2));
				if (distanceZl < 140)
				{
					zl_Manager[i].hp -= skillAttack;
					if (zl_Manager[i].hp <= 0) {
						//zergling.zerglingMoveArr[zg_Manager[i].emY / 42][zg_Manager[i].emX / 42] = BG_EMPTY;
						curPosition.x = zl_Manager[i].emX;
						curPosition.y = zl_Manager[i].emY;
						curPosition.idx = 0;
						deadPosition.push_back(curPosition);
						//deathSound.EffectPlay(0);
						zl_Manager.erase(zl_Manager.begin() + i);
						userSystem.coin += userSystem.cost;
					}
					if ((zl_Manager.size() <= 0) && (enemyManager.count == enemyManager.maxCount)) {
						startState = FALSE;
						//sunkenManager[i].SetAtkState(FALSE);
						zealot.ArrInit();
					}
				}
			}
		}
	}
}

void Skill::Draw()
{
	// ¿µ¿õ ½ºÅ³
	// ÇÃ·¹ÀÌ±×
	if (skill == HEROSKILL_Q_ && skillAct == TRUE && heroManager.m_heroSel == KERRIGAN_SHOW)
		plague[plagueSpriteCount].Render(skillX - 126, skillY - 109, 0, 0.7f, 0.7f);

	// ½ºÅè
	if (skill == HEROSKILL_Q_ && skillAct == TRUE && heroManager.m_heroSel == PHOENIX_SHOW)
		storm[stormSpriteCount].Render(skillX - 126, skillY - 109, 0, 0.7f, 0.7f);

	// À¥
	if (skill == HEROSKILL_Q_ && skillAct == TRUE && heroManager.m_heroSel == RAYNOR_SHOW)
		wep[wepSpriteCount] .Render(skillX - 126, skillY - 109, 0, 0.7f, 0.7f);
}

void Skill::MouseMove(LPARAM lParam)
{
	if (skillSet == FALSE)
	{
		rmX = LOWORD(lParam);
		rmY = HIWORD(lParam);
	}
}
