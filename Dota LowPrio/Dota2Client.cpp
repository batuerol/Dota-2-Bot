#include "Dota2Client.h"

Dota2Client::Dota2Client() : m_hDC(NULL), m_hDotaWnd(NULL), m_team(Team::NONE)
{
	using namespace std;
	// TODO: Some kind of a parser(JSON?) for other resolution options
	// Colors are original colors, not mouse over colors.
	m_pixelList.insert(make_pair("PlayDota", Pixel(1677, 1017, 87, 151, 92))); // Find-Match green.
	m_pixelList.insert(make_pair("NormalMatch", Pixel(1787, 815, 33, 37, 40)));
	m_pixelList.insert(make_pair("AllPick", Pixel(1556, 575)));
	m_pixelList.insert(make_pair("SingleDraft", Pixel(1556, 600)));
	m_pixelList.insert(make_pair("CaptainsMode", Pixel(1556, 627)));
	m_pixelList.insert(make_pair("RandomDraft", Pixel(1556, 652)));
	m_pixelList.insert(make_pair("AbilityDraft", Pixel(1556, 681)));
	m_pixelList.insert(make_pair("LeastPlayed", Pixel(1556, 708)));
	m_pixelList.insert(make_pair("AllRandom", Pixel(1556, 736)));
	m_pixelList.insert(make_pair("LimitedHeroes", Pixel(1556, 762)));
	m_pixelList.insert(make_pair("CaptainsDraft", Pixel(1556, 788)));
	m_pixelList.insert(make_pair("ARDM", Pixel(1556, 816)));
	m_pixelList.insert(make_pair("PickHero", Pixel(997, 799, 55, 87, 116)));
	m_pixelList.insert(make_pair("Accept", Pixel(862, 514, 54, 89, 73)));
	m_pixelList.insert(make_pair("Decline", Pixel(1011, 514, 70, 38, 38)));
	m_pixelList.insert(make_pair("MinimapBottomLeft", Pixel(22, 1059)));
	m_pixelList.insert(make_pair("MinimapTopRight", Pixel(271, 828)));
	m_pixelList.insert(make_pair("MinimapRefPoint1", Pixel(253, 919, 38, 77, 100)));
	m_pixelList.insert(make_pair("MinimapRefPoint2", Pixel(328, 974, 36, 64, 86)));
	m_pixelList.insert(make_pair("RadiantPortrait1", Pixel(562, 20)));
	m_pixelList.insert(make_pair("RadiantPortrait2", Pixel(622, 20)));
	m_pixelList.insert(make_pair("DirePortrait1", Pixel(1092, 20)));
	m_pixelList.insert(make_pair("DirePortrait2", Pixel(1162, 20)));
	m_pixelList.insert(make_pair("HeroPortrait", Pixel(550, 1000)));
	m_pixelList.insert(make_pair("CloseGame", Pixel(21, 24)));
	m_pixelList.insert(make_pair("LeaveGame", Pixel(1786, 975, 56, 36, 34)));
	m_pixelList.insert(make_pair("CloseGameAccept", Pixel(855, 625)));
	m_pixelList.insert(make_pair("GameIsSafe", Pixel(1778, 994, 187, 255, 221)));
	m_pixelList.insert(make_pair("MenuBackArrow", Pixel(136, 30, 17, 17, 17)));
	m_pixelList.insert(make_pair("SteamFailBar", Pixel()));
	m_pixelList.insert(make_pair("LowPrioOK", Pixel(948, 477)));
	m_pixelList.insert(make_pair("Pause", Pixel(947, 354, 36, 37, 33)));
	m_pixelList.insert(make_pair("CompendiumClose", Pixel(1441, 142)));
	m_pixelList.insert(make_pair("LowPriorityIndicator", Pixel(843, 1020, 81, 1, 1)));
}

#include <iostream>
bool Dota2Client::test()
{
	return true;
}

Dota2Client::~Dota2Client()
{
	if (m_hDC)
	{
		ReleaseDC(m_hDotaWnd, m_hDC);
	}
}

bool Dota2Client::initialize()
{
	m_hDotaWnd = FindWindow(NULL, "Dota 2");

	if (m_hDotaWnd == NULL)
	{
		return false;
	}

	m_hDC = GetDC(m_hDotaWnd);

	return m_hDC != NULL;
}

void Dota2Client::feed()
{
	validateWindowMouseState();

	if (m_team == Team::NONE)
		findTeam();

	if (isPaused())
		SendKey(VK_F9);

	SendKey(VK_F1);
	attack();
}

