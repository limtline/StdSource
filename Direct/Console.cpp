#include "Include.h"

Console console;
int c_hour, c_min, c_sec;
int h_unit, h_tens;
int m_unit, m_tens;
int s_unit, s_tens;

Console::Console()
{
	console_theme = CONSOLE_TYPE_T;
}

Console::~Console()
{

}

void Console::Init()
{
	t_Console.Create("./resource/terran_console.png", false, D3DCOLOR_XRGB(0, 0, 0));
	z_Console.Create("./resource/zerg_console.png", false, D3DCOLOR_XRGB(0, 0, 0));
	p_Console.Create("./resource/protoss_console.png", false, D3DCOLOR_XRGB(0, 0, 0));

	c_SunkenIcon.Create("./resource/Icon/Sunken/sunken_icon.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_SunkenHighlight.Create("./resource/Icon/Sunken/sunken_highlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_SunkenClick.Create("./resource/Icon/Sunken/sunken_clicked.png", false, D3DCOLOR_XRGB(0, 0, 0));

	c_DeleteIcon.Create("./resource/Icon/Delete/delete_icon.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_DeleteHighlight.Create("./resource/Icon/Delete/delete_highlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_DeleteClick.Create("./resource/Icon/Delete/delete_click.png", false, D3DCOLOR_XRGB(0, 0, 0));

	c_StartIcon.Create("./resource/Icon/Start/start_icon.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_StartHighlight.Create("./resource/Icon/Start/start_highlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_StartClick.Create("./resource/Icon/Start/start_click.png", false, D3DCOLOR_XRGB(0, 0, 0));

	c_ClockFrame.Create("./resource/Number/clockFrame.png", false, D3DCOLOR_XRGB(0, 0, 0));
	char Fname[256];
	for (int i = 0; i < 10; i++) {
		sprintf_s(Fname, "./resource/Number/num%d.png", i);
		c_NumberImg[i].Create(Fname, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	c_Colon.Create("./resource/Number/numColon.png", false, D3DCOLOR_XRGB(0, 0, 0));
	c_CoinImg.Create("./resource/coin/coin.png", false, D3DCOLOR_XRGB(0, 0, 0));


	c_NowTime = 0;
	c_GameTime = 0;
}

void Console::Update()
{
	if (GetTickCount64() - c_GameTime > 1000) {
		c_NowTime++;
		c_GameTime = GetTickCount64();
	}
}

void Console::Activate(int mx, int my, BOOL clickSunken, BOOL clickDelete, BOOL clickStart)
{
	this->Draw();
	this->DrawSkIcon(mx, my, clickSunken);
	this->DrawDelIcon(mx, my, clickDelete);
	this->DrawStrtIcon(mx, my, clickStart);
	this->DrawSample();
}

void Console::Draw()
{
	if (console_theme == CONSOLE_TYPE_T) t_Console.Draw(0, 677);
	else if (console_theme == CONSOLE_TYPE_Z) z_Console.Draw(0, 677);
	else if (console_theme == CONSOLE_TYPE_P) p_Console.Draw(0, 677);

	c_ClockFrame.Render(42 * 10+12, 674, 0, 0.65, 0.65);
	c_hour = (c_NowTime / 60 / 60) % 60;
	c_min = (c_NowTime / 60) % 60;
	c_sec = c_NowTime % 60;

	h_tens = c_hour / 10;
	h_unit = c_hour % 10;

	m_tens = c_min / 10;
	m_unit = c_min % 10;

	s_tens = c_sec / 10;
	s_unit = c_sec % 10;
	int timeArr_cnt = 0;
	for (int i = 0; i < 10; i++) {
		if (h_tens == i) {
			timeArr[0] = i;
		}
		if (h_unit == i) {
			timeArr[1] = i;
		}
		if (m_tens == i) {
			timeArr[3] = i;
		}
		if (m_unit == i) {
			timeArr[4] = i;
		}
		if (s_tens == i) {
			timeArr[6] = i;
		}
		if (s_unit == i) {
			timeArr[7] = i;
		}
	}

	timeArr[2] = 99;
	timeArr[5] = 99;

	int dist = 0;
	for (int i = 0; i < 8; i++) {
		dist = i * 14;
		if (i == 2 || i == 5) {
			c_Colon.Render(42 * 10 + 18 + dist, 684, 0, 0.15, 0.15);
			//dist += 15;
		}
		else c_NumberImg[timeArr[i]].Render(42 * 10 + 18 + dist, 684, 0, 0.15, 0.15);
	}
	
	int money = userSystem.coin;
	int maan = money / 10000;
	int cheon = (money - (maan*10000)) / 1000;
	int baek = (money - (maan*10000) - (cheon*1000)) / 100;
	int sip = (money - (maan * 10000) - (cheon * 1000) - (baek*100)) / 10;
	int il = (money - (maan * 10000) - (cheon * 1000) - (baek * 100) - (sip*10));
	
	coinArr[0] = maan;
	coinArr[1] = cheon;
	coinArr[2] = baek;
	coinArr[3] = sip;
	coinArr[4] = il;

	c_CoinImg.Render(950, 10, 0, 0.5, 0.5);
	for (int i = 0; i < 5; i++) {
		c_NumberImg[coinArr[i]].Render(985 + (i * 15), 14, 0, 0.13, 0.13);
	}
}

void Console::DrawSkIcon(int mx, int my, BOOL clickSunken)
{
	int SKX = 378, SKY = 720, SKR = 0;
	double SKSX = 0.6, SKSY = 0.6;

	c_SunkenIcon.Render(SKX, SKY, SKR, SKSX, SKSY);

	if ((mx > (SKX-5) && mx < (SKX+45)) && (my > (SKY-40) && my < (SKY+10))) {
		c_SunkenHighlight.Render(SKX, SKY, SKR, SKSX, SKSY);
	}
	if (clickSunken == TRUE) {
		c_SunkenClick.Render(SKX, SKY, SKR, SKSX, SKSY);
	}
}

void Console::DrawDelIcon(int mx, int my, BOOL clickDelete)
{
	int DLX = 798, DLY = 720, DLR = 0;
	double DLSX = 0.6, DLSY = 0.6;

	c_DeleteIcon.Render(DLX, DLY, DLR, DLSX, DLSY);

	if ((mx > (DLX-5) && mx < (DLX+45)) && (my > (DLY-40) && my < (DLY+10))) {
		c_DeleteHighlight.Render(DLX, DLY, DLR, DLSX, DLSY);
	}
	if (clickDelete == TRUE) {
		c_DeleteClick.Render(DLX, DLY, DLR, DLSX, DLSY);
	}
}

void Console::DrawStrtIcon(int mx, int my, BOOL clickStart)
{
	int STX =712, STY =720, STR = 0;
	double STSX = 0.6, STSY = 0.6;

	c_StartIcon.Render(STX, STY, STR, STSX, STSY);

	if ((mx > (STX - 5) && mx < (STX + 45)) && (my > (STY - 40) && my < (STY + 10))) {
		c_StartHighlight.Render(STX, STY, STR, STSX, STSY);
	}

	if (clickStart == TRUE) {
		c_StartClick.Render(STX, STY, STR, STSX, STSY);
		
	}
}

void Console::DrawSample()
{
	for (int i = 1; i <= 3; i++) {
		c_DeleteIcon.Render(378 + (86 * i), 720, 0, 0.6, 0.6);
	}
}

