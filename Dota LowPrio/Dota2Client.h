#pragma once

#include "WindowHelper.h"
#include "Pixel.h"
#include <vector>
#include <string>
#include <map>

class Dota2Client
{
public:
	~Dota2Client();

	static Dota2Client* getInstance();

	void findMatch(std::vector<std::string>& modes, bool normal = true);
	bool isMatchReady();
	void acceptMatch();
	bool isMatchStarted();
	bool isSafeToLeave();
	void pickHero();
	void feed();
	void quitMatch();
	bool test();
	bool isPaused();

private:
	enum class Team
	{
		NONE,
		RADIANT,
		DIRE
	};

	Dota2Client();

	bool initialize();
	void attack();	
	bool findTeam();

	void validateWindowMouseState();
	bool isInFocus();
	bool isMouseInDota();
	void setFocus();
	void correctMouse();

	void ClickLeft(Pixel& coord, size_t iTimes = 1);
	void ClickRight(Pixel& coord, size_t iTimes = 1);
	void SendKey(DWORD vKey, size_t iTimes = 1);
	Pixel pixelSave(int x, int y);

	static Dota2Client* s_Instance;

	HWND m_hDotaWnd;
	HDC m_hDC;
	Team m_team;
	Pixel m_heroPortrait;

	std::map<std::string, Pixel> m_pixelList;
};