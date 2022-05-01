#include "Include.h"

int sunken_idx = 0;
static int r = 0;
char coordinate[100];
Game m_game;
FmodSound m_BackGroundSound;

Game::Game()
{
}

Game::~Game()
{

}

void Game::Init()
{
	clickSunken = FALSE;
	drawMsMoveState = FALSE;
	drawState = FALSE;
	m_game.marinExist = FALSE;
	delMsMoveState = FALSE;
	deleteState = FALSE;
	clickStart = FALSE;
	startInitState = TRUE;
	swapScreen = FALSE;


	heroC.Init();

	// Map System Init
	m_map.Init();
	console.Init();
	
	// Sunken Init
	sunken.Init();
	
	// 영웅 Init
	kerrigan.Init();
	raynor.Init();
	phoenix.Init();
	h_skill.Init();

	// Minion Init
	zergling.Init();
	marin.Init();
	zealot.Init();
	route.Init();
	enemyManager.Init();

	// Coin System Init
	userSystem.Init();
	
	Gmanager.Init();
	//m_FmodSound.SetVolume();
	m_NowTime = 0;
	m_GameTime = 0;
	G_STAGE = 0;
	STAGE_CNT = 0;
	// 데이타 베이스///////////////////
	//sql.Init();

	char tFname[256], zFname[256], pFname[256];
	for (int i = 0; i < 4; i++) {
		sprintf_s(tFname, "./resource/Sound/Terran_Theme_%d.mp3", i + 1);
		sprintf_s(zFname, "./resource/Sound/Zerg_Theme_%d.mp3", i + 1);
		sprintf_s(pFname, "./resource/Sound/Protoss_Theme_%d.mp3", i + 1);
		m_BackGroundSound.AddSoundFile(tFname, true);
		m_BackGroundSound.AddSoundFile(zFname, true);
		m_BackGroundSound.AddSoundFile(pFname, true);
	}
	x = 1000;
	y = 400;

	GAME_INIT = TRUE;
}

