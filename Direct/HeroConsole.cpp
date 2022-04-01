#include "Include.h"

HeroConsole heroC;

HeroConsole::HeroConsole()
{
	portrait = FALSE;
}

HeroConsole::~HeroConsole()
{
}

void HeroConsole::Init()
{
	portrait = FALSE;
	// 캐리건 초상화
	kerriganPortrait.Create("./resource/KerriganPortrait/kerriganPortrait.png", false, D3DCOLOR_XRGB(0, 0, 0));
	kerriganHighlight.Create("./resource/KerriganPortrait/kerriganHighlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	kerriganClick.Create("./resource/KerriganPortrait/kerriganClick.png", false, D3DCOLOR_XRGB(0, 0, 0));
	// 캐리건 초상화

	// 레이너 초상화
	raynorPortrait.Create("./resource/RaynorPortrait/raynorPortrait.png", false, D3DCOLOR_XRGB(0, 0, 0));
	raynorHighlight.Create("./resource/RaynorPortrait/raynorHighlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	raynorClick.Create("./resource/RaynorPortrait/raynorClick.png", false, D3DCOLOR_XRGB(0, 0, 0));
	// 레이너 초상화

	// 피닉스 초상화
	phoenixPortrait.Create("./resource/PhoenixPortrait/phoenixPortrait.png", false, D3DCOLOR_XRGB(0, 0, 0));
	phoenixHighlight.Create("./resource/PhoenixPortrait/phoenixHighlight.png", false, D3DCOLOR_XRGB(0, 0, 0));
	phoenixClick.Create("./resource/PhoenixPortrait/phoenixClick.png", false, D3DCOLOR_XRGB(0, 0, 0));
	// 피닉스 초상화

	heroBG.Create("./resource/HeroBG.jpg", false, D3DCOLOR_XRGB(0, 0, 0));		// 배경
	choose.Create("./resource/HeroChoose.png", false, D3DCOLOR_XRGB(0, 0, 0));	// 글씨
}

void HeroConsole::Update()
{
}

void HeroConsole::Draw()
{
	heroBG.Render(0, 0, 0, 1, 1);
	phoenixPortrait.Render(280, 220, 0, 1, 1);
	raynorPortrait.Render(540, 220, 0, 1, 1);
	kerriganPortrait.Render(800, 220, 0, 1, 1);
	choose.Render(460, 500, 0, 1, 1);

	if (heroDraw == RAYNOR_PORTRAITHILIGHT)
		raynorHighlight.Render(540, 220, 0, 1, 1);
	if (heroDraw == PHOENIX_PORTRAITHILIGHT)
		phoenixHighlight.Render(280, 220, 0, 1, 1);
	if (heroDraw == KERRIGAN_PORTRAITHILIGHT)
		kerriganHighlight.Render(800, 220, 0, 1, 1);

	if (heroDraw == PHOENIX_READY)
		phoenixClick.Render(280, 220, 0, 1, 1);
	if (heroDraw == RAYNOR_READY)
		raynorClick.Render(540, 220, 0, 1, 1);
	if (heroDraw == KERRIGAN_READY)
		kerriganClick.Render(800, 220, 0, 1, 1);
}

void HeroConsole::DrawHero(int mX, int mY, int show)
{
	if (show == KERRIGAN_PORTRAITHILIGHT)
	{
		heroDraw = show;
	}

	else if (show == RAYNOR_PORTRAITHILIGHT)
	{
		heroDraw = show;
	}

	else if (show == PHOENIX_PORTRAITHILIGHT)
	{
		heroDraw = show;
	}
	////////////////////////////////////////////////////

	else if (show == RAYNOR_READY)
	{
		heroDraw = show;
	}

	else if (show == PHOENIX_READY)
	{
		heroDraw = show;
	}

	else if (show == KERRIGAN_READY)
	{
		heroDraw = show;
	}
}