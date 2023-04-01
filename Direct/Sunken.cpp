#include "Include.h"

Sunken sunken;
vector<SunkenManager> sunkenManager;
extern vector<EnemyManager> zg_Manager;
extern vector<EnemyManager> m_Manager;
extern vector<EnemyManager> zl_Manager;
extern vector<DeadPosition> deadPosition;
extern DeadPosition curPosition;
extern FmodSound deathSound;
FmodSound SunkenAttackSound;
FmodSound buildSound;


Sunken::Sunken()
{
	m_SunkenAniTime = 0;
	m_SunkenCount = 0;
	m_SunkenSpineCount = 0;
	active_sunkenspine = FALSE;
	m_AttackDelay = 0;
	m_KillTime = 0;
}

Sunken::Sunken(Sunken& sunken)
{
	m_SunkenAniTime = sunken.m_SunkenAniTime;
	m_SunkenCount = sunken.m_SunkenCount;
	this->SunkenImg = sunken.SunkenImg;
}

Sunken& Sunken::operator=(const Sunken& sk)
{
	m_SunkenAniTime = sunken.m_SunkenAniTime;
	m_SunkenCount = sunken.m_SunkenCount;
	this->SunkenImg = sk.SunkenImg;

	return *this;
}

Sunken::~Sunken()
{
}