void Dota2Client::findMatch(std::vector<std::string> &modes, bool normal /* = true */)
{
	validateWindowMouseState();

	Pixel& menuBackArrow = m_pixelList["MenuBackArrow"];
	Pixel& playDota = m_pixelList["PlayDota"];
	Pixel& normalMatch = m_pixelList["NormalMatch"];
	std::map<std::string, Pixel> gameModes;

	if (normal)
	{
		gameModes["AllPick"] = m_pixelList["AllPick"];
		gameModes["SingleDraft"] = m_pixelList["SingleDraft"];
		gameModes["CaptainsMode"] = m_pixelList["CaptainsMode"];
		gameModes["RandomDraft"] = m_pixelList["RandomDraft"];
		gameModes["AbilityDraft"] = m_pixelList["AbilityDraft"];
		gameModes["LeastPlayed"] = m_pixelList["LeastPlayed"];
		gameModes["AllRandom"] = m_pixelList["AllRandom"];
		gameModes["LimitedHeroes"] = m_pixelList["LimitedHeroes"];
		gameModes["CaptainsDraft"] = m_pixelList["CaptainsDraft"];
		gameModes["ARDM"] = m_pixelList["ARDM"];
	}
	else
	{
		// ranked
	}

	while (menuBackArrow != pixelSave(menuBackArrow.getX(), menuBackArrow.getY()))
	{
		ClickLeft(menuBackArrow);
	}

	// Check if find-match is open?
	if (playDota != pixelSave(playDota.getX(), playDota.getY()))
	{
		ClickLeft(playDota);
	}

	if (normalMatch.compare(pixelSave(normalMatch.getX(), normalMatch.getY()), Pixel::EPSILON))
	{
		// Open normal match tab
		ClickLeft(normalMatch);
	}

	for (auto it : gameModes)
	{
		// not selected
		bool res = it.second == pixelSave(it.second.getX(), it.second.getY());
		bool found = false;

		for (auto m : modes)
		{
			if (m == it.first)
			{
				found = true;
				break;
			}
		}
		
		if (res && found)
		{
			ClickLeft(it.second);
		}
		else if (!res && !found)
		{
			ClickLeft(it.second);
		}
	}

	//if (allRandomBox != pixelSave(allRandomBox.getX(), allRandomBox.getY()))
	/*if (!allRandomBox.compare(pixelSave(allRandomBox.getX(), allRandomBox.getY()), 10))
	{
	ClickLeft(allRandomBox);
	}*/

	// clear this
	//temp = GetPixel(m_hDC, playDota.getX(), playDota.getY());
	if (playDota.compare(pixelSave(playDota.getX(), playDota.getY()), Pixel::EPSILON))
	{
		ClickLeft(playDota);
	}
}

bool Dota2Client::isMatchReady()
{
	static Pixel* accept = &m_pixelList["Accept"];
	static Pixel* decline = &m_pixelList["Decline"];

	validateWindowMouseState();

	return	accept->compare(pixelSave(accept->getX(), accept->getY()), 5) &&
		decline->compare(pixelSave(decline->getX(), decline->getY()), 5);
}

bool Dota2Client::isMatchStarted()
{
	validateWindowMouseState();
	Pixel* p1 = &m_pixelList["MinimapRefPoint1"];
	Pixel* p2 = &m_pixelList["MinimapRefPoint2"];

	return p1->compare(pixelSave(p1->getX(), p1->getY()), 5) &&
		p2->compare(pixelSave(p2->getX(), p2->getY()), 5);
}

void Dota2Client::pickHero()
{
	validateWindowMouseState();
	
	ClickLeft(m_pixelList["CompendiumClose"]);
	ClickLeft(m_pixelList["PickHero"]);
}

void Dota2Client::acceptMatch()
{
	validateWindowMouseState();

	ClickLeft(m_pixelList["Accept"]);
}

bool Dota2Client::isPaused()
{
	static Pixel* pause = &m_pixelList["Pause"];

	return (*pause == pixelSave(pause->getX(), pause->getY()));
}

bool Dota2Client::isSafeToLeave()
{
	validateWindowMouseState();

	Pixel* safeToLeave = &m_pixelList["GameIsSafe"];
	ClickLeft(m_pixelList["CloseGame"]);
	Sleep(WindowHelper::INPUT_DELAY);
	Pixel temp = pixelSave(safeToLeave->getX(), safeToLeave->getY());
	ClickLeft(m_pixelList["CloseGame"]);

	return *safeToLeave == temp;
}

