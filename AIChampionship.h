#ifndef _AICHAMPIONSHIP_H_
#define _AICHAMPIONSHIP_H_

#include <vector>

class AIChampionship
{
public:
	AIChampionship();

	void Play();
	int Player1Wins();
	int Player2Wins();

private:

	int player1{ 0 }, player2{ 0 };
	bool gameOver{ false };

};

#endif