void Game::Draw()
{
	// Rendering Order
	// 1. Map - Ground Texture
	// 2. Sunken - Defense tower
	// 3. Sunken Enable/Disable - Overlap Sunken
	// 4. Console - Highest Priority(Inner order - console / icon / highlight / clicked)

	if (GAME_INIT == TRUE) {
		m_BackGroundSound.BGPlay(0);
		GAME_INIT = FALSE;
	}

	m_map.Draw();
	sunken.Draw(drawState, x, y, coordinate, drawMsMoveState, delMsMoveState, STAGE_CNT);

	// Minion Draw
	if (STAGE_CNT == 1) 
		zergling.Draw(mx, my);
	else if (STAGE_CNT == 2) 
		marin.Draw(mx, my);
	else if (STAGE_CNT == 3) 
		zealot.Draw(mx, my);

	// Hero Draw
	if (heroManager.m_heroSel == KERRIGAN_SHOW)
		kerrigan.Draw();
	else if (heroManager.m_heroSel == RAYNOR_SHOW)
		raynor.Draw();
	else if (heroManager.m_heroSel == PHOENIX_SHOW)
		phoenix.Draw();

	h_skill.Draw();
	sunken.DrawCheck(mx, my, drawMsMoveState, coordinate, delMsMoveState, deleteState);
	console.Activate(mx, my, clickSunken, clickDelete, clickStart);

	if (swapScreen != SWAPSCREEN)
	{
		heroC.Draw();
	}
	
	// 데이타 베이스///////////////////
	//sql.Draw();

	char str[10];

	

	// Map Array Display - to be captioned
	if (m_map.debug_BG == TRUE)
	{
		m_map.gyeokja.Render(0, 0, 0, 1, 1);
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 30; j++)
			{
				_itoa(m_map.backGroundArr[i][j], str, 10);
				dv_font.DrawString(str, j * 42 + 0, i * 42 + 0);
			}
		}
	}
	if (STAGE_CNT == 1) {
		if (marin.marin_BG == TRUE)
		{
			m_map.DrawGJ();
			for (int i = 0; i < 18; i++) {
				for (int j = 0; j < 30; j++)
				{
					_itoa(zergling.zerglingMoveArr[i][j], str, 10);
					dv_font.DrawString(str, j * 42 + 0, i * 42 + 0);
				}
			}
		}
	}
	else if (STAGE_CNT == 2) {
		if (marin.marin_BG == TRUE)
		{
			m_map.DrawGJ();
			for (int i = 0; i < 18; i++) {
				for (int j = 0; j < 30; j++)
				{
					_itoa(marin.marinMoveArr[i][j], str, 10);
					dv_font.DrawString(str, j * 42 + 0, i * 42 + 0);
				}
			}
		}
	}
	else if (STAGE_CNT == 3) {
		if (marin.marin_BG == TRUE)
		{
			m_map.DrawGJ();
			for (int i = 0; i < 18; i++) {
				for (int j = 0; j < 30; j++)
				{
					_itoa(zealot.zealotMoveArr[i][j], str, 10);
					dv_font.DrawString(str, j * 42 + 0, i * 42 + 0);
				}
			}
		}
	}

	
	/*if (enemyManager.Enemy_Activate == TRUE) {
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 30; j++) {
				_itoa(route.traceArr[i][j], str, 10);
				dv_font.DrawString(str, j * 42 + 0, i * 42 + 0);
			}
		}
	}*/
	/*if (route.show_Route == TRUE) {
		for (int i = 0; i < sizeof(Trace) / sizeof(Route); i++) {
			route.traceArr[Trace[i].y][Trace[i].x] = 55;
			_itoa(route.traceArr[Trace[i].y][Trace[i].x], str, 10);
			dv_font.DrawString(str, Trace[i].x * 42 + 0, Trace[i].y * 42 + 0);
		}
	}*/
	
	char sstr[256];
	sprintf(sstr, "[STAGE : %d][HP : %d]", G_STAGE, userSystem.userHp);
	dv_font.DrawString(sstr, 600, 20, D3DCOLOR_XRGB(0, 0, 0));

}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	srand((unsigned int)time(NULL));
	r = rand() % 12 + 1;
	static int a = 0;
	if(a == 0) 
	{
		//GameTime = GetTickCount();
		a = 1;
	}

	if (GetTickCount64() - a > frame)
	{
		key.Update();

		// 입 맛에 맞게
		m_map.Update(130);
		sunken.Update(STAGE_CNT, startState);
		kerrigan.Update(STAGE_CNT, startState);
		raynor.Update(STAGE_CNT, startState);
		phoenix.Update(STAGE_CNT, startState);
		h_skill.Update(STAGE_CNT, startState);
		Gmanager.Update();
		console.Update();
		if (STAGE_CNT == 1) zergling.Update();
		else if (STAGE_CNT == 2) marin.Update();
		else if (STAGE_CNT == 3) zealot.Update();
		heroC.Update();
		// 데이타 베이스///////////////////
		// 입 맛에 맞게 (여기선 안쓰임..프레임 값이 필요 할때만.. 그냥 방법만...)
		//sql.Update(frame+3000);

		a = GetTickCount64();
	}

	if (startState == TRUE && enemyManager.Enemy_Activate == TRUE) {
		if (startInitState == TRUE) {
			route.TraceInit();
			route.RoutInitialize();
			route.show_Route = TRUE;
			startInitState = FALSE;
			enemyManager.EnemyExist = TRUE;
		}
	}

	if (enemyManager.Enemy_Activate == FALSE) {
		startState = FALSE;
		startInitState = TRUE;
		route.show_Route = FALSE;
	}

	if (userSystem.userHp <= 0) g_Mng.n_Chap = OVER;


}



