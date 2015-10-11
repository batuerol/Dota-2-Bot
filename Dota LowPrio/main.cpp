#include <iostream>
#include <thread>
#include <chrono>

#include "Dota2Client.h"
#include "StopWatch.h"

Dota2Client* g_pDota = Dota2Client::getInstance();

void Queue(std::vector<std::string> &modes)
{
	g_pDota->findMatch(modes);

	while (!g_pDota->isMatchStarted())
	{
		if (g_pDota->isMatchReady())
		{
			g_pDota->acceptMatch();
		}

		std::this_thread::sleep_for(std::chrono::seconds(15));
	}
}

int main(int argc, char** argv)
{
	if (g_pDota == nullptr)
	{
		return -1;
	}

	std::vector<std::string> modes = { "AllRandom" };

	for (int i = 0; i < 5; ++i)
	{
		Queue(modes);

		std::this_thread::sleep_for(std::chrono::seconds(15));

		g_pDota->pickHero();

		std::this_thread::sleep_for(std::chrono::seconds(15));

		while (true)
		{
			g_pDota->feed();
			if (g_pDota->isSafeToLeave())
			{
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(15));
		}

		g_pDota->quitMatch();
	}
}