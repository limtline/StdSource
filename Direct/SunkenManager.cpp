#include "SunkenManager.h"

SunkenManager::SunkenManager() {
	//sunken = NULL;
	nX = 0;
	nY = 0;
	sX = 0;
	sY = 0;
	radian = 0;
	spriteIdx = 0;
	drawState = FALSE;
	enemyDetect = FALSE;
	AttackLock = FALSE;
	atkState = FALSE;
}

SunkenManager::SunkenManager(/*Sunken _sunken, */int _nX, int _nY, int radian, float _sX, float _sY, BOOL _drawState, BOOL _enemyDetect) {
	//this->sunken = _sunken;
	this->nX = _nX;
	this->nY = _nY;
	this->radian = 0;
	this->sX = _sX;
	this->sY = _sY;
	this->drawState = _drawState;
	this->enemyDetect = _enemyDetect;
}
//SunkenManager::SunkenManager(SunkenManager& sunkenManager)
//{
//	//this->sunken = sunkenManager.sunken;
//	this->nX = sunkenManager.nX;
//	this->nY = sunkenManager.nY;
//	this->radian = sunkenManager.radian;
//	this->sX = sunkenManager.sX;
//	this->sY = sunkenManager.sY;
//}

SunkenManager::~SunkenManager() {}

//Sunken SunkenManager::GetSunken()
//{
//	return this->sunken;
//}
int SunkenManager::GetnX()
{
	return this->nX;
}
int SunkenManager::GetnY()
{
	return this->nY;
}
int SunkenManager::GetspX()
{
	return this->spX;
}
int SunkenManager::GetspY()
{
	return this->spY;
}
int SunkenManager::GetRadian()
{
	return this->radian;
}
float SunkenManager::GetsX()
{
	return this->sX;
}
float SunkenManager::GetsY()
{
	return this->sY;
}
int SunkenManager::GetSPRIDX()
{
	return this->spriteIdx;
}
BOOL SunkenManager::GetDetect()
{
	return this->enemyDetect;
}
ULONGLONG SunkenManager::GetTime()
{
	return this->m_SKManagerAniTime;
}
BOOL SunkenManager::GetAttackLock()
{
	return this->AttackLock;
}
int SunkenManager::GetDamage()
{
	return this->damage;
}
BOOL SunkenManager::GetAtkState()
{
	return this->atkState;
}

//void SunkenManager::SetSunken(Sunken sk)
//{
//	this->sunken = sk;
//}
void SunkenManager::SetnX(int nx)
{
	this->nX = nx;
}
void SunkenManager::SetnY(int ny)
{
	this->nY = ny;
}
void SunkenManager::SetspX(int spx)
{
	this->spX = spx;
}
void SunkenManager::SetspY(int spy)
{
	this->spY = spy;
}
void SunkenManager::SetRadian(int radian)
{
	this->radian = radian;
}
void SunkenManager::SetsX(float sx)
{
	this->sX = sx;
}
void SunkenManager::SetsY(float sy)
{
	this->sY = sy;
}
void SunkenManager::SetSPRIDX(int idx)
{
	this->spriteIdx = idx;
}
void SunkenManager::SetDetect(BOOL detect)
{
	this->enemyDetect = detect;
}
void SunkenManager::SetTime(DWORD time)
{
	this->m_SKManagerAniTime = time;
}
void SunkenManager::SetAttackLock(BOOL _attackLock)
{
	this->AttackLock = _attackLock;
}
void SunkenManager::SetDamage(int dmg)
{
	this->damage = dmg;
}
void SunkenManager::SetAtkState(BOOL state)
{
	this->atkState = state;
}

void SunkenManager::Init(SunkenManager *sunkenManager, int idx) {
	for (int i = 0; i < idx; i++) {
		this->nX = 0;
		this->nY = 0;
		this->radian = 0;
		this->sX = 0;
		this->sY = 0;
		this->spriteIdx = 0;
		this->drawState = FALSE;
		this->enemyDetect = FALSE;
		this->m_SKManagerAniTime = 0;
		this->AttackLock;
		this->atkState = FALSE;
	}
}

void SunkenManager::Update()
{
	if (this->enemyDetect == TRUE) {
		if (GetTickCount64() - this->m_SKManagerAniTime > 50)
		{
			this->spriteIdx++;

			if (this->spriteIdx > 20) {
				this->spriteIdx = 0;
			}

			this->m_SKManagerAniTime = GetTickCount64();

		}
	}

	else if (this->enemyDetect == FALSE) {
		if (GetTickCount64() - this->m_SKManagerAniTime > 50)
		{
			this->spriteIdx++;

			if (this->spriteIdx > 1) {
				this->spriteIdx = 0;
			}
			this->m_SKManagerAniTime = GetTickCount64();
		}
	}
}

