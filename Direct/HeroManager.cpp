#include "Include.h"

HeroManager heroManager;

vector<EnemyManager> zg_Manager;
vector<EnemyManager> m_Manager;
vector<EnemyManager> zl_Manager;
vector<DeadPosition> deadPosition;
DeadPosition curPosition;

HeroManager::HeroManager()
{
	m_heroSel = 0;
	heroSpriteClass = 0;
	m_heroMove = false;
	m_heroCol = false;
	heroAttackState = FALSE;
	distanceZl=0;
	distanceZg=0;
	distanceMa=0;
}

HeroManager::~HeroManager()
{
}

void HeroManager::Moving(double& nX, double& nY, double& m_nX, double& m_nY, double& speed,
	int& heroMoveCol, int& heroSprite)
{
	/////////////////////////////////////////////////////////////////////////
	if (heroMoveCol == HERO_MOVE)
	{
		m_heroMove = true;
		//m_heroCol = false;
		if (m_heroMove == true)
		{
			if (nX == m_nX && nY == m_nY)
			{
				kerrigan.kerriganCol = 0;
				return;
			}
			// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
			if (nX <= m_nX && nY <= m_nY)
			{
				nX += speed;
				nY += speed;
				heroSprite = HEROMOVE_LTRB_;

				if (nX == m_nX && nY <= m_nY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
				{
					heroSprite = HEROMOVE_TB_;
				}

				if (nX <= m_nX && nY == m_nY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
				{
					heroSprite = HEROMOVE_LR_;
				}
			} // if (curMove.nX <= curMove.m_nX && curMove.nY <= curMove.m_nY)

			// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
			if (nX <= m_nX && nY >= m_nY)
			{
				nX += speed;
				nY -= speed;
				heroSprite = HEROMOVE_LBRT_;

				if (nX == m_nX && nY >= m_nY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
				{
					heroSprite = HEROMOVE_BT_;
				}

				if (nX <= m_nX && nY == m_nY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
				{
					heroSprite = HEROMOVE_LR_;
				}
			} // if (curMove.nX <= curMove.m_nX && curMove.nY >= curMove.m_nY)

			// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
			if (nX >= m_nX && nY <= m_nY)
			{
				nX -= speed;
				nY += speed;
				heroSprite = HEROMOVE_RTLB_;

				if (nX == m_nX && nY <= m_nY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
				{
					heroSprite = HEROMOVE_TB_;
				}

				if (nX >= m_nX && nY == m_nY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
				{
					heroSprite = HEROMOVE_RL_;
				}
			} // if (curMove.nX >= curMove.m_nX && curMove.nY <= curMove.m_nY)

			// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
			if (nX >= m_nX && nY >= m_nY)
			{
				nX -= speed;
				nY -= speed;
				heroSprite = HEROMOVE_RBLT_;

				if (nX == m_nX && nY >= m_nY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
				{
					heroSprite = HEROMOVE_BT_;
				}

				if (nX >= m_nX && nY == m_nY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
				{
					heroSprite = HEROMOVE_RL_;
				}
			} // if (curMove.nX >= curMove.m_nX && curMove.nY >= curMove.m_nY)

		/////////////////////////////////////////////////////////////////////////
		} // if (m_heroMove == true)

	}// if (kerriganCol == HERO_MOVE)
}

void HeroManager::MonCol(double& nX, double& nY, double& speed, int& heroMoveCol, int& heroSprite, BOOL& startState)
{
	if (heroMoveCol == HEROCOL_ON)
	{
		for (int i = 0; i < zg_Manager.size(); i++)
		{
			distanceZg = (double)sqrt((zg_Manager[i].emX - nX) * (zg_Manager[i].emX - nX) + (zg_Manager[i].emY - nY) * (zg_Manager[i].emY - nY));

			if (distanceZg < 240)
			{
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= zg_Manager[i].emX && nY <= zg_Manager[i].emY)
				{
					nX += speed;
					nY += speed;
					heroSprite = HEROMOVE_LTRB_;

					if (nX == zg_Manager[i].emX && nY <= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX <= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= zg_Manager[i].emX && nY >= zg_Manager[i].emY)
				{
					nX += speed;
					nY -= speed;
					heroSprite = HEROMOVE_LBRT_;

					if (nX == zg_Manager[i].emX && nY >= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX <= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY >= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= zg_Manager[i].emX && nY <= zg_Manager[i].emY)
				{
					nX -= speed;
					nY += speed;
					heroSprite = HEROMOVE_RTLB_;

					if (nX == zg_Manager[i].emX && nY <= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX >= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= zg_Manager[i].emX && nY >= zg_Manager[i].emY)
				{
					nX -= speed;
					nY -= speed;
					heroSprite = HEROMOVE_RBLT_;

					if (nX == zg_Manager[i].emX && nY >= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX >= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY >= curMove.m_nY)
			}
			/////////////////////////////////////////////////////////////////////////

			if (distanceZg < 150)
			{
				heroAttackState = TRUE;
				zg_Manager[i].hp -= raynor.curMove.attack;

				speed = 0;
				
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= zg_Manager[i].emX && nY <= zg_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LTRB_;

					if (nX == zg_Manager[i].emX && nY <= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX <= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} //if (curMove.nX <= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= zg_Manager[i].emX && nY >= zg_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LBRT_;

					if (nX == zg_Manager[i].emX && nY >= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX <= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} // if (curMove.nX <= marin.mrX && curMove.nY >= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= zg_Manager[i].emX && nY <= zg_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RTLB_;

					if (nX == zg_Manager[i].emX && nY <= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX >= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}

				} // if (curMove.nX >= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= zg_Manager[i].emX && nY >= zg_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RBLT_;

					if (nX == zg_Manager[i].emX && nY >= zg_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX >= zg_Manager[i].emX && nY == zg_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}
				} // if (curMove.nX >= marin.mrX && curMove.nY >= marin.mrY)
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
					heroAttackState = FALSE;
					heroSprite = HEROMOVE_TB_;
				}
			} // if (distance < 50)
		}// if (heroMoveCol == HEROCOL_ON)

		for (int i = 0; i < zl_Manager.size(); i++)
		{
			distanceZl = (double)sqrt((zl_Manager[i].emX - nX) * (zl_Manager[i].emX - nX) + (zl_Manager[i].emY - nY) * (zl_Manager[i].emY - nY));

			if (distanceZl < 240)
			{
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= zl_Manager[i].emX && nY <= zl_Manager[i].emY)
				{
					nX += speed;
					nY += speed;
					heroSprite = HEROMOVE_LTRB_;

					if (nX == zl_Manager[i].emX && nY <= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX <= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= zl_Manager[i].emX && nY >= zl_Manager[i].emY)
				{
					nX += speed;
					nY -= speed;
					heroSprite = HEROMOVE_LBRT_;

					if (nX == zl_Manager[i].emX && nY >= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX <= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY >= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= zl_Manager[i].emX && nY <= zl_Manager[i].emY)
				{
					nX -= speed;
					nY += speed;
					heroSprite = HEROMOVE_RTLB_;

					if (nX == zl_Manager[i].emX && nY <= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX >= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= zl_Manager[i].emX && nY >= zl_Manager[i].emY)
				{
					nX -= speed;
					nY -= speed;
					heroSprite = HEROMOVE_RBLT_;

					if (nX == zl_Manager[i].emX && nY >= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX >= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY >= curMove.m_nY)
			}
			/////////////////////////////////////////////////////////////////////////

			if (distanceZl < 150)
			{
				heroAttackState = TRUE;
				zl_Manager[i].hp -= raynor.curMove.attack;

				speed = 0;
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= zl_Manager[i].emX && nY <= zl_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LTRB_;

					if (nX == zl_Manager[i].emX && nY <= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX <= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} //if (curMove.nX <= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= zl_Manager[i].emX && nY >= zl_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LBRT_;

					if (nX == zl_Manager[i].emX && nY >= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX <= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} // if (curMove.nX <= marin.mrX && curMove.nY >= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= zl_Manager[i].emX && nY <= zl_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RTLB_;

					if (nX == zl_Manager[i].emX && nY <= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX >= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}

				} // if (curMove.nX >= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= zl_Manager[i].emX && nY >= zl_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RBLT_;

					if (nX == zl_Manager[i].emX && nY >= zl_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX >= zl_Manager[i].emX && nY == zl_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}
				} // if (curMove.nX >= marin.mrX && curMove.nY >= marin.mrY)
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
					heroAttackState = FALSE;
					heroSprite = HEROMOVE_TB_;
				}
			} // if (distance < 50)
		}

		for (int i = 0; i < m_Manager.size(); i++)
		{
			distanceMa = (double)sqrt((m_Manager[i].emX - nX) * (m_Manager[i].emX - nX) + (m_Manager[i].emY - nY) * (m_Manager[i].emY - nY));

			if (distanceMa < 240)
			{
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= m_Manager[i].emX && nY <= m_Manager[i].emY)
				{
					nX += speed;
					nY += speed;
					heroSprite = HEROMOVE_LTRB_;

					if (nX == m_Manager[i].emX && nY <= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX <= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= m_Manager[i].emX && nY >= m_Manager[i].emY)
				{
					nX += speed;
					nY -= speed;
					heroSprite = HEROMOVE_LBRT_;

					if (nX == m_Manager[i].emX && nY >= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX <= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROMOVE_LR_;
					}
				} // if (curMove.nX <= curMove.m_nX && curMove.nY >= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= m_Manager[i].emX && nY <= m_Manager[i].emY)
				{
					nX -= speed;
					nY += speed;
					heroSprite = HEROMOVE_RTLB_;

					if (nX == m_Manager[i].emX && nY <= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROMOVE_TB_;
					}

					if (nX >= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY <= curMove.m_nY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= m_Manager[i].emX && nY >= m_Manager[i].emY)
				{
					nX -= speed;
					nY -= speed;
					heroSprite = HEROMOVE_RBLT_;

					if (nX == m_Manager[i].emX && nY >= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_BT_;
					}

					if (nX >= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROMOVE_RL_;
					}
				} // if (curMove.nX >= curMove.m_nX && curMove.nY >= curMove.m_nY)
			}
			/////////////////////////////////////////////////////////////////////////

			if (distanceMa < 150)
			{
				heroAttackState = TRUE;
				
				m_Manager[i].hp -= raynor.curMove.attack;

				speed = 0;
				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� Ŭ�� (4��и�) (������ �Ʒ� �밢��)
				if (nX <= m_Manager[i].emX && nY <= m_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LTRB_;

					if (nX == m_Manager[i].emX && nY <= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX <= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} //if (curMove.nX <= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� ũ��, ���콺 y�� ���� y���� ������ (1��и�) (������ �� �밢��)
				if (nX <= m_Manager[i].emX && nY >= m_Manager[i].emY)
				{
					heroSprite = HEROATTACK_LBRT_;

					if (nX == m_Manager[i].emX && nY >= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX <= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (������)
					{
						heroSprite = HEROATTACK_LR_;
					}

				} // if (curMove.nX <= marin.mrX && curMove.nY >= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� Ŭ�� (3��и�)	 (���� �Ʒ� �밢��)
				if (nX >= m_Manager[i].emX && nY <= m_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RTLB_;

					if (nX == m_Manager[i].emX && nY <= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� Ŭ�� (�Ʒ���)
					{
						heroSprite = HEROATTACK_TB_;
					}

					if (nX >= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}

				} // if (curMove.nX >= marin.mrX && curMove.nY <= marin.mrY)

				// ���콺 x�� ���� x ���� �۰�, ���콺 y�� ���� y���� ������ (2��и�) (���� �� �밢��)
				if (nX >= m_Manager[i].emX && nY >= m_Manager[i].emY)
				{
					heroSprite = HEROATTACK_RBLT_;

					if (nX == m_Manager[i].emX && nY >= m_Manager[i].emY)	// ���콺 x�� ���� x�� ����, ���콺 y���� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_BT_;
					}

					if (nX >= m_Manager[i].emX && nY == m_Manager[i].emY)	// ���콺 x�� ���� x���� �۰�, ���콺 y�� ���� y�� ������ (����)
					{
						heroSprite = HEROATTACK_RL_;
					}
				} // if (curMove.nX >= marin.mrX && curMove.nY >= marin.mrY)
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
					heroAttackState = FALSE;
					heroSprite = HEROMOVE_TB_;
				}
			} // if (distance < 50)
		}
	}
}

void HeroManager::HeroSelect(int sel)
{
	if (sel == KERRIGAN_SHOW)
	{
		m_heroSel = sel;
	}

	else if (sel == RAYNOR_SHOW)
	{
		m_heroSel = sel;
	}

	else if (sel == PHOENIX_SHOW)
	{
		m_heroSel = sel;
	}
}
