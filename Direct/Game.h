#ifndef __Game_H__
#define __Game_H__




class Game : public Chap
{
	BOOL GAME_INIT;

	BOOL drawState;			// 성큰 그리기 상태 변수 - 클릭 시에 그리기 동작을 수행하도록 함
	BOOL drawMsMoveState;	// 성큰 건설 가능 상태 변수 - 마우스가 이동한 위치에 성큰을 지을수 있는지 판단
	BOOL clickSunken;		// 성큰 클릭 상태 변수 - 성큰 아이콘의 클릭 상태를 제어함

	BOOL deleteState;		// 성큰 지우기 상태 변수 - 클릭 시에 성큰을 지우는 동작을 수행 하도록 함
	BOOL delMsMoveState;	// 성큰 지우기 가능 상태 변수 - 마우스가 이동한 위치에 성큰이 있는지 판별하고 지우기를 수행
	BOOL clickDelete;		// 성큰 지우기 클릭 상태 변수 - 성큰 지우기 아이콘 클릭 상태를 제어함

	BOOL clickStart;
	BOOL startMsMoveState;
	BOOL startState;

	BOOL startInitState;

	BOOL drawHero;

	int G_STAGE;
	
	int x, y;
	int mx, my;

	int swapScreen = 0;
public:
	Game();
	~Game();


	DWORD m_GameTime;
	DWORD m_NowTime;
	BOOL marinExist;
	int STAGE_CNT;
	int heroMove;
	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	void GetTime();

	BOOL GetStartState()
	{
		return this->startState;
	}

	BOOL GetStartInitState()
	{
		return this->startInitState;
	}

	void SetStartState(BOOL tf)
	{
		this->startState = tf;
	}
	void SetStartInitState(BOOL tf)
	{
		this->startInitState = tf;
	}

	virtual void OnMessage(MSG* msg);
};

extern Game m_game;

#endif