void Sunken::Init()
{
	char FileName[256];

	SunkenImg.Create("./resource/Building/Sunken_done/sunken0.png", false, D3DCOLOR_XRGB(0, 0, 0));

	for (int i = 0; i < 21; i++) {
		sprintf_s(FileName, "./resource/Building/Sunken_done/sunken%d.png", i);
		SunkenAttack[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	SunkenEnable.Create("./resource/Building/Sunken_done/sunken_building_possible.png", false, D3DCOLOR_XRGB(0, 0, 0));
	SunkenDiable.Create("./resource/Building/Sunken_done/sunken_builing_impossible.png", false, D3DCOLOR_XRGB(0, 0, 0));

	for (int i = 0; i < 21; i++) {
		sprintf_s(FileName, "./resource/Building/Sunken_done/skattack/sunken_spine%d.png", i);
		SunkenSpine[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	deathSound.Init();
	SunkenAttackSound.Init();

	AttackLock = FALSE;
	m_KillTime = 0;
	deathSound.AddSoundFile("./resource/Sound/zerglingDeathSound.mp3", false);
	deathSound.AddSoundFile("./resource/Sound/marinDeathSound.mp3", false);
	deathSound.AddSoundFile("./resource/Sound/zealotDeathSound.mp3", false);
	SunkenAttackSound.AddSoundFile("./resource/Sound/sunkenAttackSound.mp3", false);
	buildSound.AddSoundFile("./resource/Sound/ZergBuildingSound.mp3", false);

	/*for (int i = 0; i < sunkenManager.size(); i++) sunkenManager.erase(sunkenManager.begin() + i);
	for (int i = 0; i < zg_Manager.size(); i++) zg_Manager.erase(zg_Manager.begin() + i);
	for (int i = 0; i < m_Manager.size(); i++) m_Manager.erase(m_Manager.begin() + i);
	for (int i = 0; i < zl_Manager.size(); i++) zl_Manager.erase(zl_Manager.begin() + i);
	for (int i = 0; i < deadPosition.size(); i++) deadPosition.erase(deadPosition.begin() + i);*/

	sunkenManager.clear();
	zg_Manager.clear();
	m_Manager.clear();
	zl_Manager.clear();
	deadPosition.clear();

	curPosition.Init();

}

void Sunken::Update(int Enemy_Kind, BOOL& startState)
{
	if (GetTickCount64() - m_SunkenAniTime > 100)
	{
		m_SunkenCount++;
		if (m_SunkenCount > 21) {
			m_SunkenCount = 0;
		}
		m_SunkenAniTime = GetTickCount64();
	}

	for (int i = 0; i < deadPosition.size(); i++)
	{
		if (GetTickCount64() - m_KillTime > 25)
		{
			deadPosition[i].idx++;
			if (Enemy_Kind == 1) {
				if (deadPosition[i].idx > 9) deadPosition.erase(deadPosition.begin() + i);
			}
			if (Enemy_Kind == 2) {
				if (deadPosition[i].idx > 11) deadPosition.erase(deadPosition.begin() + i);
			}
			if (Enemy_Kind == 3) {
				if (deadPosition[i].idx > 10) deadPosition.erase(deadPosition.begin() + i);
			}
			m_KillTime = GetTickCount64();
		}
	}

	// �� ������ ��� Update ����

	// ���� ������ üũ - ���� �������Ŀ� �����
	// 1. ��ū�� ���������� ���� ���� ���� �׻� �����Ǿ��ִ�.
	// 2. Lock ���°� False�� ��쿡 �˻縦 �����ϰ� ��� �����·� ��ȯ�ȴ�. ���� �߰ߵ��� �ʾ��� ��� 1������ �ٽ� ����.
	// 3. �˻縦 �ѹ� �����ϰ� ���� �߰ߵǾ��ٸ� ��� ���� �ɷ� ��˻縦 �������� �ʴ´�.
	if (startState == TRUE) {
		for (int i = 0; i < sunkenManager.size(); i++) {
			if (sunkenManager[i].GetAttackLock() == FALSE) {
				sunkenManager[i].EnemyCheck_Test(Enemy_Kind, sunkenManager[i]);

				sunkenManager[i].SetAttackLock(TRUE);
			}

			if (sunkenManager[i].GetDetect() == TRUE) {
				if (Enemy_Kind == 1) { // zergling
					for (int j = 0; j < zg_Manager.size(); j++) {
						if (((zg_Manager[j].emX / 42) == (sunkenManager[i].GetspX() / 42)) && ((zg_Manager[j].emY / 42) == (sunkenManager[i].GetspY() / 42)))
						{
							zg_Manager[j].hp -= sunkenManager[i].GetDamage();
							if (zg_Manager[j].hp <= 0) {
								zergling.zerglingMoveArr[zg_Manager[j].emY / 42][zg_Manager[j].emX / 42] = BG_EMPTY;
								curPosition.x = zg_Manager[j].emX;
								curPosition.y = zg_Manager[j].emY;
								curPosition.idx = 0;
								deadPosition.push_back(curPosition);
								deathSound.EffectPlay(0);
								zg_Manager.erase(zg_Manager.begin() + j);
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
				if (Enemy_Kind == 2) { // marin
					for (int j = 0; j < m_Manager.size(); j++) {
						if (((m_Manager[j].emX / 42) == (sunkenManager[i].GetspX() / 42)) && ((m_Manager[j].emY / 42) == (sunkenManager[i].GetspY() / 42)))
						{
							m_Manager[j].hp -= sunkenManager[i].GetDamage();
							if (m_Manager[j].hp <= 0) {
								marin.marinMoveArr[m_Manager[j].emY / 42][m_Manager[j].emX / 42] = BG_EMPTY;
								curPosition.x = m_Manager[j].emX;
								curPosition.y = m_Manager[j].emY;
								curPosition.idx = 0;
								deadPosition.push_back(curPosition);
								deathSound.EffectPlay(1);
								m_Manager.erase(m_Manager.begin() + j);
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
				if (Enemy_Kind == 3) { // zealot
					for (int j = 0; j < zl_Manager.size(); j++) {
						if (((zl_Manager[j].emX / 42) == (sunkenManager[i].GetspX() / 42)) && ((zl_Manager[j].emY / 42) == (sunkenManager[i].GetspY() / 42)))
						{
							zl_Manager[j].hp -= sunkenManager[i].GetDamage();
							if (zl_Manager[j].hp <= 0) {
								zealot.zealotMoveArr[zl_Manager[j].emY / 42][zl_Manager[j].emX / 42] = BG_EMPTY;
								curPosition.x = zl_Manager[j].emX;
								curPosition.y = zl_Manager[j].emY;
								curPosition.idx = 0;
								deadPosition.push_back(curPosition);
								deathSound.EffectPlay(2);
								zl_Manager.erase(zl_Manager.begin() + j);
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
	}

	if (startState == FALSE) {
		for (int i = 0; i < sunkenManager.size(); i++) {
			sunkenManager[i].SetAtkState(FALSE);
		}
		enemyManager.count = 0;
		enemyManager.EnemyExist = FALSE;
		enemyManager.Enemy_Activate = FALSE;
		curPosition.Init();
	}

	// ��ū Manager vector ũ�⸸ŭ loop�� �����Ͽ� �� index���� ������ update, ��¿� ����
	for (int i = 0; i < sunkenManager.size(); i++) {
		if (sunkenManager[i].GetAtkState() == TRUE) { // Detect�����̸� ���� ��ü Sprite ���
			if (GetTickCount64() - sunkenManager[i].GetTime() > 50)
			{
				sunkenManager[i].SetSPRIDX(sunkenManager[i].GetSPRIDX() + 1);

				if (sunkenManager[i].GetSPRIDX() > 20) {
					sunkenManager[i].SetSPRIDX(0);
					sunkenManager[i].SetAttackLock(TRUE);
				}
				if (sunkenManager[i].GetSPRIDX() == 20) {
					sunkenManager[i].SetAttackLock(FALSE);
				}

				sunkenManager[i].SetTime(GetTickCount64());

			}
		}

		else if (sunkenManager[i].GetAtkState() == FALSE) { // Detect ���°� �ƴϸ� 0~1�� ��������Ʈ �ݺ� ���
			if (GetTickCount64() - sunkenManager[i].GetTime() > 50)
			{
				sunkenManager[i].SetSPRIDX(sunkenManager[i].GetSPRIDX() + 1);

				if (sunkenManager[i].GetSPRIDX() > 1) {
					sunkenManager[i].SetSPRIDX(0);
				}

				sunkenManager[i].SetTime(GetTickCount64());
			}
			sunkenManager[i].SetAttackLock(FALSE);
		}
	}
}

// Function : Draw(�׸��� ����, Ŭ��x, Ŭ��y, ??, �׸��� ���� ����, ����� ����)
// ��ū�� �׸��� ���� �Լ�
void Sunken::Draw(BOOL drawState, int nX, int nY, char* coordinate, BOOL drawMsMoveState, BOOL delMsMoveState, int Enemy_Kind)
{
	SunkenManager skmanager;
	int x, y;
	BOOL renderState = TRUE;
	int structure_exist = 0;
	char arr[100];
	CalculateBuildArea(&x, &y, nX, nY);	// ��ū�� ���� ������ �����
	sprintf_s(arr, "[X : %d] [Y : %d] : [BX : %d] [BY : %d]", x, y, x - 42, y - 42);
	strcpy(coordinate, arr);

	for (int i = y / 42 - 1; i <= y / 42; i++) {
		for (int j = x / 42 - 1; j <= x / 42; j++) {
			if (m_map.backGroundArr[i][j] == 0) renderState = TRUE; // ��ū�� ���� 4���� �迭 ������ 0�̶�� TRUE
			else {
				renderState = FALSE; // �ϳ��� FALSE�� ��� ���̻� �˻縦 �������� ����
				break;
			}
		}
		if (renderState == FALSE) break; // for loop ����
	}

	// �׸��� ���� ������ �� 
	if (drawMsMoveState == TRUE) {
		// renderState�� TRUE�̰� Ŭ�� ����� ���Դٸ�
		if (drawState == TRUE && renderState == TRUE) {

			buildSound.EffectPlay(0);
			
			if (userSystem.coin >= 100) {
				for (int i = y / 42 - 1; i <= y / 42; i++) {
					for (int j = x / 42 - 1; j <= x / 42; j++) {
						m_map.backGroundArr[i][j] = BG_STRUCTURE; // �迭������ ��ū�� �Ǽ� �Ǿ��ٴ� ǥ�ø� ����
					}
				}

				// skmanager�� ��ū�� ������ ��ġ�� x, y, radian, scaleX, scaleY �� �����ϰ�,
				// sunkenManager(SunkenManagerŬ���� ����)�� push back

				skmanager.SetnX(x - 42);
				skmanager.SetnY(y - 42);
				skmanager.SetRadian(0);
				skmanager.SetsX(0.5);
				skmanager.SetsY(0.5);
				skmanager.SetAttackLock(FALSE);
				skmanager.SetDamage(3);
				skmanager.SetAtkState(FALSE);
				sunkenManager.push_back(skmanager);
				userSystem.coin -= 100;
			}
		}
	}

	// ����� ��ū ������ �̿��� ��ū Sprite�� �����
	int idx = 0;
	for (auto i : sunkenManager) {
		SunkenAttack[i.GetSPRIDX()].Render(i.GetnX(), i.GetnY(), i.GetRadian(), i.GetsX(), i.GetsY());
		if (i.GetAtkState() == TRUE)
			if (i.GetSPRIDX() == 0) SunkenAttackSound.EffectPlay(0);
			SunkenSpine[i.GetSPRIDX()].Render(i.GetspX(), i.GetspY(), i.GetRadian(), i.GetsX(), i.GetsY());
		idx++;
	}

	if (deadPosition.size() > 0) {
		for (auto i : deadPosition) {
			if (Enemy_Kind == 1) zergling.ZerglingDieImg[i.idx].Render(i.x, i.y, 0, 0.6, 0.6);
			else if (Enemy_Kind == 2) marin.MarinDieImg[i.idx].Render(i.x, i.y, 0, 0.6, 0.6);
			else if (Enemy_Kind == 3) zealot.ZealotDieImg[i.idx].Render(i.x, i.y, 0, 0.6, 0.6);
		}
	}
	idx = 0;
}

// Function : EnemyCheck()
// ��ū�� ���� �Ǻ��ϱ� ���� �Լ�
//BOOL Sunken::EnemyCheck(int Enemy_Kind)
//{
//	// ��������������������������������������
//	// ��        ��        ��
//	// ��    4   ��    1   ��
//	// ��        ��        ��
//	// ������������������������������������
//	// ��        ��        ��
//	// ��    3   ��    2   ��
//	// ��        ��        ��
//	// ��������������������������������������
//	// �߾�(��ū/��ž)�� �������� 1�� ~ 4�� ������ ��ġ���� ���� �߰��Ѵ�.
//
//	int skx, sky;
//	for (int i = 0; i < sunkenManager.size(); i++)
//	{
//		skx = sunkenManager[i].GetnX() / 42;
//		sky = sunkenManager[i].GetnY() / 42;
//		// 1�� ��ġ �˻� ����
//		for (int y = sky; y >= sky - 3; y--) {
//			if (y < 0)break;
//			for (int x = (skx + 1); x <= ((skx + 1) + 3) + (y - sky); x++) {
//				if (x > 29) break;
//
//				if (Enemy_Kind == 1) {	// Zergling
//					if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) {	// ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//						sunkenManager[i].SetDetect(TRUE);				// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//						sunkenManager[i].SetspX(x * 42);				// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				if (Enemy_Kind == 2) {	// Marin
//					if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//						sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//						sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				if (Enemy_Kind == 3) {	// Zealot
//					if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//						sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//						sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				sunkenManager[i].SetDetect(FALSE);			// �̿��� ��� ��쿡 ���Ͽ� ��ū�� detection ���´� FALSE�� �����ȴ�.
//			}
//			if (sunkenManager[i].GetDetect() == TRUE) {
//				AttackLock = TRUE;
//				break;// ����� �߰��ߴٸ� ������ ���ݼ���
//			}
//		}
//
//		if (sunkenManager[i].GetDetect() == FALSE) {		// 2�� ���� 4�� ��ġ�� ��ū�� ������ ���� �ܰ迡�� �߰����� ������ ��쿡 �����ϵ��� �Ѵ�.
//			for (int y = sky + 1; y <= sky + 1 + 3; y++) {
//				if (y > 18) break;
//				for (int x = skx + 1; x <= ((skx + 1) + 3) - (y - (sky + 1)); x++) {
//					if (x > 29) break;
//
//					if (Enemy_Kind == 1) {
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// ����� �߰��ߴٸ� ������ ���ݼ���
//				}
//			}
//		}
//
//		if (sunkenManager[i].GetDetect() == FALSE) {
//			for (int y = (sky + 1); y <= (sky + 1) + 3; y++) {
//				if (y > 18) break;
//				for (int x = skx; x >= (skx - 3) + (y - (sky + 1)); x--) {
//					if (x < 0) break;
//					if (Enemy_Kind == 1) {
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// ����� �߰��ߴٸ� ������ ���ݼ���
//				}
//			}
//		}
//
//		if (sunkenManager[i].GetDetect() == FALSE) {
//			for (int y = sky; y >= sky - 3; y--) {
//				if (y < 0) break;
//				for (int x = skx; x >= (skx - 3) - (y - sky); x--) {
//					if (x < 0) break;
//					if (Enemy_Kind == 1) {
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
//							sunkenManager[i].SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
//							sunkenManager[i].SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// ����� �߰��ߴٸ� ������ ���ݼ���
//				}
//			}
//		}
//	}
//	return AttackLock = FALSE;
//}


// Function : DrawCheck(���콺X, ���콺Y, �Ǽ� ���� �Ǻ�, ??, ����� ���� �Ǻ�, ����� ����)
// �׸� ������ üũ�ϴ� �Լ�
BOOL Sunken::DrawCheck(int mX, int mY, BOOL drawMsMoveState, char* coordinate, BOOL delMsMoveState, BOOL deleteState)
{
	/*
	* ��ū�� �Ǽ�, �ı� �Ҷ� ���Ǵ� �Լ��̴�. �ʷϻ� ����(�Ǽ� ����)�� ������ ����(�Ǽ� �Ұ�/ �ı�)���� �����Ͽ� ����Ѵ�.
	*
	* mX = ���콺 X ��ġ
	* mY = ���콺 Y ��ġ
	* drawMsMoveState = ��ū �Ǽ� ���� ON/OFF �Ǻ� ����
	* coordinate = ??
	* delMsMoveState = ��ū �ı� ���� ON/OFF �Ǻ� ����
	* deleteState = Ŭ�� ���� ��� ����� ����
	*/

	int x, y;
	char arr[100];
	BOOL renderState = TRUE; // TRUE, FALSE � ������ �ʱ�ȭ �ص� ��� ����.
	CalculateBuildArea(&x, &y, mX, mY);	// �Ǽ� ���� ����
	sprintf_s(arr, "[X : %d] [Y : %d] : [BX : %d] [BY : %d]", x, y, x - 42, y - 42);
	strcpy(coordinate, arr);

	// ��ū �Ǽ� �Ǵ� �ı� ������ ���
	if (drawMsMoveState == TRUE || delMsMoveState == TRUE) {
		// �װ��� �Ǽ� ������ ���� �˻縦 �����Ѵ�.
		for (int i = y / 42 - 1; i <= (y / 42); i++) {
			for (int j = x / 42 - 1; j <= (x / 42); j++) {
				if (m_map.backGroundArr[i][j] == 0) renderState = TRUE;	// map �迭�� 0�̶�� �Ǽ� ���ɻ��·� ��ȯ
				else {
					renderState = FALSE; // �Ǽ� ������ �ϳ��� 0�� ������� FALSE
					break;
				}
			}
			if (renderState == FALSE) break; // FALSE��� ���̻� �˻縦 �������� �ʴ´�.
		}

		// �ı� ��� ���� ������ ���
		if (delMsMoveState == TRUE) {
			SunkenDiable.Render(x - 42, y - 42, 0, 0.5, 0.5); // ��ū �ı� �ؽ��ĸ� �������Ѵ�.
			if (deleteState == TRUE) {	// �ı��� �����ϴ� ����� ���� ���(��Ŭ��)
				int idx = 0;
				for (auto i : sunkenManager) {	// sunkenManager(��ū ��ġ������ ������ �ִ� Ŭ����vector)�� data �� ��ŭ for���� ����
					if ((i.GetnX() == x - 42) && (i.GetnY() == y - 42)) { // ��ū�� ��ġ�� �ľ��ߴٸ�
						sunkenManager.erase(sunkenManager.begin() + idx); // �ش� ��ü�� ��ū ������ �ı���
						for (int j = y / 42 - 1; j <= y / 42; j++) {
							for (int k = x / 42 - 1; k <= x / 42; k++) {
								m_map.backGroundArr[j][k] = 0; // �� �迭�� �ش� ��ġ�� 0���� �ʱ�ȭ �Ѵ�.
							}
						}
						break;
					}
					idx++;
				}
			}
		}
		// �ı� ��� ������ �ƴҰ��
		else {
			if (renderState == TRUE) { // �Ǽ��� �����ϴٸ� �Ǽ� ���� �ؽ��� ���
				SunkenEnable.Render(x - 42, y - 42, 0, 0.5, 0.5);
			}
			else SunkenDiable.Render(x - 42, y - 42, 0, 0.5, 0.5); // �Ǽ��� �Ұ����ϴٸ� �Ǽ� �Ұ��� �ؽ��� ���
		}
	}

	return renderState;
}

void Sunken::DrawDieMotion(int unit_kind, int idx, int x, int y)
{
	int cnt = 0;
	while (cnt < idx) {
		if (GetTickCount64() - m_KillTime > 25)
		{
			if (unit_kind == 1) {
				zergling.ZerglingDieImg[cnt].Render(x, y, 0, 0.6, 0.6);
				cnt++;
			}
			m_KillTime = GetTickCount64();
		}
	}
}

// �Ǽ� ����ȭ ���� �Լ� - ���� ���콺 ��ġ���� ���� ����� ������ �Ǽ��ϵ��� ��
void Sunken::CalculateBuildArea(int* x, int* y, int nX, int nY)
{
	/*****************************************************************************************************************************
	*
	* �׷����� ������ �˻�� ������ ���� ����ȴ�.
	* 1. ���� ���콺�� ��ġ�� ���� �������� 42�� ���� �������� �ּ�X, �ּ�Y, �ִ�X, �ִ�Y�� ���Ѵ�.
	*	ex) ���콺�� ��ġ�� (237, 364)�� ��� minx = 210, miny = 336, maxx = 252, maxy = 378 �̴�.
	* 2. ���� ���콺�� ��ġ���� ���� ����� �������� ã�´�.
	*	ex) (���� ���콺�� ��ġx - �� �������� x) + (���� ���콺�� ��ġy - �� ��������y) = case_res�� �Ǹ�, case_res ���� ���� ���� ����� �������� ���� x, y��ǥ�� return �Ѵ�.
	*
	******************************************************************************************************************************/

	int minX = 0, minY = 0, maxX = 0, maxY = 0;
	int case_res = 1280;	// ����� ���� ����, 1280���� �ʱ�ȭ�� ������ �� �� �̻��� ũ�⸦ ���� �� ���� �����̴�.
	int case_define = 0;	// ��ġ���� ������ case ����, CASE1_MINXMINY = 1, CASE2_MAXXMINY = 2, CASE3_MINXMAXY = 3, CASE4_MAXXMAXY = 4

	// �ּ� X, �ִ� X�� ���ϴ� for loop
	for (int i = 0; i < 30; i++) {

		if (maxX > nX) {
			minX = maxX - 42;
			break;
		}
		maxX += 42;
	}

	//�ּ� Y, �ִ� Y�� ���ϴ� for loop
	for (int i = 0; i < 16; i++) {

		if (maxY > nY) {
			minY = maxY - 42;
			break;
		}
		maxY += 42;
	}

	// 1�� ���̽����� ���������� �˻縦 ������
	if (((nX - minX) + (nY - minY)) < case_res) {
		case_res = (nX - minX) + (nY - minY);	// case ������� ���ǽ��� �˻��� �� ���� �ش� ������ �ʱ�ȭ��
		case_define = CASE1_MINXMINY;
	}
	if (((maxX - nX) + (nY - minY)) < case_res) {
		case_res = (maxX - nX) + (nY - minY);
		case_define = CASE2_MAXXMINY;
	}
	if (((nX - minX) + (maxY - nY)) < case_res) {
		case_res = (nX - minX) + (maxY - nY);
		case_define = CASE3_MINXMAXY;
	}
	if (((maxX - nX) + (maxY - nY)) < case_res)
	{
		case_res = (maxX - nX) + (maxY - nY);
		case_define = CASE4_MAXXMAXY;
	}

	// �� ��쿡 ���� ���� x, y ���� reference �������� return��
	switch (case_define) {
	case CASE1_MINXMINY:
		*x = minX;
		*y = minY;
		break;
	case CASE2_MAXXMINY:
		*x = maxX;
		*y = minY;
		break;
	case CASE3_MINXMAXY:
		*x = minX;
		*y = maxY;
		break;
	case CASE4_MAXXMAXY:
		*x = maxX;
		*y = maxY;
		break;
	default:
		break;
	}
}