BOOL SunkenManager::EnemyCheck_Test(int Enemy_Kind, SunkenManager& skmanager)
{
	// ��������������������������������������
	// ��        ��        ��
	// ��    4   ��    1   ��
	// ��        ��        ��
	// ������������������������������������
	// ��        ��        ��
	// ��    3   ��    2   ��
	// ��        ��        ��
	// ��������������������������������������
	// �߾�(��ū/��ž)�� �������� 1�� ~ 4�� ������ ��ġ���� ���� �߰��Ѵ�.

	int skx, sky;

	skx = skmanager.GetnX() / 42;
	sky = skmanager.GetnY() / 42;
	// 1�� ��ġ �˻� ����
	for (int y = sky; y >= sky - 3; y--) {
		if (y < 0)break;
		for (int x = (skx + 1); x <= ((skx + 1) + 3) + (y - sky); x++) {
			if (x > 29) break;

			if (Enemy_Kind == 1) {	// Zergling
				if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) {	// ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
					skmanager.SetDetect(TRUE);				// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
					skmanager.SetspX(x * 42);				// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
					skmanager.SetspY(y * 42);
					break;
				}
			}

			if (Enemy_Kind == 2) {	// Marin
				if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
					skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
					skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
					skmanager.SetspY(y * 42);
					break;
				}
			}

			if (Enemy_Kind == 3) {	// Zealot
				if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
					skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
					skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
					skmanager.SetspY(y * 42);
					break;
				}
			}

			skmanager.SetDetect(FALSE);			// �̿��� ��� ��쿡 ���Ͽ� ��ū�� detection ���´� FALSE�� �����ȴ�.
		}
		if (skmanager.GetDetect() == TRUE) {
			//AttackLock = TRUE;
			break;// ����� �߰��ߴٸ� ������ ���ݼ���
		}
	}

	if (skmanager.GetDetect() == FALSE) {		// 2�� ���� 4�� ��ġ�� ��ū�� ������ ���� �ܰ迡�� �߰����� ������ ��쿡 �����ϵ��� �Ѵ�.
		for (int y = sky + 1; y <= sky + 1 + 3; y++) {
			if (y > 18) break;
			for (int x = skx + 1; x <= ((skx + 1) + 3) - (y - (sky + 1)); x++) {
				if (x > 29) break;

				if (Enemy_Kind == 1) {
					if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 2) {
					if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 3) {
					if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				skmanager.SetDetect(FALSE);
			}
			if (skmanager.GetDetect() == TRUE) {
				//AttackLock = TRUE;
				break;// ����� �߰��ߴٸ� ������ ���ݼ���
			}
		}
	}

	if (skmanager.GetDetect() == FALSE) {
		for (int y = (sky + 1); y <= (sky + 1) + 3; y++) {
			if (y > 18) break;
			for (int x = skx; x >= (skx - 3) + (y - (sky + 1)); x--) {
				if (x < 0) break;
				if (Enemy_Kind == 1) {
					if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 2) {
					if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 3) {
					if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}
				skmanager.SetDetect(FALSE);
			}
			if (skmanager.GetDetect() == TRUE) {
				//AttackLock = TRUE;
				break;// ����� �߰��ߴٸ� ������ ���ݼ���
			}
		}
	}

	if (skmanager.GetDetect() == FALSE) {
		for (int y = sky; y >= sky - 3; y--) {
			if (y < 0) break;
			for (int x = skx; x >= (skx - 3) - (y - sky); x--) {
				if (x < 0) break;
				if (Enemy_Kind == 1) {
					if (zergling.zerglingMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 2) {
					if (marin.marinMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}

				if (Enemy_Kind == 3) {
					if (zealot.zealotMoveArr[y][x] == BG_ENEMY) { // ���� ��ġ�� ���� ������ ��� �ִ� �迭�� �˻���, ���� �ִٰ� �Ǵܵɰ��,
						skmanager.SetDetect(TRUE);		// �߰��� ��ġ�� ��ū�� ���Ͽ� detection ���¸� TRUE�� ��ȯ
						skmanager.SetspX(x * 42);		// �����˼�(���� ���)�� ���� �ִ� ��ġ�� ����ϵ�����
						skmanager.SetspY(y * 42);
						break;
					}
				}
				skmanager.SetDetect(FALSE);
			}
			if (skmanager.GetDetect() == TRUE) {
				//AttackLock = TRUE;
				break;// ����� �߰��ߴٸ� ������ ���ݼ���
			}
		}
	}

	if (skmanager.GetDetect() == TRUE) skmanager.atkState = TRUE;
	else if (skmanager.GetDetect() == TRUE) skmanager.atkState = FALSE;
	return FALSE;
}