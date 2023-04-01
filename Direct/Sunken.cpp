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

	// 적 정보를 계속 Update 받음

	// 공격 딜레이 체크 - 게임 시작이후에 실행됨
	// 1. 성큰이 공격중이지 않을 경우는 락이 항상 해제되어있다.
	// 2. Lock 상태가 False일 경우에 검사를 수행하고 즉시 락상태로 전환된다. 적이 발견되지 않았을 경우 1번부터 다시 수행.
	// 3. 검사를 한번 수행하고 적이 발견되었다면 즉시 락이 걸려 재검사를 수행하지 않는다.
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

	// 성큰 Manager vector 크기만큼 loop를 수행하여 각 index마다 정보를 update, 출력에 관여
	for (int i = 0; i < sunkenManager.size(); i++) {
		if (sunkenManager[i].GetAtkState() == TRUE) { // Detect상태이면 공격 전체 Sprite 출력
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

		else if (sunkenManager[i].GetAtkState() == FALSE) { // Detect 상태가 아니면 0~1번 스프라이트 반복 출력
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

// Function : Draw(그리기 상태, 클릭x, 클릭y, ??, 그리기 가능 상태, 지우기 상태)
// 성큰을 그리기 위한 함수
void Sunken::Draw(BOOL drawState, int nX, int nY, char* coordinate, BOOL drawMsMoveState, BOOL delMsMoveState, int Enemy_Kind)
{
	SunkenManager skmanager;
	int x, y;
	BOOL renderState = TRUE;
	int structure_exist = 0;
	char arr[100];
	CalculateBuildArea(&x, &y, nX, nY);	// 성큰을 지을 공간을 계산함
	sprintf_s(arr, "[X : %d] [Y : %d] : [BX : %d] [BY : %d]", x, y, x - 42, y - 42);
	strcpy(coordinate, arr);

	for (int i = y / 42 - 1; i <= y / 42; i++) {
		for (int j = x / 42 - 1; j <= x / 42; j++) {
			if (m_map.backGroundArr[i][j] == 0) renderState = TRUE; // 성큰을 지을 4개의 배열 공간이 0이라면 TRUE
			else {
				renderState = FALSE; // 하나라도 FALSE일 경우 더이상 검사를 수행하지 않음
				break;
			}
		}
		if (renderState == FALSE) break; // for loop 종료
	}

	// 그리기 가능 상태일 때 
	if (drawMsMoveState == TRUE) {
		// renderState가 TRUE이고 클릭 명령이 들어왔다면
		if (drawState == TRUE && renderState == TRUE) {

			buildSound.EffectPlay(0);
			
			if (userSystem.coin >= 100) {
				for (int i = y / 42 - 1; i <= y / 42; i++) {
					for (int j = x / 42 - 1; j <= x / 42; j++) {
						m_map.backGroundArr[i][j] = BG_STRUCTURE; // 배열공간에 성큰이 건설 되었다는 표시를 남김
					}
				}

				// skmanager에 성큰이 지어질 위치의 x, y, radian, scaleX, scaleY 를 저장하고,
				// sunkenManager(SunkenManager클래스 벡터)에 push back

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

	// 저장된 성큰 정보를 이용해 성큰 Sprite를 출력함
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
// 성큰이 적을 판별하기 위한 함수
//BOOL Sunken::EnemyCheck(int Enemy_Kind)
//{
//	// ┌────────┬────────┐
//	// │        │        │
//	// │    4   │    1   │
//	// │        │        │
//	// ├───────ㅁ────────┤
//	// │        │        │
//	// │    3   │    2   │
//	// │        │        │
//	// └────────┴────────┘
//	// 중앙(성큰/포탑)을 기점으로 1번 ~ 4번 순서의 위치부터 적을 발견한다.
//
//	int skx, sky;
//	for (int i = 0; i < sunkenManager.size(); i++)
//	{
//		skx = sunkenManager[i].GetnX() / 42;
//		sky = sunkenManager[i].GetnY() / 42;
//		// 1번 위치 검사 수행
//		for (int y = sky; y >= sky - 3; y--) {
//			if (y < 0)break;
//			for (int x = (skx + 1); x <= ((skx + 1) + 3) + (y - sky); x++) {
//				if (x > 29) break;
//
//				if (Enemy_Kind == 1) {	// Zergling
//					if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) {	// 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//						sunkenManager[i].SetDetect(TRUE);				// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//						sunkenManager[i].SetspX(x * 42);				// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				if (Enemy_Kind == 2) {	// Marin
//					if (marin.marinMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//						sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//						sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				if (Enemy_Kind == 3) {	// Zealot
//					if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//						sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//						sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//						sunkenManager[i].SetspY(y * 42);
//						break;
//					}
//				}
//
//				sunkenManager[i].SetDetect(FALSE);			// 이외의 모든 경우에 대하여 성큰의 detection 상태는 FALSE로 결정된다.
//			}
//			if (sunkenManager[i].GetDetect() == TRUE) {
//				AttackLock = TRUE;
//				break;// 대상을 발견했다면 무조건 공격수행
//			}
//		}
//
//		if (sunkenManager[i].GetDetect() == FALSE) {		// 2번 부터 4번 위치의 성큰은 각각의 선행 단계에서 발견하지 못했을 경우에 수행하도록 한다.
//			for (int y = sky + 1; y <= sky + 1 + 3; y++) {
//				if (y > 18) break;
//				for (int x = skx + 1; x <= ((skx + 1) + 3) - (y - (sky + 1)); x++) {
//					if (x > 29) break;
//
//					if (Enemy_Kind == 1) {
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// 대상을 발견했다면 무조건 공격수행
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
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// 대상을 발견했다면 무조건 공격수행
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
//						if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 2) {
//						if (marin.marinMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//
//					if (Enemy_Kind == 3) {
//						if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // 적의 위치에 대한 정보를 담고 있는 배열을 검사함, 적이 있다고 판단될경우,
//							sunkenManager[i].SetDetect(TRUE);		// 발견한 위치의 성큰에 대하여 detection 상태를 TRUE로 전환
//							sunkenManager[i].SetspX(x * 42);		// 가시촉수(공격 모션)을 적이 있는 위치에 출력하도록함
//							sunkenManager[i].SetspY(y * 42);
//							break;
//						}
//					}
//					sunkenManager[i].SetDetect(FALSE);
//				}
//				if (sunkenManager[i].GetDetect() == TRUE) {
//					AttackLock = TRUE;
//					break;// 대상을 발견했다면 무조건 공격수행
//				}
//			}
//		}
//	}
//	return AttackLock = FALSE;
//}


// Function : DrawCheck(마우스X, 마우스Y, 건설 가능 판별, ??, 지우기 가능 판별, 지우기 수행)
// 그릴 영역을 체크하는 함수
BOOL Sunken::DrawCheck(int mX, int mY, BOOL drawMsMoveState, char* coordinate, BOOL delMsMoveState, BOOL deleteState)
{
	/*
	* 성큰을 건설, 파괴 할때 사용되는 함수이다. 초록색 영역(건설 가능)과 붉은색 영역(건설 불가/ 파괴)으로 구분하여 출력한다.
	*
	* mX = 마우스 X 위치
	* mY = 마우스 Y 위치
	* drawMsMoveState = 성큰 건설 상태 ON/OFF 판별 변수
	* coordinate = ??
	* delMsMoveState = 성큰 파괴 상태 ON/OFF 판별 변수
	* deleteState = 클릭 했을 경우 지우기 수행
	*/

	int x, y;
	char arr[100];
	BOOL renderState = TRUE; // TRUE, FALSE 어떤 값으로 초기화 해도 상관 없다.
	CalculateBuildArea(&x, &y, mX, mY);	// 건설 영역 선정
	sprintf_s(arr, "[X : %d] [Y : %d] : [BX : %d] [BY : %d]", x, y, x - 42, y - 42);
	strcpy(coordinate, arr);

	// 성큰 건설 또는 파괴 상태일 경우
	if (drawMsMoveState == TRUE || delMsMoveState == TRUE) {
		// 네개의 건설 지점에 대한 검사를 수행한다.
		for (int i = y / 42 - 1; i <= (y / 42); i++) {
			for (int j = x / 42 - 1; j <= (x / 42); j++) {
				if (m_map.backGroundArr[i][j] == 0) renderState = TRUE;	// map 배열이 0이라면 건설 가능상태로 전환
				else {
					renderState = FALSE; // 건설 지점에 하나라도 0이 있을경우 FALSE
					break;
				}
			}
			if (renderState == FALSE) break; // FALSE라면 더이상 검사를 수행하지 않는다.
		}

		// 파괴 기능 수행 상태일 경우
		if (delMsMoveState == TRUE) {
			SunkenDiable.Render(x - 42, y - 42, 0, 0.5, 0.5); // 성큰 파괴 텍스쳐를 렌더링한다.
			if (deleteState == TRUE) {	// 파괴를 수행하는 명령이 들어올 경우(좌클릭)
				int idx = 0;
				for (auto i : sunkenManager) {	// sunkenManager(성큰 위치정보를 가지고 있는 클래스vector)의 data 수 만큼 for문을 수행
					if ((i.GetnX() == x - 42) && (i.GetnY() == y - 42)) { // 성큰의 위치를 파악했다면
						sunkenManager.erase(sunkenManager.begin() + idx); // 해당 객체의 성큰 정보를 파괴함
						for (int j = y / 42 - 1; j <= y / 42; j++) {
							for (int k = x / 42 - 1; k <= x / 42; k++) {
								m_map.backGroundArr[j][k] = 0; // 맵 배열의 해당 위치를 0으로 초기화 한다.
							}
						}
						break;
					}
					idx++;
				}
			}
		}
		// 파괴 기능 수행이 아닐경우
		else {
			if (renderState == TRUE) { // 건설이 가능하다면 건설 가능 텍스쳐 출력
				SunkenEnable.Render(x - 42, y - 42, 0, 0.5, 0.5);
			}
			else SunkenDiable.Render(x - 42, y - 42, 0, 0.5, 0.5); // 건설이 불가능하다면 건설 불가능 텍스쳐 출력
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

// 건설 최적화 영역 함수 - 현재 마우스 위치에서 가장 가까운 기점에 건설하도록 함
void Sunken::CalculateBuildArea(int* x, int* y, int nX, int nY)
{
	/*****************************************************************************************************************************
	*
	* 그려지는 영역의 검사는 다음과 같이 수행된다.
	* 1. 현재 마우스가 위치한 값을 기준으로 42로 나눠 떨어지는 최소X, 최소Y, 최대X, 최대Y를 구한다.
	*	ex) 마우스의 위치가 (237, 364)일 경우 minx = 210, miny = 336, maxx = 252, maxy = 378 이다.
	* 2. 현재 마우스의 위치에서 가장 가까운 꼭지점을 찾는다.
	*	ex) (현재 마우스의 위치x - 각 꼭지점의 x) + (현재 마우스의 위치y - 각 꼭지점의y) = case_res가 되며, case_res 값이 가장 작은 경우의 꼭지점을 최종 x, y좌표로 return 한다.
	*
	******************************************************************************************************************************/

	int minX = 0, minY = 0, maxX = 0, maxY = 0;
	int case_res = 1280;	// 결과값 저장 변수, 1280으로 초기화된 이유는 이 값 이상의 크기를 가질 수 없기 때문이다.
	int case_define = 0;	// 위치값을 선정할 case 변수, CASE1_MINXMINY = 1, CASE2_MAXXMINY = 2, CASE3_MINXMAXY = 3, CASE4_MAXXMAXY = 4

	// 최소 X, 최대 X를 구하는 for loop
	for (int i = 0; i < 30; i++) {

		if (maxX > nX) {
			minX = maxX - 42;
			break;
		}
		maxX += 42;
	}

	//최소 Y, 최대 Y를 구하는 for loop
	for (int i = 0; i < 16; i++) {

		if (maxY > nY) {
			minY = maxY - 42;
			break;
		}
		maxY += 42;
	}

	// 1번 케이스부터 순차적으로 검사를 수행함
	if (((nX - minX) + (nY - minY)) < case_res) {
		case_res = (nX - minX) + (nY - minY);	// case 결과값은 조건식을 검사할 때 마다 해당 식으로 초기화됨
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

	// 각 경우에 대해 최종 x, y 값을 reference 형식으로 return함
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