void Game::OnMessage( MSG* msg )
{
	switch (msg->message) {
	case WM_LBUTTONDOWN:
		x = LOWORD(msg->lParam);
		y = HIWORD(msg->lParam);

		// 성큰 아이콘 클릭 -> 콘솔창
		if (ONCLICK_SUNKEN(x, y)) {
			clickSunken = TRUE;
			deleteState = FALSE;
		}

		// 성큰 지우기 클릭 -> 콘솔창
		else if (ONCLICK_DELETE(x, y)) {
			clickDelete = TRUE;
			drawState = FALSE;
		}

		// 시작 아이콘 클릭 -> 콘솔창
		else if (ONCLICK_START(x, y)) {
			clickStart = TRUE;
			if (STAGE_CNT >= 3) {
				STAGE_CNT = 0;
				enemyManager.maxCount += 3;
				enemyManager.max_hp += 50;
				//userSystem.cost += 5;
			}
		}

		// 각 상태에 대한 마우스 클릭 동작은 콘솔창 밖으로 이동했을 때 활성화 됨
		if (y < 680) {
			drawState = TRUE;
			deleteState = TRUE;
		}

		// 초상화 클릭 영역
		if (x > 780 && x <= 1040 && y >= 210 && y <= 440)
		{
			heroC.DrawHero(x, y, KERRIGAN_READY);
		}

		if (x > 530 && x <= 780 && y >= 210 && y <= 440)
		{
			heroC.DrawHero(x, y, RAYNOR_READY);
		}

		if (x > 270 && x <= 520 && y >= 210 && y <= 440)
		{
			heroC.DrawHero(x, y, PHOENIX_READY);
		}
		// 초상화 클릭 영역

		break;

	case WM_LBUTTONUP:
		x = LOWORD(msg->lParam);
		y = HIWORD(msg->lParam);
		// 마우스 버튼 UP 상태
		// 성큰 아이콘이 클릭 되면 성큰을 그리기 위한 변수를 제외한 모든 변수가 FALSE 값으로 변함
		if (clickSunken == TRUE) {
			drawMsMoveState = TRUE;
			delMsMoveState = FALSE;
		}

		// 성큰 지우기가 클릭 되면 성큰을 지우기 위한 변수를 제외한 모든 변수가 FALSE 값으로 변함
		if (clickDelete == TRUE) {
			delMsMoveState = TRUE;
			drawMsMoveState = FALSE;
		}

		if (clickStart == TRUE) {
			if (startState == FALSE) {
				G_STAGE += 1;
				STAGE_CNT += 1;
			}
			startState = TRUE;
			enemyManager.Enemy_Activate = TRUE;
		}

		if (heroC.portrait == FALSE)
		{
			heroC.portrait = TRUE;
			// 영웅 선택시 게임 실행~~~
			// 캐리건
			if (x > 780 && x <= 1040 && y >= 210 && y <= 440)
			{
				heroManager.HeroSelect(KERRIGAN_SHOW);
				swapScreen = SWAPSCREEN;
			}

			// 레이너
			if (x > 530 && x <= 780 && y >= 210 && y <= 440)
			{
				heroManager.HeroSelect(RAYNOR_SHOW);
				swapScreen = SWAPSCREEN;
			}

			// 피닉스
			if (x > 270 && x <= 520 && y >= 210 && y <= 440)
			{
				heroManager.HeroSelect(PHOENIX_SHOW);
				swapScreen = SWAPSCREEN;
			}
			// 영웅 선택시 게임 실행~~~
		}

		// 마우스 Up 버튼이 인식되면 클릭 동작에서만 수행되는 변수는 전부 FALSE로 초기화됨
		clickSunken = FALSE;
		clickDelete = FALSE;
		clickStart = FALSE;
		drawState = FALSE;
		deleteState = FALSE;
		break;
	case WM_MOUSEMOVE:
		// 현재 마우스가 위치한 모든 값에 대한 동작을 처리함
		mx = LOWORD(msg->lParam);
		my = HIWORD(msg->lParam);
		if (clickSunken == TRUE) {
			drawMsMoveState = TRUE;
			delMsMoveState = FALSE;
		}

		if (clickDelete == TRUE) {
			drawMsMoveState = FALSE;
			delMsMoveState = TRUE;
		}

		// 초상화 하이라이트
		if (mx > 780 && mx <= 1040 && my >= 210 && my <= 440)
		{
			heroC.DrawHero(mx, my, KERRIGAN_PORTRAITHILIGHT);
		}

		if (mx > 530 && mx <= 780 && my >= 210 && my <= 440)
		{
			heroC.DrawHero(mx, my, RAYNOR_PORTRAITHILIGHT);
		}

		if (mx > 270 && mx <= 520 && my >= 210 && my <= 440)
		{
			heroC.DrawHero(mx, my, PHOENIX_PORTRAITHILIGHT);
		}
		// 초상화 하이라이트

		h_skill.MouseMove(msg->lParam);

		// to be deleted, 현재 마우스 위치값을 표시하는 캡션
		SetWindowText(msg->hwnd, coordinate);
		break;
	case WM_RBUTTONDOWN:
		// 우클릭-> 건설과 관련된 모든 변수를 FALSE처리함
		// 영웅 유닛이 선택 된 경우에는 영웅 유닛의 이동을 수행
		x = LOWORD(msg->lParam);
		y = HIWORD(msg->lParam);

		drawState = FALSE;			// 그리기 상태 해제
		drawMsMoveState = FALSE;	// 건설 판별 상태 해제
		deleteState = FALSE;		// 지우기 상태 해제
		delMsMoveState = FALSE;		// 지우기 판별 상태 해제

		if (heroManager.m_heroSel == KERRIGAN_SHOW)
			kerrigan.MouseMoving(msg->lParam);
		if (heroManager.m_heroSel == PHOENIX_SHOW)
			phoenix.MouseMoving(msg->lParam);
		if (heroManager.m_heroSel == RAYNOR_SHOW)
			raynor.MouseMoving(msg->lParam);
		break;
	}
}
