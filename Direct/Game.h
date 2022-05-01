#ifndef __Game_H__
#define __Game_H__




class Game : public Chap
{
	BOOL GAME_INIT;

	BOOL drawState;			// ��ū �׸��� ���� ���� - Ŭ�� �ÿ� �׸��� ������ �����ϵ��� ��
	BOOL drawMsMoveState;	// ��ū �Ǽ� ���� ���� ���� - ���콺�� �̵��� ��ġ�� ��ū�� ������ �ִ��� �Ǵ�
	BOOL clickSunken;		// ��ū Ŭ�� ���� ���� - ��ū �������� Ŭ�� ���¸� ������

	BOOL deleteState;		// ��ū ����� ���� ���� - Ŭ�� �ÿ� ��ū�� ����� ������ ���� �ϵ��� ��
	BOOL delMsMoveState;	// ��ū ����� ���� ���� ���� - ���콺�� �̵��� ��ġ�� ��ū�� �ִ��� �Ǻ��ϰ� ����⸦ ����
	BOOL clickDelete;		// ��ū ����� Ŭ�� ���� ���� - ��ū ����� ������ Ŭ�� ���¸� ������

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