void Dota2Client::attack()
{
	static Pixel* direction = nullptr;
	if (direction == nullptr)
	{
		if (m_team == Team::RADIANT)
		{
			direction = &m_pixelList["MinimapTopRight"];
		}
		else if (m_team == Team::DIRE)
		{
			direction = &m_pixelList["MinimapBottomLeft"];
		}
	}

	if (direction != nullptr)
	{
		// TODO: Get attack key from user. 
		// Who doesn't use 'a' for attack command? DansGame
		SendKey(0x41);
		ClickLeft(*direction);
	}
}

void Dota2Client::quitMatch()
{
	validateWindowMouseState();

	m_team = Team::NONE;

	ClickLeft(m_pixelList["CloseGame"]);
	ClickLeft(m_pixelList["PlayDota"]);
	ClickLeft(m_pixelList["CloseGameAccept"]);

	Pixel* leaveGame = &m_pixelList["LeaveGame"];
	Sleep(1000);
	while (leaveGame->compare(pixelSave(leaveGame->getX(), leaveGame->getY()), 5))
	{
		ClickLeft(*leaveGame);
		ClickLeft(m_pixelList["CloseGameAccept"]);
	}
}

bool Dota2Client::findTeam()
{
	Pixel& rp1 = m_pixelList["RadiantPortrait1"];
	Pixel& rp2 = m_pixelList["RadiantPortrait2"];
	Pixel& dp1 = m_pixelList["DirePortrait1"];
	Pixel& dp2 = m_pixelList["DirePortrait2"];
	Pixel& heroPort = m_pixelList["HeroPortrait"];

	ClickLeft(rp1);
	Pixel ref1 = pixelSave(heroPort.getX(), heroPort.getY());
	ClickLeft(rp2);
	Pixel ref2 = pixelSave(heroPort.getX(), heroPort.getY());
	if (ref1 != ref2)
	{
		m_team = Team::RADIANT;
		return true;
	}

	ClickLeft(dp1);
	ref1 = pixelSave(heroPort.getX(), heroPort.getY());
	ClickLeft(dp2);
	ref2 = pixelSave(heroPort.getX(), heroPort.getY());
	if (ref1 != ref2)
	{
		m_team = Team::DIRE;
		return true;
	}

	return false;
}

void Dota2Client::validateWindowMouseState()
{
	if (!isMouseInDota())
		correctMouse();

	if (!isInFocus())
	{
		setFocus();
		Sleep(WindowHelper::INPUT_DELAY);
	}
}

bool Dota2Client::isInFocus()
{
	HWND hWnd = GetForegroundWindow();
	return hWnd == m_hDotaWnd;
}

bool Dota2Client::isMouseInDota()
{
	POINT pos;
	GetCursorPos(&pos);
	RECT rect;
	GetWindowRect(m_hDotaWnd, &rect);

	return (pos.x >= rect.left && pos.x <= rect.right) && (pos.y >= rect.top && pos.y <= rect.bottom);
}

void Dota2Client::correctMouse()
{
	WindowHelper::MoveMouse(m_hDotaWnd, 100, 100);
}

void Dota2Client::setFocus()
{
	SetForegroundWindow(m_hDotaWnd);
}

void Dota2Client::ClickLeft(Pixel& coord, size_t times)
{
	for (size_t i = 0; i < times; ++i)
	{
		WindowHelper::LeftClick(m_hDotaWnd, coord.getX(), coord.getY());
	}
}

void Dota2Client::ClickRight(Pixel& coord, size_t times)
{
	for (size_t i = 0; i < times; i++)
	{
		WindowHelper::RightClick(m_hDotaWnd, coord.getX(), coord.getY());
	}
}

void Dota2Client::SendKey(DWORD vkey, size_t times)
{
	for (size_t i = 0; i < times; i++)
	{
		WindowHelper::SendKey(m_hDotaWnd, vkey);
	}
}

Pixel Dota2Client::pixelSave(int x, int y)
{
	COLORREF color = GetPixel(m_hDC, x, y);
	return Pixel(x, y, GetRValue(color), GetGValue(color), GetBValue(color));
}

Dota2Client* Dota2Client::s_Instance = nullptr;

Dota2Client* Dota2Client::getInstance()
{
	if (s_Instance != nullptr)
		return s_Instance;

	s_Instance = new Dota2Client();
	if (!s_Instance->initialize())
	{
		delete s_Instance;
		s_Instance = nullptr;
	}

	if (s_Instance != nullptr)
	{
		//SetForegroundWindow(s_Instance->m_hDotaWnd);
		Sleep(WindowHelper::INPUT_DELAY * 2);
	}

	return s_Instance;
}

